/**
 * @file
 * Header file supplied for use by 3rd party code so that they can easily
 * include all necessary headers.
 */

//
// TODO What's next:
// * Library Extension
// * Math library (started)
//   * round, min, max, log, ceil, exp
//   * number format to string
// * Date/Time type & functions
// * Execution count timeout
// * Potential tail call optimization rather than loop & switch case for VM
// * Use string views
// * Move GarbageCollected from global to Context, in order to get rid of mutex
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

