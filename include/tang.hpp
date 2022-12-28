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
// 2. Poke.. pop.. peek, when poke and peek are the same stack location.
//    24 POKE        0
//    26 POP
//    27 PEEK        0
//    ex: 26 & 27 can be removed, if not a jump target.
//        27 is often a jump target when 26 is from a for() initialization.
//
// 3. Push.. pop, can be removed.
//    17 JMPF_POP    24
//    19 NULLVAL
//    20 POP
//    21 JMP         7
//    ex: 19 & 20 can be removed, if 20 is not a jump target.
//
//
// TODO What's next:
// * Better location tracking for bytecode and error reporting.
// * Tang version
// * Library Extension
// * Math library (started)
//   * round, min, max, log, ceil, exp
//   * number format to string
// * Date/Time type & functions
// * Execution count timeout
// * Stand-alone interpreter program
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

