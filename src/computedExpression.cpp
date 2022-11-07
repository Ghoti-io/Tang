/**
 * @file
 * Define the Tang::ComputedExpression class.
 */

#include "computedExpression.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpression::~ComputedExpression() {}

string ComputedExpression::dump() const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? "NULL"
    : "UNKNOWN";
}

GarbageCollected ComputedExpression::makeCopy() const {
  return GarbageCollected::make<ComputedExpression>();
}

bool ComputedExpression::is_equal([[maybe_unused]] const int & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const double & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const bool & val) const {
  return typeid(*this) == typeid(ComputedExpression)
    ? val == false
    : false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const string & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const nullptr_t & val) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? true
    : false;
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

GarbageCollected ComputedExpression::__not() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compute the logical not of this value."});
}

GarbageCollected ComputedExpression::__lessThan([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpression::__equal([[maybe_unused]] const GarbageCollected & rhs) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  if (typeid(*this) == typeid(ComputedExpression)) {
    if (typeid(*rhs) == typeid(ComputedExpression)) {
      return GarbageCollected::make<ComputedExpressionBoolean>(true);
    }
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpression::__integer() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to an integer."});
}

GarbageCollected ComputedExpression::__float() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a float."});
}

GarbageCollected ComputedExpression::__boolean() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a boolean."});
}

GarbageCollected ComputedExpression::__string() const {
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to cast this value to a string."});
}

