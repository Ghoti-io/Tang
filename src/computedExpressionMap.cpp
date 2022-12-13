/**
 * @file
 * Define the Tang::ComputedExpressionMap class.
 */

#include "computedExpressionMap.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionIterator.hpp"
#include "computedExpressionIteratorEnd.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionMap::ComputedExpressionMap(map<string, GarbageCollected> contents) : contents{contents} {}

string ComputedExpressionMap::dump() const {
  string s = "{";
  bool isFirst = true;
  for (auto & item : this->contents) {
    if (!isFirst) {
      s += ",";
    }
    s += item.first + ":" + item.second->__asCode();
    isFirst = false;
  }
  s += "}";
  return s;
}

bool ComputedExpressionMap::isCopyNeeded() const {
  return true;
}

GarbageCollected ComputedExpressionMap::makeCopy() const {
  // Make a deep copy of all array elements.
  map<string, GarbageCollected> newContents;
  for (auto & item : this->contents) {
    newContents.insert({item.first, item.second->isCopyNeeded()
      ? item.second->makeCopy()
      : item.second});
  }
  return GarbageCollected::make<ComputedExpressionMap>(newContents);
}

GarbageCollected ComputedExpressionMap::__getIterator(const GarbageCollected & collection) const {
  return GarbageCollected::make<ComputedExpressionIterator>(collection);
}

GarbageCollected ComputedExpressionMap::__iteratorNext(size_t index) const {
  if (index >= this->contents.size()) {
    return GarbageCollected::make<ComputedExpressionIteratorEnd>();
  }
  auto iter{this->contents.begin()};
  size_t i{0};
  while (i < index) {
    ++i;
    ++iter;
  }

  return GarbageCollected::make<ComputedExpressionArray>(
    vector<GarbageCollected> {
      GarbageCollected::make<ComputedExpressionString>(iter->first),
      iter->second
    }
  );

}

GarbageCollected ComputedExpressionMap::__index(const GarbageCollected & index) const {
  if (typeid(*index) == typeid(ComputedExpressionString)) {
    auto & indexConv = static_cast<ComputedExpressionString&>(*index);
    auto s = indexConv.dump();
    if (indexConv.bytesLength()) {
      // index is not an empty string
      if (this->contents.count(s)) {
        return this->contents.at(s);
      }

      // index does not exist in map.
      return GarbageCollected::make<ComputedExpressionError>(Error{"Index does not exist in map"});
    }
  }

  // Return the default error.
  return ComputedExpression::__index(index);
}

GarbageCollected ComputedExpressionMap::__assign_index(const GarbageCollected & index, const GarbageCollected & value) {
  if (typeid(*index) == typeid(ComputedExpressionString)) {
    auto & indexConv = static_cast<ComputedExpressionString&>(*index);
    auto s = indexConv.dump();
    if (indexConv.bytesLength()) {
      this->contents.insert({s, value});
      return value;
    }
  }

  // Return the default error.
  return ComputedExpression::__assign_index(index, value);
}

GarbageCollected ComputedExpressionMap::__string() const {
  return GarbageCollected::make<ComputedExpressionString>(this->__asCode());
}
 
GarbageCollected ComputedExpressionMap::__boolean() const {
  return GarbageCollected::make<ComputedExpressionBoolean>(this->contents.size() != 0);
}

