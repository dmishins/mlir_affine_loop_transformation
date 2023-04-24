add_mlir_dialect_library(MLIRLoopInterchangeTransforms
  TestPrint.cpp
  LoopTiling.cpp
  LoopInterleave.cpp

  ADDITIONAL_HEADER_DIRS
  ${MLIR_MAIN_INCLUDE_DIR}/mlir/Dialect/Affine

  DEPENDS
  MLIRLoopInterchangePassIncGen

  LINK_LIBS PUBLIC
  MLIRAffineDialect
  MLIRArithDialect
  MLIRAsyncDialect
  MLIRAffineUtils
  MLIRFuncDialect
  MLIRFuncTransforms
  MLIRGPUOps
  MLIRIR
  MLIRLLVMDialect
  MLIRMathDialect
  MLIRMathToLLVM
  MLIRMemRefDialect
  MLIRNVVMDialect
  MLIRPass
  MLIRSideEffectInterfaces
  MLIRSCFToControlFlow
  MLIRTargetLLVMIRImport
  MLIRTransformUtils
  MLIRControlFlowToLLVM
  MLIRMemRefToLLVM
  MLIRFuncToLLVM
  MLIRArithToLLVM
  MLIROpenMPToLLVM
  )
