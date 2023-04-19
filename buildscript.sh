echo "./bin/cgeist ${1}.c --raise-scf-to-affine -S  > ${1}.mlir"
./bin/cgeist ${1}.c --raise-scf-to-affine -S  > ${1}.mlir


echo "./bin/mlir-opt \
    --lower-affine \
    --convert-arith-to-llvm \
    --convert-scf-to-cf \
    --convert-func-to-llvm \
    --reconcile-unrealized-casts ${1}.mlir | ./bin/mlir-translate --mlir-to-llvmir > ${1}.ll"
./bin/mlir-opt -lower-affine -convert-scf-to-cf -memref-expand -convert-memref-to-llvm -convert-vector-to-llvm -convert-func-to-llvm -convert-cf-to-llvm -reconcile-unrealized-casts  ${1}.mlir | ./bin/mlir-translate --mlir-to-llvmir > ${1}.ll


# ./bin/mlir-opt \
#     --lower-affine \
#     --convert-arith-to-llvm \
#     --convert-scf-to-cf \
#     --convert-func-to-llvm \
#     --reconcile-unrealized-casts ${1}.mlir | ./bin/mlir-translate --mlir-to-llvmir > ${1}.ll


echo "./bin/clang ${1}.ll -o ${1}.out"
./bin/clang ${1}.ll -o ${1}.out