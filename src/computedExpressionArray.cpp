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

ComputedExpressionArray::ComputedExpressionArray(vector<SPCE> contents) : contents{contents} {}

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

SPCE ComputedExpressionArray::makeCopy() const {
  // Make a deep copy of all array elements.
  vector<SPCE> newContents;
  newContents.reserve(this->contents.size());
  for (auto const & item : this->contents) {
    newContents.push_back(item->isCopyNeeded()
      ? item->makeCopy()
      : item);
  }
  return make_shared<ComputedExpressionArray>(newContents);
}

SPCE ComputedExpressionArray::__index(const SPCE & index) const {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.getValue();
    return (i >= 0)
      // index >= 0
      ? i < (integer_t)this->contents.size()
        ? this->contents[i]
        : make_shared<ComputedExpressionError>(Error{"Index out of range."})
      // index < 0
      : -i <= (integer_t)this->contents.size()
        ? this->contents[this->contents.size() + i]
        : make_shared<ComputedExpressionError>(Error{"Index out of range."});
  }

  // Return the default error.
  return ComputedExpression::__index(index);
}

SPCE ComputedExpressionArray::__slice(const SPCE & begin, const SPCE & end, const SPCE & skip) const {
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
    convBegin = convSkip > 0 ? 0 : this->contents.size() - 1;
   }
  else if (typeid(*begin) == typeid(ComputedExpressionInteger)) {
    // Begin is an integer.
    convBegin = static_cast<ComputedExpressionInteger&>(*begin).getValue();
    convBegin = (convBegin >= 0)
      ? convBegin
      : this->contents.size() + convBegin;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // Verify that the end is either default or an integer.
  if (typeid(*end) == typeid(ComputedExpression)) {
    // End is a default value.
    convEnd = convSkip > 0 ? this->contents.size() : -1;
   }
  else if (typeid(*end) == typeid(ComputedExpressionInteger)) {
    // End is an integer.
    convEnd = static_cast<ComputedExpressionInteger&>(*end).getValue();
    convEnd = (convEnd >= 0)
      ? convEnd
      : this->contents.size() + convEnd;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // The new target container.
  vector<SPCE> newContents;

  // Skip is positive.
  if (convSkip > 0) {
    for (int i = max(0, convBegin); i < (int)this->contents.size() && i < convEnd; i += convSkip) {
      auto & item = this->contents.at(i);
      newContents.push_back(item->isCopyNeeded() ? item->makeCopy() : item);
    }
    return make_shared<ComputedExpressionArray>(newContents);
  }

  // Skip is negative.
  for (int i = min((int)this->contents.size() - 1, convBegin); i >= 0 && i > convEnd; i += convSkip) {
    auto & item = this->contents.at(i);
    newContents.push_back(item->isCopyNeeded() ? item->makeCopy() : item);
  }

  return make_shared<ComputedExpressionArray>(newContents);
}

SPCE ComputedExpressionArray::__getIterator(const SPCE & collection) const {
  return make_shared<ComputedExpressionIterator>(collection);
}

SPCE ComputedExpressionArray::__iteratorNext(size_t index) const {
  if (index >= this->contents.size()) {
    return make_shared<ComputedExpressionIteratorEnd>();
  }
  return this->contents[index];
}

SPCE ComputedExpressionArray::__assign_index(const SPCE & index, const SPCE & value) {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.getValue();
    return (i >= 0)
      // index >= 0
      ? i < (integer_t)this->contents.size()
        ? this->contents[i] = value
        : make_shared<ComputedExpressionError>(Error{"Index out of range."})
      // index < 0
      : -i <= (integer_t)this->contents.size()
        ? this->contents[this->contents.size() + i] = value
        : make_shared<ComputedExpressionError>(Error{"Index out of range."});
  }

  // Return the default error.
  return ComputedExpression::__assign_index(index, value);
}

SPCE ComputedExpressionArray::__string() const {
  return make_shared<ComputedExpressionString>(this->__asCode());
}

const std::vector<Tang::SPCE> & ComputedExpressionArray::getContents() const {
  return this->contents;
}

void ComputedExpressionArray::append(const SPCE & item) {
  this->contents.push_back(item);
}

NativeBoundFunctionMap ComputedExpressionArray::getMethods() {
  return {
    {"length", {0, [](SPCE & target, [[maybe_unused]] vector<SPCE>& args) -> SPCE {
      return make_shared<ComputedExpressionInteger>((integer_t)static_cast<ComputedExpressionArray&>(*target).getContents().size());
    }}},
    {"append", {1, [](SPCE & target, vector<SPCE>& args) -> SPCE {
      // Get the item to be added to the array.
      auto & item = args.at(0);
      static_cast<ComputedExpressionArray &>(*target).append(item);
      return target;
    }}},
  };
}

