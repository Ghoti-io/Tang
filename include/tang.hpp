/**
 * @file
 * Header file supplied for use by 3rd party code so that they can easily
 * include all necessary headers.
 */

//
// Future Optimizations:
//
// 1. All opcodes after a JMP and before a jump target can be removed.
//    17 JMPF_POP    32
//      ...
//    29 JMP         12
//    31 POP
//    32 PEEK        1
//    ex: 31 can be removed.
//
//
// TODO What's next:
// * Library Extension
// * Math library (started)
//   * round, min, max, log, ceil, exp
//   * number format to string
// * Date/Time type & functions
// * Execution count timeout
// * Optimization
// * Potential tail call optimization rather than loop & switch case for VM
//

#ifndef TANG_HPP
#define TANG_HPP

#include "macros.hpp"
#include "tangBase.hpp"
#include "astNode.hpp"
#include "error.hpp"
#include "garbageCollected.hpp"
#include "program.hpp"
#include "context.hpp"
#include "opcode.hpp"
#include "computedExpression.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionError.hpp"

#endif // TANG_HPP

