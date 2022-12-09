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
    auto i = indexConv.getValue();
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

  // Return the default error.
  return ComputedExpression::__index(index);
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
    convSkip = static_cast<ComputedExpressionInteger&>(*skip).getValue();
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }
  // Verify that the skip is not 0.
  if (!convSkip) {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // Verify that the begin is either default or an integer.
  if (typeid(*begin) == typeid(ComputedExpression)) {
    // Begin is a default value.
    convBegin = convSkip > 0 ? 0 : this->val.length() - 1;
   }
  else if (typeid(*begin) == typeid(ComputedExpressionInteger)) {
    // Begin is an integer.
    convBegin = static_cast<ComputedExpressionInteger&>(*begin).getValue();
    convBegin = (convBegin >= 0)
      ? convBegin
      : this->val.length() + convBegin;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // Verify that the end is either default or an integer.
  if (typeid(*end) == typeid(ComputedExpression)) {
    // End is a default value.
    convEnd = convSkip > 0 ? this->val.length() : -1;
   }
  else if (typeid(*end) == typeid(ComputedExpressionInteger)) {
    // End is an integer.
    convEnd = static_cast<ComputedExpressionInteger&>(*end).getValue();
    convEnd = (convEnd >= 0)
      ? convEnd
      : this->val.length() + convEnd;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
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

  // Return the default error.
  return ComputedExpression::__slice(begin, end, skip);
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

  // Return the default error.
  return ComputedExpression::__add(rhs);
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

  // Return the default error.
  return ComputedExpression::__lessThan(rhs);
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

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

GarbageCollected ComputedExpressionString::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>((bool)this->val.bytesLength());
}

GarbageCollected ComputedExpressionString::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->val);
}

UnicodeString ComputedExpressionString::getValue() const {
  return this->val;
}

NativeBoundFunctionMap ComputedExpressionString::getMethods() {
  return {
    {"length", [](GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
      if (typeid(*target) == typeid(ComputedExpressionString)) {
        return GarbageCollected::make<ComputedExpressionInteger>((integer_t)static_cast<ComputedExpressionString &>(*target).getValue().length());
      }
      return GarbageCollected::make<ComputedExpressionError>(Error{""});
    }},
  };
}

