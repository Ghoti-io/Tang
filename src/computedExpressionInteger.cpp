/**
 * @file
 */

#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionInteger::ComputedExpressionInteger(int64_t val) : val{val} {}

string ComputedExpressionInteger::dump() const {
  return to_string(this->val);
}

ComputedExpression * ComputedExpressionInteger::makeCopy() const {
  return new ComputedExpressionInteger(this->val);
}

bool ComputedExpressionInteger::is_equal(const int & val) const {
  return val == this->val;
}

bool ComputedExpressionInteger::is_equal(const double & val) const {
  return val == (double)this->val;
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
        this->val + rhsConv.val);
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
        this->val - rhsConv.val);
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
        this->val * rhsConv.val);
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
    if (rhsConv.val == 0) {
      return GarbageCollected::make<ComputedExpressionError>(Error{"Cannot divide by zero."});
    }
    return GarbageCollected::make<ComputedExpressionFloat>(
        this->val / rhsConv.val);
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

GarbageCollected ComputedExpressionInteger::__integer() const {
  return GarbageCollected::make<ComputedExpressionInteger>(this->val);
}

GarbageCollected ComputedExpressionInteger::__float() const {
  return GarbageCollected::make<ComputedExpressionFloat>((double)this->val);
}

