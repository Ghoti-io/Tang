/**
 * @file
 * Define the Tang::Context class.
 */

#include "context.hpp"
#include "program.hpp"
#include "computedExpression.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

Context::Context(ContextData && data) : data{move(data)}, computedExpressionOut{make_shared<ComputedExpressionString>("")}, result{make_shared<ComputedExpression>()} {}

