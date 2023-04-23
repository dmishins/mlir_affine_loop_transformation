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

#include "polygeist/Passes/Passes.h"

using namespace mlir;
using namespace mlir::polygeist;

#define DEBUG_TYPE "affine-loop-interleave"

namespace {

/// A pass to perform loop tiling on all suitable loop nests of a Function.
struct AffineLoopInterleave : public AffineLoopInterleaveBase<AffineLoopInterleave> {
  AffineLoopInterleave() = default;
  void runOnOperation() override;

};

} // namespace

/// Creates a pass to perform loop tiling on all suitable loop nests of a
/// Function.
std::unique_ptr<OperationPass<func::FuncOp>> mlir::polygeist::createLoopInterleavePass() {
  return std::make_unique<AffineLoopInterleave>();
}

void AffineLoopInterleave::runOnOperation() {
  // Bands of loops to tile.
  llvm::outs() << "Hello World, welcome to our pass! \n";

    func::FuncOp func = getOperation();
    func.walk([&](Operation *op) {
      if (auto affineForOp = dyn_cast<AffineForOp>(op)){
        LLVM_DEBUG(llvm::outs() << "Yay! A loop!:" << func.getName() <<  "\n");

      }
      else{
        LLVM_DEBUG(llvm::outs() << "Operation is not a loop:" << func.getName() <<  "\n");
      }
    });
  
}
