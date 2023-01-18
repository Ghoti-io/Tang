/**
 * @file
 * Define the Tang::ComputedExpressionString class.
 */

#include <algorithm>
#include "computedExpressionString.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionIterator.hpp"
#include "computedExpressionIteratorEnd.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionString::ComputedExpressionString(const string &val) {
  this->stringParts.push_back(UnicodeString{val});
}

ComputedExpressionString::ComputedExpressionString(const vector<UnicodeString> & stringParts) : stringParts{stringParts} {}

string ComputedExpressionString::dump() const {
  // Sanity check because many strings will only have one chunk.
  if (this->stringParts.size() == 1) {
    return this->stringParts.at(0).render();
  }

  string out{};
  for (auto & part : this->stringParts) {
    out += part.render();
  }
  return out;
}

string ComputedExpressionString::__asCode() const {
  string out{};
  for (auto & part : this->stringParts) {
    out += part;
  }
  return (UnicodeString)"\"" + unescape(out) + (UnicodeString)"\"";
}

SPCE ComputedExpressionString::makeCopy() const {
  return make_shared<ComputedExpressionString>(*this);
}

bool ComputedExpressionString::is_equal(const bool & val) const {
  return val == (bool)this->bytesLength();
}

bool ComputedExpressionString::is_equal(const string & val) const {
  return val == this->dump();
}

SPCE ComputedExpressionString::__index(const SPCE & index) const {
  if (typeid(*index) == typeid(ComputedExpressionInteger)) {
    auto & indexConv = static_cast<ComputedExpressionInteger&>(*index);
    auto i = indexConv.getValue();
    auto totalLength{this->length()};

    // Find the indexed grapheme.
    if (i >= 0) {
      // index >= 0.
      if (i < (integer_t)totalLength) {
        // Collect the string parts.
        integer_t count{0};
        for (auto & part : this->stringParts) {
          if (count + (integer_t)part.length() > i) {
            // The index grapheme is within the current part.
            vector<UnicodeString> newParts{};
            newParts.push_back(part.substr(i - count, 1));
            return make_shared<ComputedExpressionString>(newParts);
          }
          count += part.length();
        }
        // Impossible to get here.
      }
      return make_shared<ComputedExpressionError>(Error{"Index out of range."});
    }
    else {
      // index < 0.
      // Convert to an index from the beginning.
      i += totalLength;

      if (i >= 0) {
        // collect the string parts.
        integer_t count{0};
        for (auto & part : this->stringParts) {
          if (count + (integer_t)part.length() > i) {
            // The index grapheme is within the current part.
            vector<UnicodeString> newParts{};
            newParts.push_back(part.substr(i - count, 1));
            return make_shared<ComputedExpressionString>(newParts);
          }
          count += part.length();
        }
        // Impossible to get here.
      }
      return make_shared<ComputedExpressionError>(Error{"Index out of range."});
    }
  }

  // Return the default error.
  return ComputedExpression::__index(index);
}

