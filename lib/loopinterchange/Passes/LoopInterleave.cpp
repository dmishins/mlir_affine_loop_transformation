//===- LoopTiling.cpp --- Loop tiling pass ------------------------------*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements a pass to tile loop nests.
//
//===----------------------------------------------------------------------===//

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
#include "mlir/IR/BlockAndValueMapping.h"
#include "mlir/IR/Builders.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"

namespace mlir {
#define GEN_PASS_DEF_AFFINELOOPTILING
#include "mlir/Dialect/Affine/Passes.h.inc"
} // namespace mlir

#include "PassDetails.h"

#include "loopinterchange/Passes/Passes.h"

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

void AffineLoopInterleave::runOnOperation() {
  // Bands of loops to tile.
  LLVM_DEBUG(llvm::dbgs() << "Hello World, welcome to our pass! \n");

  func::FuncOp func = getOperation();
  func.walk([&](Operation *op) {
    if (auto affineForOp = dyn_cast<AffineForOp>(op)) {
      LLVM_DEBUG(llvm::dbgs() << "Yay! A loop!:" << op->getName() << "\n");
      SmallVector<AffineForOp, 4> loops;
      SmallVector<unsigned int, 4> map{1, 0};

      getPerfectlyNestedLoops(loops, affineForOp);
      LLVM_DEBUG(llvm::dbgs()
                 << "found a perfect nest of depth " << loops.size() << '\n');
      if (loops.size() == 2) {
        if (isValidLoopInterchangePermutation(loops, map)) {
          LLVM_DEBUG(llvm::dbgs() << "valid to permute, but only if there are "
                                     "no function calls/issues! \n");
          if (isLoopInterchangeable(affineForOp)) {
            permuteLoops(loops, map);
            LLVM_DEBUG(llvm::dbgs() << "All good, permuting\n ");
          }
        } else {
          LLVM_DEBUG(llvm::dbgs() << "Can't permute :( \n");
        }
      } else {
        LLVM_DEBUG(llvm::dbgs() << "not 2 depth :( \n");
      }
    } else {
      LLVM_DEBUG(llvm::dbgs()
                 << "Operation is not a loop:" << op->getName() << "\n");
    }
  });
}
