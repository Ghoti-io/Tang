/**
 * @file
 * Define the Tang::ComputedExpressionNull class.
 */

#include "computedExpressionNull.hpp"
#include "computedExpressionBoolean.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionNull::ComputedExpressionNull() {}

string ComputedExpressionNull::dump() const {
  return "NULL";
}

ComputedExpression * ComputedExpressionNull::makeCopy() const {
  return new ComputedExpressionNull();
}

bool ComputedExpressionNull::is_equal([[maybe_unused]] const nullptr_t & val) const {
  return true;
}

GarbageCollected ComputedExpressionNull::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNull)) {
    return GarbageCollected::make<ComputedExpressionBoolean>(true);
  }
  return GarbageCollected::make<ComputedExpressionBoolean>(false);
}

