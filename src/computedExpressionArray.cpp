/**
 * @file
 * Define the Tang::ComputedExpressionArray class.
 */

#include "computedExpressionArray.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
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

