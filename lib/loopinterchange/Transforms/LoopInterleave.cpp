#include "mlir/Dialect/Affine/Passes.h"

#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/AffineStructures.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/Utils.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/BlockAndValueMapping.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/Location.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"

namespace mlir {
#define GEN_PASS_DEF_AFFINELOOPTILING
#include "mlir/Dialect/Affine/Passes.h.inc"
} // namespace mlir

#include "PassDetails.h"

using namespace mlir;
using namespace mlir::loopinterchange;

#define DEBUG_TYPE "affine-loop-interleave"

// For debugging purposes.
#undef LLVM_DEBUG
#define LLVM_DEBUG(X)                                                          \
  { X; }

namespace {

/// A pass to perform loop tiling on all suitable loop nests of a Function.
struct AffineLoopInterleave
    : public AffineLoopInterleaveBase<AffineLoopInterleave> {
  AffineLoopInterleave() = default;
  void runOnOperation() override;

  struct ForArgs {
    SmallVector<mlir::Location, 4> locs;
    void push(mlir::Location loc) { locs.push_back(loc); }
    unsigned int query(mlir::Location loc) const {
      // LLVM_DEBUG(llvm::dbgs() << ">> Querying for " << loc << "\n");
      for (unsigned int i = 0; i < locs.size(); i++) {
        // LLVM_DEBUG(llvm::dbgs() << ">> Comparing with " << locs[i] << "\n");
        if (locs[i] == loc) {
          return i;
        }
      }
      return -1;
    }
  };

  struct IMap {
    SmallVector<unsigned int, 4> map;
    bool filled = false;
    bool setOrCheck(SmallVector<unsigned int, 4> other) {
      if (!filled) {
        filled = true;
        map = other;
        return true;
      }
      if (map.size() != other.size()) {
        return false;
      }
      for (unsigned int i = 0; i < map.size(); i++) {
        if (map[i] != other[i]) {
          return false;
        }
      }
      return true;
    }
    bool isIMapAligned(mlir::Operation::operand_range indices,
                       ForArgs const &forArgs) {
      SmallVector<unsigned int, 4> imap;
      for (auto const index : indices) {
        unsigned int arg = forArgs.query(index.getLoc());
        // LLVM_DEBUG(llvm::dbgs() << ">> Index: \%arg" << arg << "\n");
        if (arg == (unsigned)-1) {
          LLVM_DEBUG(llvm::dbgs() << ">> Index not found in for args\n");
          return false;
        }
        imap.push_back(arg);
      }
      return setOrCheck(imap);
    }
  };

  bool isLoopInterchangeable(AffineForOp forOp) {
    bool valid = true;
    forOp.walk([&](Operation *op) {
      if (op->getName().getStringRef() == "llvm.call") {
        valid = false;
        LLVM_DEBUG(llvm::dbgs()
                   << ">> Found " << op->getName() << " : " << op->getDialect()
                   << " which is not valid \n");
      }
    });
    return valid;
  }
};

} // namespace

/// Creates a pass to perform loop tiling on all suitable loop nests of a
/// Function.
std::unique_ptr<OperationPass<func::FuncOp>>
mlir::loopinterchange::createLoopInterleavePass() {
  return std::make_unique<AffineLoopInterleave>();
}

void AffineLoopInterleave::runOnOperation() {
  // Bands of loops to tile.
  LLVM_DEBUG(llvm::dbgs() << ">> Performing loop interchange optimization\n");

  func::FuncOp func = getOperation();
  func.walk([&](Operation *op) {
    if (auto affineForOp = dyn_cast<AffineForOp>(op)) {
      LLVM_DEBUG(llvm::dbgs() << ">> Found " << op->getName() << "at"
                              << op->getLoc() << "\n");
      SmallVector<AffineForOp, 4> loops;
      ForArgs forArgs;
      IMap imapBaseLine;

      // Get the perfectly nested loops.
      getPerfectlyNestedLoops(loops, affineForOp);
      if (loops.size() < 2) {
        // LLVM_DEBUG(llvm::dbgs() << ">> Not a nested loop, skipping\n");
        return;
      }
      LLVM_DEBUG(llvm::dbgs() << ">> Found a perfect nest of depth "
                              << loops.size() << '\n');

      // Setup the map and the induction vars.
      for (unsigned int i = 0; i < loops.size(); i++) {
        auto loc = loops[i].getInductionVar().getLoc();
        // LLVM_DEBUG(llvm::dbgs() << ">> Induction var: " << loc << "\n");
        forArgs.push(loc);
      }

      // Check which permutation is better.
      auto &body = loops.back().getLoopBody();
      if (body.getBlocks().size() > 1) {
        LLVM_DEBUG(llvm::dbgs() << ">> Not a single block, skipping\n");
        return;
      }
      auto &block = body.front();
      bool aligned = true;
      for (auto &op : block) {
        bool alignedCurrent = true;
        if (auto aop = dyn_cast<AffineLoadOp>(op)) {
          LLVM_DEBUG(llvm::dbgs()
                     << ">> Found an affine load expr: " << aop << "\n");
          alignedCurrent =
              imapBaseLine.isIMapAligned(aop.getIndices(), forArgs);
          ////
        } else if (auto aop = dyn_cast<AffineStoreOp>(op)) {
          LLVM_DEBUG(llvm::dbgs()
                     << ">> Found an affine store expr: " << aop << "\n");
          alignedCurrent =
              imapBaseLine.isIMapAligned(aop.getIndices(), forArgs);
        }
        if (!alignedCurrent) {
          aligned = false;
          break;
        }
      }
      // Check if the accesses are aligned, and only permute if they are.
      if (!aligned || !imapBaseLine.filled) {
        LLVM_DEBUG(llvm::dbgs() << ">> Accesses are not aligned, skipping\n");
        return;
      }

      LLVM_DEBUG(
          llvm::dbgs()
          << ">> All accesses are aligned, producing the new affine map:\n");

      // Changing the loop interleaving map.
      auto &affineMap = imapBaseLine.map;

      for (unsigned int i = 0; i < affineMap.size(); i++) {
        LLVM_DEBUG(llvm::dbgs()
                   << ">> " << i << " -> " << affineMap[i] << "\n");
      }

      // Check if the result permutation is valid dependency-wise.
      if (!isValidLoopInterchangePermutation(loops, affineMap)) {
        LLVM_DEBUG(llvm::dbgs()
                   << ">> Failed dependency check, can't permute :( \n");
        return;
      }

      // Check if the loop has side effects.
      if (!isLoopInterchangeable(affineForOp)) {
        LLVM_DEBUG(llvm::dbgs()
                   << ">> Unable to permute due to side effects found\n");
        return;
      }

      // Finally, permute the loops.
      LLVM_DEBUG(llvm::dbgs() << ">> All good, permuting :)\n");
      permuteLoops(loops, affineMap);
    }
  });
}
