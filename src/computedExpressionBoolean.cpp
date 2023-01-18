/**
 * @file
 * Define the Tang::ComputedExpressionBoolean class.
 */

#include "computedExpressionBoolean.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionBoolean::ComputedExpressionBoolean(bool val) : val{val} {}

string ComputedExpressionBoolean::dump() const {
  return this->val ? "true" : "false";
}

SPCE ComputedExpressionBoolean::makeCopy() const {
  return make_shared<ComputedExpressionBoolean>(this->val);
}

bool ComputedExpressionBoolean::is_equal(const bool & val) const {
  return this->val == val;
}

SPCE ComputedExpressionBoolean::__not() const {
  return make_shared<ComputedExpressionBoolean>(!this->val);
}

SPCE ComputedExpressionBoolean::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionBoolean)) {
    auto & rhsConv = static_cast<ComputedExpressionBoolean &>(*rhs);
    return make_shared<ComputedExpressionBoolean>(this->val == rhsConv.val);
  }

  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return make_shared<ComputedExpressionBoolean>(false);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

SPCE ComputedExpressionBoolean::__integer() const {
  return make_shared<ComputedExpressionInteger>(this->val ? 1 : 0);
}

SPCE ComputedExpressionBoolean::__float() const {
  return make_shared<ComputedExpressionFloat>(this->val ? (float_t)1. : 0);
}

SPCE ComputedExpressionBoolean::__boolean() const {
  return make_shared<ComputedExpressionBoolean>(this->val);
}

