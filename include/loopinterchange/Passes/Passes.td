#ifndef LOOPINTERCHANGE_PASSES
#define LOOPINTERCHANGE_PASSES

include "mlir/Pass/PassBase.td"

def TestPrint : Pass<"test-print"> {
  let summary = "Test print";
  let constructor = "mlir::loopinterchange::testPrint()";
}

def AffineLoopInterleave : Pass<"affine-loop-interleave", "func::FuncOp"> {
  let summary = "Tile affine loop nests";
  let constructor = "mlir::loopinterchange::createLoopInterleavePass()";
}

def AffineLoopTilingBtr : Pass<"affine-loop-tile-btr", "func::FuncOp"> {
  let summary = "Tile affine loop nests";
  let constructor = "mlir::loopinterchange::createLoopTilingBtrPass()";
  let options = [
    Option<"cacheSizeInKiB", "cache-size", "uint64_t", /*default=*/"512",
           "Set size of cache to tile for in KiB (default: 512)">,
    Option<"separate", "separate", "bool", /*default=*/"false",
           "Separate full and partial tiles (default: false)">,
    Option<"tileSize", "tile-size", "unsigned", /*default=*/"",
           "Use this tile size for all loops">,
    ListOption<"tileSizes", "tile-sizes", "unsigned",
               "List of tile sizes for each perfect nest "
               "(overridden by -tile-size)">,
  ];
}

#endif // LOOPINTERCHANGE_PASSES