SPCE ComputedExpressionString::__slice(const SPCE & begin, const SPCE & end, const SPCE & skip) const {
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

  // Compute the total length.
  integer_t totalLength{(integer_t)this->length()};

  // Verify that the begin is either default or an integer.
  if (typeid(*begin) == typeid(ComputedExpression)) {
    // Begin is a default value.
    convBegin = convSkip > 0 ? 0 : totalLength - 1;
   }
  else if (typeid(*begin) == typeid(ComputedExpressionInteger)) {
    // Begin is an integer.
    convBegin = static_cast<ComputedExpressionInteger&>(*begin).getValue();
    convBegin = (convBegin >= 0)
      ? convBegin
      : totalLength + convBegin;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // Verify that the end is either default or an integer.
  if (typeid(*end) == typeid(ComputedExpression)) {
    // End is a default value.
    convEnd = convSkip > 0 ? totalLength : -1;
   }
  else if (typeid(*end) == typeid(ComputedExpressionInteger)) {
    // End is an integer.
    convEnd = static_cast<ComputedExpressionInteger&>(*end).getValue();
    convEnd = (convEnd >= 0)
      ? convEnd
      : totalLength + convEnd;
  }
  else {
    // Return the default error.
    return ComputedExpression::__slice(begin, end, skip);
  }

  // The new target container.
  vector<UnicodeString> newParts;

  // Special case: skip is 1.
  if (convSkip == 1) {
    // Copy chunks at a time.
    // Collect the string parts.
    integer_t count{0};
    for (auto & part : this->stringParts) {
      if (count >= convEnd) {
        // There are no more parts to collect.
        break;
      }

      if (count >= convBegin) {
        // The beginning of this chunk will be included.
        // All or part of this chunk should be collected.
        if (count + (integer_t)part.length() <= convEnd) {
          // All of the chunk should be collected.
          newParts.push_back(part);
        }
        else {
          // Only part of the chunk should be collected.
          newParts.push_back(part.substr(0, convEnd - count));

          // No more chunks will be added.
          break;
        }
      }
      else {
        // The beginning of this chunk will *not* be included.
        // This chunk may need to be skipped or only partially included.
        if (count + (integer_t)part.length() < convBegin) {
          // This chunk should be skipped entirely.
          count += part.length();
          continue;
        }
        // The slice is starting in this chunk.
        newParts.push_back(part.substr(convBegin - count, convEnd - convBegin));
        count += part.length();
        continue;
      }

      count += part.length();
    }
    return make_shared<ComputedExpressionString>(newParts);
  }

  // Flag to indicate that the final results should be reversed.
  bool isReversed{convSkip < 0};

  int actualBegin{convBegin};
  int actualEnd{convEnd};
  int actualSkip{convSkip};
  if (isReversed) {
    // Compute exact begin and end values which can be used by the forward
    // algorithm and then later reversed.
    // Ex: [5:1:-3] will become [2:6:3], giving elements (2, 5), to be reversed
    // later.
    // [::-1], when the string has 3 graphemes, is equivalent to
    // [2:(0-1):-1], which is reversed to:
    // [0:3:1], to be reversed later.
    actualSkip = -actualSkip;
    std::swap(actualBegin, actualEnd);
    actualBegin = actualEnd - ((actualEnd - actualBegin - 1) / actualSkip * actualSkip);
    ++actualEnd;
  }

  // Range Sanity Checks
  actualBegin = max(actualBegin, 0);
  actualEnd = min(actualEnd, totalLength);

  // Perform the skip
  integer_t count{0};
  integer_t nextIndex{actualBegin};
  for (auto & part : this->stringParts) {
    while ((count + (integer_t)part.length() > nextIndex) && (nextIndex < actualEnd)) {
      // nextIndex is within the current chunk.
      newParts.push_back(part.substr(nextIndex - count, 1));
      nextIndex += actualSkip;
    }
    count += part.length();
  }

  // Reverse the parts, if required.
  if (isReversed) {
    reverse(newParts.begin(), newParts.end());
  }

  // Create the new string.
  return make_shared<ComputedExpressionString>(newParts);
}

SPCE ComputedExpressionString::__getIterator(const SPCE & collection) const {
  return make_shared<ComputedExpressionIterator>(collection);
}

SPCE ComputedExpressionString::__iteratorNext(size_t index) const {
  if (index >= this->length()) {
    return make_shared<ComputedExpressionIteratorEnd>();
  }
  return this->__index(make_shared<ComputedExpressionInteger>((integer_t)index));
}

SPCE ComputedExpressionString::__add(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);

    // Create a new vector to hold the concatenation.
    vector<UnicodeString>newParts{};
    newParts.reserve(this->stringParts.size() + rhsConv.stringParts.size());
    newParts.insert(newParts.end(), this->stringParts.begin(), this->stringParts.end());
    newParts.insert(newParts.end(), rhsConv.stringParts.begin(), rhsConv.stringParts.end());
    return make_shared<ComputedExpressionString>(newParts);
  }

  // Return the default error.
  return ComputedExpression::__add(rhs);
}

SPCE ComputedExpressionString::__not() const {
  return make_shared<ComputedExpressionBoolean>(!this->bytesLength());
}

SPCE ComputedExpressionString::__lessThan(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->dump() < rhsConv.dump());
  }

  // Return the default error.
  return ComputedExpression::__lessThan(rhs);
}

SPCE ComputedExpressionString::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionString)) {
    auto & rhsConv = static_cast<ComputedExpressionString&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(
        this->dump() == rhsConv.dump());
  }
  if (typeid(*rhs) == typeid(ComputedExpression)) {
    return make_shared<ComputedExpressionBoolean>(false);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

SPCE ComputedExpressionString::__boolean() const {
  return make_shared<ComputedExpressionBoolean>((bool)this->bytesLength());
}

SPCE ComputedExpressionString::__string() const {
  return make_shared<ComputedExpressionString>(*this);
}

const vector<UnicodeString>& ComputedExpressionString::getValue() const {
  return this->stringParts;
}

size_t ComputedExpressionString::length() const {
  // Return the cached length, if it exists.
  if (this->cachedLength) {
    return *this->cachedLength;
  }

  // Calculate the length and cache the results.
  size_t count{0};
  for (auto & item : this->stringParts) {
    count += item.length();
  }

  this->cachedLength = count;
  return count;
}

size_t ComputedExpressionString::bytesLength() const {
  // Return the cached length, if it exists.
  if (this->cachedBytesLength) {
    return *this->cachedBytesLength;
  }

  // Calculate the length and cache the results.
  size_t count{0};
  for (auto & item : this->stringParts) {
    count += item.bytesLength();
  }

  this->cachedBytesLength = count;
  return count;
}

NativeBoundFunctionMap ComputedExpressionString::getMethods() {
  return {
    {"length", {0, [](SPCE & target, [[maybe_unused]] vector<SPCE>& args) -> SPCE {
      return make_shared<ComputedExpressionInteger>((integer_t)static_cast<ComputedExpressionString &>(*target).length());
    }}},
  };
}

ComputedExpressionString & ComputedExpressionString::operator+=(const ComputedExpressionString &rhs) {
  this->stringParts.insert(this->stringParts.end(), rhs.stringParts.begin(), rhs.stringParts.end());
  return *this;
}

void ComputedExpressionString::setUntrusted() {
  for (auto & s : this->stringParts) {
    s.setUntrusted();
  }
}

void ComputedExpressionString::setPercent() {
  for (auto & s : this->stringParts) {
    s.setPercent();
  }
}

