/**
 * @file
 */

#include "computedExpressionFloat.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionFloat::ComputedExpressionFloat(double val) : val{val} {}

string ComputedExpressionFloat::dump() const {
  return to_string(this->val);
}

ComputedExpression * ComputedExpressionFloat::makeCopy() const {
  return new ComputedExpressionFloat(this->val);
}

bool ComputedExpressionFloat::is_equal(const int & val) const {
  return (float)val == this->val;
}

bool ComputedExpressionFloat::is_equal(const double & val) const {
  return val == this->val;
}

GarbageCollected ComputedExpressionFloat::__add(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val + rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val + rhsConv.val);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

