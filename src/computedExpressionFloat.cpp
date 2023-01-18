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

SPCE ComputedExpressionFloat::makeCopy() const {
  return make_shared<ComputedExpressionFloat>(this->val);
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

SPCE ComputedExpressionFloat::__add(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val + rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val + rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__add(rhs);
}

SPCE ComputedExpressionFloat::__subtract(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val - rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val - rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__subtract(rhs);
}

SPCE ComputedExpressionFloat::__multiply(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val * rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val * rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__multiply(rhs);
}

SPCE ComputedExpressionFloat::__divide(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    if (rhsConv.val == 0) {
      return make_shared<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return make_shared<ComputedExpressionFloat>(
        this->val / rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.getValue() == 0) {
      return make_shared<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return make_shared<ComputedExpressionFloat>(
        this->val / rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__divide(rhs);
}

SPCE ComputedExpressionFloat::__negative() const {
  return make_shared<ComputedExpressionFloat>(-this->val);
}

SPCE ComputedExpressionFloat::__not() const {
  return make_shared<ComputedExpressionBoolean>(!this->val);
}

SPCE ComputedExpressionFloat::__lessThan(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val < rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val < rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__lessThan(rhs);
}

SPCE ComputedExpressionFloat::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val == rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val == rhsConv.getValue());
  }

  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return make_shared<ComputedExpressionBoolean>(false);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

SPCE ComputedExpressionFloat::__integer() const {
  return make_shared<ComputedExpressionInteger>((integer_t)this->val);
}

SPCE ComputedExpressionFloat::__float() const {
  return make_shared<ComputedExpressionFloat>(this->val);
}

SPCE ComputedExpressionFloat::__boolean() const {
  return make_shared<ComputedExpressionBoolean>((bool)this->val);
}

SPCE ComputedExpressionFloat::__string() const {
  return make_shared<ComputedExpressionString>(this->dump());
}

Tang::float_t ComputedExpressionFloat::getValue() const {
  return this->val;
}

