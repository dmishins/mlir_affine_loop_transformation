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

// clang-tidy seems to expect the absolute path in the header guard on some
// systems, so just disable it.
// NOLINTNEXTLINE(llvm-header-guard)
#ifndef DIALECT_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS_H
#define DIALECT_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS_H

#include "mlir/Pass/Pass.h"
#include "loopinterchange/Passes/Passes.h"

namespace mlir {
class FunctionOpInterface;

namespace loopinterchange {

#define GEN_PASS_CLASSES
#include "loopinterchange/Passes/Passes.h.inc"

} // namespace loopinterchange
} // namespace mlir

#endif // DIALECT_LOOPINTERCHANGE_TRANSFORMS_PASSDETAILS_H
