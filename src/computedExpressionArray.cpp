/**
 * @file
 * Define the Tang::ComputedExpressionArray class.
 */

#include "computedExpressionArray.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionIterator.hpp"
#include "computedExpressionIteratorEnd.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionArray::ComputedExpressionArray(vector<GarbageCollected> contents) : contents{contents} {}

string ComputedExpressionArray::dump() const {
  string s = "[";
  bool isFirst = true;
  for (auto & item : this->contents) {
    if (!isFirst) {
      s += ",";
    }
    s += item->__asCode();
    isFirst = false;
  }
  s += "]";
  return s;
}

bool ComputedExpressionArray::isCopyNeeded() const {
  return true;
}

GarbageCollected ComputedExpressionArray::makeCopy() const {
  // Make a deep copy of all array elements.
  vector<GarbageCollected> newContents;
  newContents.reserve(this->contents.size());
  for (auto const & item : this->contents) {
    newContents.push_back(item->isCopyNeeded()
      ? item->makeCopy()
      : item);
  }
  return GarbageCollected::make<ComputedExpressionArray>(newContents);
}

GarbageCollected ComputedExpressionArray::__index(const GarbageCollected & index) const {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.val;
    return (i >= 0)
      // index >= 0
      ? i < (integer_t)this->contents.size()
        ? this->contents[i]
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."})
      // index < 0
      : -i <= (integer_t)this->contents.size()
        ? this->contents[this->contents.size() + i]
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."});
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Invalid index value."});
}

GarbageCollected ComputedExpressionArray::__slice(const GarbageCollected & begin, const GarbageCollected & end, const GarbageCollected & skip) const {
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
    convBegin = convSkip > 0 ? 0 : this->contents.size() - 1;
   }
  else if (typeid(*begin) == typeid(ComputedExpressionInteger)) {
    // Begin is an integer.
    convBegin = static_cast<ComputedExpressionInteger&>(*begin).val;
    convBegin = (convBegin >= 0)
      ? convBegin
      : this->contents.size() + convBegin;
  }
  else {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }

  // Verify that the end is either default or an integer.
  if (typeid(*end) == typeid(ComputedExpression)) {
    // End is a default value.
    convEnd = convSkip > 0 ? this->contents.size() : -1;
   }
  else if (typeid(*end) == typeid(ComputedExpressionInteger)) {
    // End is an integer.
    convEnd = static_cast<ComputedExpressionInteger&>(*end).val;
    convEnd = (convEnd >= 0)
      ? convEnd
      : this->contents.size() + convEnd;
  }
  else {
    return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
  }

  // The new target container.
  vector<GarbageCollected> newContents;

  // Skip is positive.
  if (convSkip > 0) {
    for (int i = max(0, convBegin); i < (int)this->contents.size() && i < convEnd; i += convSkip) {
      auto & item = this->contents.at(i);
      newContents.push_back(item->isCopyNeeded() ? item->makeCopy() : item);
    }
    return GarbageCollected::make<ComputedExpressionArray>(newContents);
  }

  // Skip is negative.
  for (int i = min((int)this->contents.size() - 1, convBegin); i >= 0 && i > convEnd; i += convSkip) {
    auto & item = this->contents.at(i);
    newContents.push_back(item->isCopyNeeded() ? item->makeCopy() : item);
  }
  return GarbageCollected::make<ComputedExpressionArray>(newContents);

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
}

GarbageCollected ComputedExpressionArray::__getIterator(const GarbageCollected & collection) const {
  return GarbageCollected::make<ComputedExpressionIterator>(collection);
}

GarbageCollected ComputedExpressionArray::__iteratorNext(size_t index) const {
  if (index >= this->contents.size()) {
    return GarbageCollected::make<ComputedExpressionIteratorEnd>();
  }
  return this->contents[index];
}

GarbageCollected ComputedExpressionArray::__assign_index(const GarbageCollected & index, const GarbageCollected & value) {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.val;
    return (i >= 0)
      // index >= 0
      ? i < (integer_t)this->contents.size()
        ? this->contents[i] = value
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."})
      // index < 0
      : -i <= (integer_t)this->contents.size()
        ? this->contents[this->contents.size() + i] = value
        : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."});
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to assign this value to the index location."});
}

GarbageCollected ComputedExpressionArray::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->__asCode());
}

