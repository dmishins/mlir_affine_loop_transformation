POLY_PATH=../Polygeist/build/bin

# echo "${POLY_PATH}/cgeist ${1}.c --raise-scf-to-affine -S > ${1}.mlir"
${POLY_PATH}/cgeist ${1}.c --raise-scf-to-affine -S > ${1}.mlir


${POLY_PATH}/mlir-opt -lower-affine \
    -convert-scf-to-cf \
    -memref-expand \
    -convert-memref-to-llvm \
    -convert-vector-to-llvm \
    -convert-func-to-llvm \
    -convert-cf-to-llvm \
    -reconcile-unrealized-casts \
    ${1}.mlir | ${POLY_PATH}/mlir-translate --mlir-to-llvmir > ${1}.ll


# echo "${POLY_PATH}/clang ${1}.ll -o ${1}.out"
${POLY_PATH}/clang ${1}.ll -o ${1}.out

./${1}.out