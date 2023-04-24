set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name loopinterchange)
add_public_tablegen_target(MLIRLoopInterchangePassIncGen)

add_mlir_doc(Passes LoopInterchangePasses ./ -gen-pass-doc)
