get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIROptLib
		MLIRLoopInterchangeTransforms
        )
add_llvm_executable(loop-opt loop-opt.cpp)

install(TARGETS loop-opt
EXPORT LoopInterchangeTargets
RUNTIME DESTINATION ${LLVM_TOOLS_INSTALL_DIR}
COMPONENT loop-opt)

llvm_update_compile_flags(loop-opt)
target_link_libraries(loop-opt PRIVATE ${LIBS})
