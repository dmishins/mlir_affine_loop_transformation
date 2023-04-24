//===- PassDetails.h - loopinterchange pass class details ----------------*- C++
//-*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Stuff shared between the different loopinterchange passes.
//
//===----------------------------------------------------------------------===//

#ifndef LIB_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS
#define LIB_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS

#include "mlir/Pass/Pass.h"
#include "loopinterchange/Passes.h"

namespace mlir {
class FunctionOpInterface;

namespace loopinterchange {

#define GEN_PASS_CLASSES
#include "loopinterchange/Passes.h.inc"

} // namespace loopinterchange
} // namespace mlir

#endif /* LIB_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS */
