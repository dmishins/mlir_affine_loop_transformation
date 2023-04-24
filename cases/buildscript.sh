POLY_PATH=../../Polygeist/build/bin

while getopts f:xh flag
do
   case ${flag} in
        x) run="yes";;
        f) file=${OPTARG};;
        h) echo "Usage: $0 [-f <file>] [-x] [-h]"; exit 0;;
   esac
done

item="${file%.c}"

echo "${POLY_PATH}/cgeist ${item}.c --raise-scf-to-affine -S > ${item}.mlir"
${POLY_PATH}/cgeist ${item}.c --raise-scf-to-affine -S > ${item}.mlir


echo "../build/bin/loop-opt -affine-loop-interleave ${item}.mlir > ${item}_transformed.mlir"
../build/bin/loop-opt -affine-loop-interleave ${item}.mlir > ${item}_transformed.mlir

${POLY_PATH}/mlir-opt -lower-affine \
    -convert-scf-to-cf \
    -memref-expand \
    -convert-memref-to-llvm \
    -convert-vector-to-llvm \
    -convert-func-to-llvm \
    -convert-cf-to-llvm \
    -reconcile-unrealized-casts \
    ${item}_transformed.mlir | ${POLY_PATH}/mlir-translate --mlir-to-llvmir > ${item}_transformed.ll


# echo "${POLY_PATH}/mlir-opt -lower-affine \
#     -convert-scf-to-cf \
#     -memref-expand \
#     -convert-memref-to-llvm \
#     -convert-vector-to-llvm \
#     -convert-func-to-llvm \
#     -convert-cf-to-llvm \
#     -reconcile-unrealized-casts \
#     ${item}.mlir | ${POLY_PATH}/mlir-translate --mlir-to-llvmir > ${item}_transformed.ll"

${POLY_PATH}/mlir-opt -lower-affine \
    -convert-scf-to-cf \
    -memref-expand \
    -convert-memref-to-llvm \
    -convert-vector-to-llvm \
    -convert-func-to-llvm \
    -convert-cf-to-llvm \
    -reconcile-unrealized-casts \
    ${item}.mlir | ${POLY_PATH}/mlir-translate --mlir-to-llvmir > ${item}.ll


echo "${POLY_PATH}/clang ${item}.ll -o ${item}.out"
${POLY_PATH}/clang ${item}.ll -o ${item}.out

echo "${POLY_PATH}/clang ${item}_transformed.ll -o ${item}_transformed.out"
${POLY_PATH}/clang ${item}_transformed.ll -o ${item}_transformed.out

# check if we want to run
if [ "$run" = "yes" ]; then
    echo "[[ Running <${item}> ]]"
    ./${item}.out
    echo "[[ Running <${item}_transformed> ]]"
    ./${item}_transformed.out
fi