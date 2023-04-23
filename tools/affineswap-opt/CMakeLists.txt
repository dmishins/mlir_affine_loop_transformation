get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)
set(LIBS
        ${dialect_libs}
        ${conversion_libs}
        MLIROptLib
		MLIRPolygeist
		MLIRPolygeistTransforms
        )
add_llvm_executable(affineswap-opt affineswap-opt.cpp)

install(TARGETS affineswap-opt
EXPORT PolygeistTargets
RUNTIME DESTINATION ${LLVM_TOOLS_INSTALL_DIR}
COMPONENT affineswap-opt)

llvm_update_compile_flags(affineswap-opt)
target_link_libraries(affineswap-opt PRIVATE ${LIBS})
