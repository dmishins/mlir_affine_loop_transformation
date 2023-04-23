while getopts f:xh flag
do
   case ${flag} in
        x) run="yes";;
        f) item=${OPTARG};;
        h) echo "Usage: $0 [-f <item>] [-x] [-h]"; exit 0;;
   esac
done

POLY_PATH=../../Polygeist/build/bin

${POLY_PATH}/cgeist ${item}.c --raise-scf-to-affine -S > ${item}.mlir


${POLY_PATH}/mlir-opt -lower-affine \
    -convert-scf-to-cf \
    -memref-expand \
    -convert-memref-to-llvm \
    -convert-vector-to-llvm \
    -convert-func-to-llvm \
    -convert-cf-to-llvm \
    -reconcile-unrealized-casts \
    ${item}.mlir | ${POLY_PATH}/mlir-translate --mlir-to-llvmir > ${item}.ll


${POLY_PATH}/clang ${item}.ll -o ${item}.out

# check if we want to run
if [ "$run" = "yes" ]; then
    echo "Running ${item}"
    ./${item}.out
fi