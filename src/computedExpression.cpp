/**
 * @file
 * Define the Tang::ComputedExpression class.
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

bool ComputedExpression::is_equal([[maybe_unused]] const Error & val) const {
  return false;
}

GarbageCollected ComputedExpression::__add([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

GarbageCollected ComputedExpression::__subtract([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to subtract these values."});
}

GarbageCollected ComputedExpression::__multiply([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to multiply these values."});
}

GarbageCollected ComputedExpression::__divide([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to divide these values."});
}

GarbageCollected ComputedExpression::__modulo([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to modulo these values."});
}

GarbageCollected ComputedExpression::__negative() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to negate this value."});
}

GarbageCollected ComputedExpression::__integer() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to an integer."});
}

GarbageCollected ComputedExpression::__float() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a float."});
}

