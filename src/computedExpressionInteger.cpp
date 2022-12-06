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

GarbageCollected ComputedExpressionInteger::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionInteger>(this->val);
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

GarbageCollected ComputedExpressionInteger::__add(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val + rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val + rhsConv.getValue());
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

GarbageCollected ComputedExpressionInteger::__subtract(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val - rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val - rhsConv.getValue());
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

GarbageCollected ComputedExpressionInteger::__multiply(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val * rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val * rhsConv.getValue());
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to multiply these values."});
}

GarbageCollected ComputedExpressionInteger::__divide(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.val == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val / rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    if (rhsConv.getValue() == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val / rhsConv.getValue());
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to divide these values."});
}

GarbageCollected ComputedExpressionInteger::__modulo(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    if (rhsConv.val == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot modulo by zero."});
    }
    return GarbageCollected::make<ComputedExpressionInteger>(
        this->val % rhsConv.val);
  }
  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to modulo these values."});
}

GarbageCollected ComputedExpressionInteger::__negative() const {
  return GarbageCollected::make<ComputedExpressionInteger>(-this->val);
}

GarbageCollected ComputedExpressionInteger::__not() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(!this->val);
}

GarbageCollected ComputedExpressionInteger::__lessThan(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val < rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val < rhsConv.getValue());
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpressionInteger::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionInteger)) {
    auto & rhsConv = static_cast<ComputedExpressionInteger&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val == rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpressionFloat)) {
    auto & rhsConv = static_cast<ComputedExpressionFloat&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val == rhsConv.getValue());
  }

  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpressionInteger::__integer() const {
  return GarbageCollected::make<ComputedExpressionInteger>(this->val);
}

GarbageCollected ComputedExpressionInteger::__float() const {
  return GarbageCollected::make<ComputedExpressionFloat>((float_t)this->val);
}

GarbageCollected ComputedExpressionInteger::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>((bool)this->val);
}

GarbageCollected ComputedExpressionInteger::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->dump());
}

Tang::integer_t ComputedExpressionInteger::getValue() const {
  return this->val;
}

