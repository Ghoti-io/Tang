/**
 * @file
 */

#include "computedExpression.hpp"

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
  // TODO Return an error.
  return GarbageCollected::make<ComputedExpressionInteger>(0);
}

ComputedExpressionInteger::ComputedExpressionInteger(int64_t val) : val{val} {}

string ComputedExpressionInteger::dump() const {
  return to_string(this->val);
}

ComputedExpression * ComputedExpressionInteger::makeCopy() const {
  return new ComputedExpressionInteger(this->val);
}

bool ComputedExpressionInteger::is_equal(const int & val) const {
  return val == this->val;
}

bool ComputedExpressionInteger::is_equal(const double & val) const {
  return val == (double)this->val;
}

GarbageCollected ComputedExpressionInteger::__add(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val + rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val + rhsConv.val);
  }

  // TODO Return an error.
  return GarbageCollected::make<ComputedExpressionInteger>(0);
}

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

GarbageCollected ComputedExpressionFloat::__add([[maybe_unused]] const GarbageCollected & rhs) const {
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

  // TODO Return an error.
  return GarbageCollected::make<ComputedExpressionInteger>(0);
}

