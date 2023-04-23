//===- ForBreakToWhile.cpp - scf.for(scf.if) to scf.while lowering --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PassDetails.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlowOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/SCF/Transforms/Passes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"

#include "polygeist/Passes/Passes.h"

using namespace mlir;
using namespace mlir::scf;
using namespace mlir::polygeist;


namespace {
struct TestPrint : public TestPrintBase<TestPrint> {
  void runOnOperation() override {
    // auto *parentOp = getOperation();
    // MLIRContext *ctx = parentOp->getContext();
    // RewritePatternSet patterns(ctx);
    // patterns.add<ForBreakLoweringPattern>(patterns.getContext(), /*benefit=*/3);
    // (void)applyPatternsAndFoldGreedily(parentOp, std::move(patterns));
  }
};
} // namespace

// void mlir::polygeist::populateForBreakToWhilePatterns(
//     RewritePatternSet &patterns) {
//   patterns.add<ForBreakLoweringPattern>(patterns.getContext(), /*benefit=*/3);
// }

std::unique_ptr<Pass> mlir::polygeist::testPrint() {
  return std::make_unique<TestPrint>();
}
