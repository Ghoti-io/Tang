/**
 * @file
 */

#include "computedExpression.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpression::~ComputedExpression() {}

string ComputedExpression::dump() const {
  return "";
}

ComputedExpression * ComputedExpression::makeCopy() const {
  return new ComputedExpression();
}

bool ComputedExpression::is_equal([[maybe_unused]] const int & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const double & val) const {
  return false;
}

GarbageCollected ComputedExpression::__add([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

