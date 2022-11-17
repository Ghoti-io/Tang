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
      s += ", ";
    }
    s += item->dump();
    isFirst = false;
  }
  s += "]";
  return s;
}

GarbageCollected ComputedExpressionArray::makeCopy() const {
  // TODO Should this be a deep copy?
  return GarbageCollected::make<ComputedExpressionArray>(this->contents);
}

GarbageCollected ComputedExpressionArray::__index(const GarbageCollected & index) const {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.val;
    return (i >= 0) && (i < (integer_t)this->contents.size())
      ? this->contents[i]
      : GarbageCollected::make<ComputedExpressionError>(Error{"Index out of range."});
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Invalid index value."});
}

