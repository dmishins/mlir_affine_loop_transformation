rm -rf build
mkdir build
cd build
cmake -G Ninja .. \
  -DMLIR_DIR=$PWD/../../Polygeist/build/lib/cmake/mlir \
  -DCLANG_DIR=$PWD/../../Polygeist/build/lib/cmake/clang \
  -DLLVM_TARGETS_TO_BUILD='host' \
  -DLLVM_ENABLE_ASSERTIONS=ON \
  -DCMAKE_BUILD_TYPE=DEBUG
ninja