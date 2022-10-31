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

ComputedExpression * ComputedExpressionBoolean::makeCopy() const {
  return new ComputedExpressionBoolean(this->val);
}

bool ComputedExpressionBoolean::is_equal(const bool & val) const {
  return this->val == val;
}

GarbageCollected ComputedExpressionBoolean::__not() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(!this->val);
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

