/**
 * @file
 * Define the Tang::ComputedExpressionInteger class.
 */

#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionInteger::ComputedExpressionInteger(integer_t val) : val{val} {}

string ComputedExpressionInteger::dump() const {
  return to_string(this->val);
}

SPCE ComputedExpressionInteger::makeCopy() const {
  return make_shared<ComputedExpressionInteger>(this->val);
}

bool ComputedExpressionInteger::is_equal(const integer_t & val) const {
  return val == this->val;
}

bool ComputedExpressionInteger::is_equal(const float_t & val) const {
  return val == (float_t)this->val;
}

bool ComputedExpressionInteger::is_equal(const bool & val) const {
  return val == (bool)this->val;
}

SPCE ComputedExpressionInteger::__add(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionInteger>(
        this->val + rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val + rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__add(rhs);
}

SPCE ComputedExpressionInteger::__subtract(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionInteger>(
        this->val - rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val - rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__subtract(rhs);
}

SPCE ComputedExpressionInteger::__multiply(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionInteger>(
        this->val * rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionFloat>(
        this->val * rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__multiply(rhs);
}

SPCE ComputedExpressionInteger::__divide(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.val == 0) {
      return make_shared<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return make_shared<ComputedExpressionInteger>(
        this->val / rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    if (rhsConv.getValue() == 0) {
      return make_shared<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return make_shared<ComputedExpressionFloat>(
        this->val / rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__divide(rhs);
}

SPCE ComputedExpressionInteger::__modulo(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.val == 0) {
      return make_shared<ComputedExpressionError>(Error{"Cannot modulo by zero."});
    }
    return make_shared<ComputedExpressionInteger>(
        this->val % rhsConv.val);
  }

  // Return the default error.
  return ComputedExpression::__modulo(rhs);
}

SPCE ComputedExpressionInteger::__negative() const {
  return make_shared<ComputedExpressionInteger>(-this->val);
}

SPCE ComputedExpressionInteger::__not() const {
  return make_shared<ComputedExpressionBoolean>(!this->val);
}

SPCE ComputedExpressionInteger::__lessThan(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val < rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val < rhsConv.getValue());
  }

  // Return the default error.
  return ComputedExpression::__lessThan(rhs);
}

SPCE ComputedExpressionInteger::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val == rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->val == rhsConv.getValue());
  }

  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return make_shared<ComputedExpressionBoolean>(false);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

SPCE ComputedExpressionInteger::__integer() const {
  return make_shared<ComputedExpressionInteger>(this->val);
}

SPCE ComputedExpressionInteger::__float() const {
  return make_shared<ComputedExpressionFloat>((float_t)this->val);
}

SPCE ComputedExpressionInteger::__boolean() const {
  return make_shared<ComputedExpressionBoolean>((bool)this->val);
}

SPCE ComputedExpressionInteger::__string() const {
  return make_shared<ComputedExpressionString>(this->dump());
}

Tang::integer_t ComputedExpressionInteger::getValue() const {
  return this->val;
}

