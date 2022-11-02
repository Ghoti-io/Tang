/**
 * @file
 * Define the Tang::ComputedExpressionBoolean class.
 */

#include "computedExpressionNull.hpp"
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

GarbageCollected ComputedExpressionBoolean::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(this->val);
}

bool ComputedExpressionBoolean::is_equal(const bool & val) const {
  return this->val == val;
}

GarbageCollected ComputedExpressionBoolean::__not() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(!this->val);
}

GarbageCollected ComputedExpressionBoolean::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionBoolean)) {
    auto & rhsConv = static_cast<ComputedExpressionBoolean &>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(this->val == rhsConv.val);
  }

  if (typeid(*rhs) == typeid(ComputedExpressionNull)) {
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpressionBoolean::__integer() const {
  return GarbageCollected::make<ComputedExpressionInteger>(this->val ? 1 : 0);
}

GarbageCollected ComputedExpressionBoolean::__float() const {
  return GarbageCollected::make<ComputedExpressionFloat>(this->val ? 1. : 0);
}

GarbageCollected ComputedExpressionBoolean::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(this->val);
}

