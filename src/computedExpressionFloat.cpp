/**
 * @file
 * Define the Tang::ComputedExpressionFloat class.
 */

#include "computedExpressionFloat.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionFloat::ComputedExpressionFloat(float_t val) : val{val} {}

string ComputedExpressionFloat::dump() const {
  return to_string(this->val);
}

GarbageCollected ComputedExpressionFloat::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionFloat>(this->val);
}

bool ComputedExpressionFloat::is_equal(const integer_t & val) const {
  return (float)val == this->val;
}

bool ComputedExpressionFloat::is_equal(const float_t & val) const {
  return val == this->val;
}

bool ComputedExpressionFloat::is_equal(const bool & val) const {
  return val == (bool)this->val;
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
        this->val + rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__add(rhs);
}

GarbageCollected ComputedExpressionFloat::__subtract(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val - rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val - rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__subtract(rhs);
}

GarbageCollected ComputedExpressionFloat::__multiply(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val * rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val * rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__multiply(rhs);
}

GarbageCollected ComputedExpressionFloat::__divide(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    if (rhsConv.val == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val / rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.getValue() == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val / rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__divide(rhs);
}

GarbageCollected ComputedExpressionFloat::__negative() const {
  return GarbageCollected::make<ComputedExpressionFloat>(-this->val);
}

GarbageCollected ComputedExpressionFloat::__not() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(!this->val);
}

GarbageCollected ComputedExpressionFloat::__lessThan(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val < rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val < rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__lessThan(rhs);
}

GarbageCollected ComputedExpressionFloat::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val == rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val == rhsConv.getValue());
  }

  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

GarbageCollected ComputedExpressionFloat::__integer() const {
  return GarbageCollected::make<ComputedExpressionInteger>((integer_t)this->val);
}

GarbageCollected ComputedExpressionFloat::__float() const {
  return GarbageCollected::make<ComputedExpressionFloat>(this->val);
}

GarbageCollected ComputedExpressionFloat::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>((bool)this->val);
}

GarbageCollected ComputedExpressionFloat::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->dump());
}

Tang::float_t ComputedExpressionFloat::getValue() const {
  return this->val;
}

