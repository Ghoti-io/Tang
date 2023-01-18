/**
 * @file
 * Define the Tang::ComputedExpressionIteratorEnd class.
 */

#include "computedExpressionIteratorEnd.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionIteratorEnd::ComputedExpressionIteratorEnd() {}

string ComputedExpressionIteratorEnd::dump() const {
  return "IteratorEnd";
}

SPCE ComputedExpressionIteratorEnd::__string() const {
  return make_shared<ComputedExpressionString>("IteratorEnd");
}

