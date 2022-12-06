/**
 * @file
 * Define the Tang::ComputedExpressionString class.
 */

#include "computedExpressionString.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionIterator.hpp"
#include "computedExpressionIteratorEnd.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionString::ComputedExpressionString(string val) : val{val} {}

string ComputedExpressionString::dump() const {
  return this->val;
}

string ComputedExpressionString::__asCode() const {
  return (UnicodeString)"\"" + unescape(this->val) + (UnicodeString)"\"";
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

GarbageCollected ComputedExpressionString::__index(const GarbageCollected & index) const {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.val;
    return (i >= 0)
      // index >= 0
      ? i < (integer_t)this->val.length()
        ? GarbageCollected::make<ComputedExpressionString>(this->val.substr(i, 1))
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."})
      // index < 0
      : -i <= (integer_t)this->val.length()
        ? GarbageCollected::make<ComputedExpressionString>(this->val.substr(this->val.length() + i, 1))
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."});
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Invalid index value."});
}

GarbageCollected ComputedExpressionString::__slice(const GarbageCollected & begin, const GarbageCollected & end, const GarbageCollected & skip) const {
  int convBegin, convEnd, convSkip;

  // Verify that the skip is either default or an integer.
  if (typeid(*skip) == typeid(ComputedExpression)) {
    // Skip is a default value.
    convSkip = 1;
  }
  else if (typeid(*skip) == typeid(ComputedExpressionInteger)) {
    // Skip is an integer.
    convSkip = static_cast<ComputedExpressionInteger&>(*skip).val;
  }
  else {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }
  // Verify that the skip is not 0.
  if (!convSkip) {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }

  // Verify that the begin is either default or an integer.
  if (typeid(*begin) == typeid(ComputedExpression)) {
    // Begin is a default value.
    convBegin = convSkip > 0 ? 0 : this->val.length() - 1;
   }
  else if (typeid(*begin) == typeid(ComputedExpressionInteger)) {
    // Begin is an integer.
    convBegin = static_cast<ComputedExpressionInteger&>(*begin).val;
    convBegin = (convBegin >= 0)
      ? convBegin
      : this->val.length() + convBegin;
  }
  else {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }

  // Verify that the end is either default or an integer.
  if (typeid(*end) == typeid(ComputedExpression)) {
    // End is a default value.
    convEnd = convSkip > 0 ? this->val.length() : -1;
   }
  else if (typeid(*end) == typeid(ComputedExpressionInteger)) {
    // End is an integer.
    convEnd = static_cast<ComputedExpressionInteger&>(*end).val;
    convEnd = (convEnd >= 0)
      ? convEnd
      : this->val.length() + convEnd;
  }
  else {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }

  // The new target container.
  string newString;

  // Skip is positive.
  if (convSkip > 0) {
    for (int i = max(0, convBegin); i < (int)this->val.length() && i < convEnd; i += convSkip) {
      newString += this->val.substr(i, 1);
    }
    return GarbageCollected::make<ComputedExpressionString>(newString);
  }

  // Skip is negative.
  for (int i = min((int)this->val.length() - 1, convBegin); i >= 0 && i > convEnd; i += convSkip) {
    newString += this->val.substr(i, 1);
  }
  return GarbageCollected::make<ComputedExpressionString>(newString);

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
}

GarbageCollected ComputedExpressionString::__getIterator(const GarbageCollected & collection) const {
  return GarbageCollected::make<ComputedExpressionIterator>(collection);
}

GarbageCollected ComputedExpressionString::__iteratorNext(size_t index) const {
  if (index >= this->val.length()) {
    return GarbageCollected::make<ComputedExpressionIteratorEnd>();
  }
  return GarbageCollected::make<ComputedExpressionString>(this->val.substr(index, 1));
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

