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

ComputedExpressionMap::ComputedExpressionMap(map<string, SPCE> contents) : contents{contents} {}

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

SPCE ComputedExpressionMap::makeCopy() const {
  // Make a deep copy of all array elements.
  map<string, SPCE> newContents;
  for (auto & item : this->contents) {
    newContents.insert({item.first, item.second->isCopyNeeded()
      ? item.second->makeCopy()
      : item.second});
  }
  return make_shared<ComputedExpressionMap>(newContents);
}

SPCE ComputedExpressionMap::__getIterator(const SPCE & collection) const {
  return make_shared<ComputedExpressionIterator>(collection);
}

SPCE ComputedExpressionMap::__iteratorNext(size_t index) const {
  if (index >= this->contents.size()) {
    return make_shared<ComputedExpressionIteratorEnd>();
  }
  auto iter{this->contents.begin()};
  size_t i{0};
  while (i < index) {
    ++i;
    ++iter;
  }

  return make_shared<ComputedExpressionArray>(
    vector<SPCE> {
      make_shared<ComputedExpressionString>(iter->first),
      iter->second
    }
  );

}

SPCE ComputedExpressionMap::__index(const SPCE & index) const {
  if (typeid(*index) == typeid(ComputedExpressionString)) {
    auto & indexConv = static_cast<ComputedExpressionString&>(*index);
    auto s = indexConv.dump();
    if (indexConv.bytesLength()) {
      // index is not an empty string
      if (this->contents.count(s)) {
        return this->contents.at(s);
      }

      // index does not exist in map.
      return make_shared<ComputedExpressionError>(Error{"Index does not exist in map"});
    }
  }

  // Return the default error.
  return ComputedExpression::__index(index);
}

SPCE ComputedExpressionMap::__assign_index(const SPCE & index, const SPCE & value) {
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

SPCE ComputedExpressionMap::__string() const {
  return make_shared<ComputedExpressionString>(this->__asCode());
}
 
SPCE ComputedExpressionMap::__boolean() const {
  return make_shared<ComputedExpressionBoolean>(this->contents.size() != 0);
}

