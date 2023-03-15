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
// * Use string views
//

#ifndef TANG_HPP
#define TANG_HPP

#include "tang/astNodeArray.hpp"
#include "tang/astNodeAssign.hpp"
#include "tang/astNodeBinary.hpp"
#include "tang/astNodeBoolean.hpp"
#include "tang/astNodeBreak.hpp"
#include "tang/astNodeCast.hpp"
#include "tang/astNodeContinue.hpp"
#include "tang/astNodeDoWhile.hpp"
#include "tang/astNodeFloat.hpp"
#include "tang/astNodeFor.hpp"
#include "tang/astNodeFunctionCall.hpp"
#include "tang/astNodeFunctionDeclaration.hpp"
#include "tang/astNode.hpp"
#include "tang/astNodeIdentifier.hpp"
#include "tang/astNodeIfElse.hpp"
#include "tang/astNodeIndex.hpp"
#include "tang/astNodeInteger.hpp"
#include "tang/astNodeLibrary.hpp"
#include "tang/astNodeMap.hpp"
#include "tang/astNodePeriod.hpp"
#include "tang/astNodePrint.hpp"
#include "tang/astNodeRangedFor.hpp"
#include "tang/astNodeReturn.hpp"
#include "tang/astNodeSlice.hpp"
#include "tang/astNodeString.hpp"
#include "tang/astNodeTernary.hpp"
#include "tang/astNodeUnary.hpp"
#include "tang/astNodeUse.hpp"
#include "tang/astNodeWhile.hpp"
#include "tang/computedExpressionArray.hpp"
#include "tang/computedExpressionBoolean.hpp"
#include "tang/computedExpressionCompiledFunction.hpp"
#include "tang/computedExpressionError.hpp"
#include "tang/computedExpressionFloat.hpp"
#include "tang/computedExpression.hpp"
#include "tang/computedExpressionInteger.hpp"
#include "tang/computedExpressionIteratorEnd.hpp"
#include "tang/computedExpressionIterator.hpp"
#include "tang/computedExpressionLibrary.hpp"
#include "tang/computedExpressionLibraryMath.hpp"
#include "tang/computedExpressionLibraryTang.hpp"
#include "tang/computedExpressionMap.hpp"
#include "tang/computedExpressionNativeBoundFunction.hpp"
#include "tang/computedExpressionNativeFunction.hpp"
#include "tang/computedExpressionNativeLibraryFunction.hpp"
#include "tang/computedExpressionString.hpp"
#include "tang/context.hpp"
#include "tang/error.hpp"
#include "tang/htmlEscapeAscii.hpp"
#include "tang/htmlEscape.hpp"
#include "tang/macros.hpp"
#include "tang/opcode.hpp"
#include "tang/percentEncode.hpp"
#include "tang/program.hpp"
#include "tang/tangBase.hpp"
#include "tang/tangScanner.hpp"
#include "tang/unescape.hpp"
#include "tang/unicodeString.hpp"

#endif // TANG_HPP

