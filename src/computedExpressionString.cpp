/**
 * @file
 * Define the Tang::ComputedExpressionString class.
 */

#include "computedExpressionString.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionString::ComputedExpressionString(string val) : val{val} {}

string ComputedExpressionString::dump() const {
  return this->val;
}

GarbageCollected ComputedExpressionString::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionString>(this->val);
}

bool ComputedExpressionString::is_equal(const bool & val) const {
  return val == (bool)this->val.bytesLength();
}

bool ComputedExpressionString::is_equal(const string & val) const {
  return val == this->val;
}

GarbageCollected ComputedExpressionString::__add(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);
    return GarbageCollected::make<ComputedExpressionString>(
        this->val + rhsConv.val);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

GarbageCollected ComputedExpressionString::__not() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(!this->val.bytesLength());
}

GarbageCollected ComputedExpressionString::__lessThan(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val < rhsConv.val);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpressionString::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->val == rhsConv.val);
  }
  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return GarbageCollected::make<ComputedExpressionBoolean>(false);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

GarbageCollected ComputedExpressionString::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>((bool)this->val.bytesLength());
}

GarbageCollected ComputedExpressionString::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->val);
}

