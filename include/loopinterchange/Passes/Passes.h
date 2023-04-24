#ifndef LOOPINTERCHANGE_DIALECT_LOOPINTERCHANGE_PASSES_H
#define LOOPINTERCHANGE_DIALECT_LOOPINTERCHANGE_PASSES_H

#include "mlir/Conversion/LLVMCommon/LoweringOptions.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include <memory>
namespace mlir {
class PatternRewriter;
class RewritePatternSet;
class DominanceInfo;
namespace loopinterchange {
std::unique_ptr<Pass> testPrint();
std::unique_ptr<OperationPass<mlir::func::FuncOp>> createLoopTilingBtrPass(uint64_t);
std::unique_ptr<OperationPass<mlir::func::FuncOp>> createLoopTilingBtrPass();
std::unique_ptr<OperationPass<mlir::func::FuncOp>> createLoopInterleavePass();

void populateForBreakToWhilePatterns(RewritePatternSet &patterns);
} // namespace loopinterchange
} // namespace mlir

namespace mlir {
// Forward declaration from Dialect.h
template <typename ConcreteDialect>
void registerDialect(DialectRegistry &registry);

namespace arith {
class ArithDialect;
} // end namespace arith

namespace scf {
class SCFDialect;
} // end namespace scf

namespace memref {
class MemRefDialect;
} // end namespace memref

namespace func {
class FuncDialect;
}

class AffineDialect;
namespace LLVM {
class LLVMDialect;
}

#define GEN_PASS_REGISTRATION
#include "loopinterchange/Passes/Passes.h.inc"

} // end namespace mlir

#endif // LOOPINTERCHANGE_DIALECT_LOOPINTERCHANGE_PASSES_H
