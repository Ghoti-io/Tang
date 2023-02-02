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

#include "astNodeArray.hpp"
#include "astNodeAssign.hpp"
#include "astNodeBinary.hpp"
#include "astNodeBoolean.hpp"
#include "astNodeBreak.hpp"
#include "astNodeCast.hpp"
#include "astNodeContinue.hpp"
#include "astNodeDoWhile.hpp"
#include "astNodeFloat.hpp"
#include "astNodeFor.hpp"
#include "astNodeFunctionCall.hpp"
#include "astNodeFunctionDeclaration.hpp"
#include "astNode.hpp"
#include "astNodeIdentifier.hpp"
#include "astNodeIfElse.hpp"
#include "astNodeIndex.hpp"
#include "astNodeInteger.hpp"
#include "astNodeLibrary.hpp"
#include "astNodeMap.hpp"
#include "astNodePeriod.hpp"
#include "astNodePrint.hpp"
#include "astNodeRangedFor.hpp"
#include "astNodeReturn.hpp"
#include "astNodeSlice.hpp"
#include "astNodeString.hpp"
#include "astNodeTernary.hpp"
#include "astNodeUnary.hpp"
#include "astNodeUse.hpp"
#include "astNodeWhile.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionCompiledFunction.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpression.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionIteratorEnd.hpp"
#include "computedExpressionIterator.hpp"
#include "computedExpressionLibrary.hpp"
#include "computedExpressionLibraryMath.hpp"
#include "computedExpressionLibraryTang.hpp"
#include "computedExpressionMap.hpp"
#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionNativeLibraryFunction.hpp"
#include "computedExpressionString.hpp"
#include "context.hpp"
#include "error.hpp"
#include "htmlEscapeAscii.hpp"
#include "htmlEscape.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "percentEncode.hpp"
#include "program.hpp"
#include "tangBase.hpp"
#include "tangScanner.hpp"
#include "unescape.hpp"
#include "unicodeString.hpp"

#endif // TANG_HPP

