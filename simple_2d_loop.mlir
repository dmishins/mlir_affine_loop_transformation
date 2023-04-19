module attributes {dlti.dl_spec = #dlti.dl_spec<#dlti.dl_entry<"dlti.endianness", "little">, #dlti.dl_entry<i64, dense<64> : vector<2xi32>>, #dlti.dl_entry<f80, dense<128> : vector<2xi32>>, #dlti.dl_entry<i1, dense<8> : vector<2xi32>>, #dlti.dl_entry<i8, dense<8> : vector<2xi32>>, #dlti.dl_entry<i16, dense<16> : vector<2xi32>>, #dlti.dl_entry<i32, dense<32> : vector<2xi32>>, #dlti.dl_entry<f16, dense<16> : vector<2xi32>>, #dlti.dl_entry<f64, dense<64> : vector<2xi32>>, #dlti.dl_entry<f128, dense<128> : vector<2xi32>>>, llvm.data_layout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128", llvm.target_triple = "x86_64-unknown-linux-gnu", "polygeist.target-cpu" = "x86-64", "polygeist.target-features" = "+cx8,+fxsr,+mmx,+sse,+sse2,+x87", "polygeist.tune-cpu" = "generic"} {
  llvm.mlir.global internal constant @str0("hi %u\0A\00") {addr_space = 0 : i32}
  llvm.func @printf(!llvm.ptr<i8>, ...) -> i32
  memref.global "private" @array : memref<10xi32> = uninitialized
  func.func @main() -> i32 attributes {llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %0 = memref.get_global @array : memref<10xi32>
    affine.for %arg0 = 0 to 10 {
      %3 = arith.index_cast %arg0 : index to i64
      %4 = arith.trunci %3 : i64 to i32
      affine.store %4, %0[%arg0] : memref<10xi32>
    }
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr<array<7 x i8>>
    %2 = llvm.getelementptr %1[0, 0] : (!llvm.ptr<array<7 x i8>>) -> !llvm.ptr<i8>
    affine.for %arg0 = 0 to 10 step 2 {
      %3 = affine.load %0[%arg0] : memref<10xi32>
      %4 = llvm.call @printf(%2, %3) : (!llvm.ptr<i8>, i32) -> i32
    }
    return %c0_i32 : i32
  }
}
