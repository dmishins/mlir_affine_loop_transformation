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

namespace {

/// A pass to perform loop tiling on all suitable loop nests of a Function.
struct AffineLoopInterleave
    : public AffineLoopInterleaveBase<AffineLoopInterleave> {
  AffineLoopInterleave() = default;
  void runOnOperation() override;

  bool isLoopInterchangeable(AffineForOp forOp) {
    bool valid = true;
    forOp.walk([&](Operation *op) {
      if (op->getName().getStringRef() == "llvm.call") {
        valid = false;
        LLVM_DEBUG(llvm::dbgs() << op->getName() << " : " << op->getDialect()
                                << " not valid \n");
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

#undef LLVM_DEBUG
#define LLVM_DEBUG(X)                                                          \
  { X; }

void AffineLoopInterleave::runOnOperation() {
  // Bands of loops to tile.
  LLVM_DEBUG(llvm::dbgs() << ">> Hello World, welcome to our pass! \n");

  func::FuncOp func = getOperation();
  func.walk([&](Operation *op) {
    if (auto affineForOp = dyn_cast<AffineForOp>(op)) {
      LLVM_DEBUG(llvm::dbgs() << ">> Yay! A loop!: " << op->getName() << "\n");
      SmallVector<AffineForOp, 4> loops;
      SmallVector<unsigned int, 4> map;

      getPerfectlyNestedLoops(loops, affineForOp);
      if (loops.size() < 2) {
        LLVM_DEBUG(llvm::dbgs() << ">> Not a nested loop, skipping\n");
        return;
      }
      LLVM_DEBUG(llvm::dbgs() << ">> Found a perfect nest of depth "
                              << loops.size() << '\n');

      for (unsigned int i = 0; i < loops.size(); i++) {
        map.push_back(i);
      }

      // Check which permutation is better.
      auto &body = loops.back().getLoopBody();
      if (body.getBlocks().size() > 1) {
        LLVM_DEBUG(llvm::dbgs() << ">> Not a single block, skipping\n");
        return;
      }
      auto &block = body.front();
      for (auto &op : block) {
        if (auto aop = dyn_cast<AffineLoadOp>(op)) {
          LLVM_DEBUG(llvm::dbgs()
                     << ">> Found an affine load expr: " << aop << "\n");
          auto affineMapAttr = aop.getAffineMapAttr();
          LLVM_DEBUG(llvm::dbgs()
                     << ">> Affine map attr: " << affineMapAttr << "\n");
          // auto indices = aop.getIndices();
          // for (auto const index : indices) {
          //   LLVM_DEBUG(llvm::dbgs() << ">> Index: " << index << "\n");
          //   // if (auto expr = index.dyn_cast<Index>()) {
          //   //   LLVM_DEBUG(llvm::dbgs() << ">> Dim expr: " << expr << "\n");
          //   //   if (expr.getPosition() == 0) {
          //   //     LLVM_DEBUG(llvm::dbgs() << ">> Swapping 0 and 1");
          //   //     std::swap(map[0], map[1]);
          //   //     break;
          //   //   }
          //   // }
          // }
        } else if (auto aop = dyn_cast<AffineStoreOp>(op)) {
          //
        }
      }

      // Hardcoded for now :(
      std::swap(map[0], map[1]);

      if (isValidLoopInterchangePermutation(loops, map)) {
        LLVM_DEBUG(llvm::dbgs() << ">> Valid to permute, but only if there are "
                                   "no function calls/issues! \n");
        if (isLoopInterchangeable(affineForOp)) {
          permuteLoops(loops, map);
          LLVM_DEBUG(llvm::dbgs() << ">> All good, permuting\n");
        }
      } else {
        LLVM_DEBUG(llvm::dbgs() << ">> Can't permute :( \n");
      }
    } else {
      LLVM_DEBUG(llvm::dbgs()
                 << ">> Operation is not a loop: " << op->getName() << "\n");
    }
  });
}
