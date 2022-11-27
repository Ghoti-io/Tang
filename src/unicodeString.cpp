/**
 * @file
 *
 * Contains the function declarations for the Tang::UnicodeString class and the
 * interface to ICU.
 */

#include <cassert>
#include <vector>
#include <memory>
#include <algorithm>
#include <unicode/uconfig.h>
#include <unicode/ustring.h>
#include <unicode/brkiter.h>
#include "unicodeString.hpp"

using namespace std;
using namespace Tang;

static std::vector<size_t> getGraphemeOffsets(const icu::UnicodeString &str) {
  vector<size_t> offsets;
  // Worst case: string is standard ASCII.
  offsets.reserve(str.length() + 1);

  // Create an ICU Character Break Iterator to identify the graphemes.
  UErrorCode err = U_ZERO_ERROR;
  unique_ptr<icu::BreakIterator> iter(icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), err));
  assert(U_SUCCESS(err));

  // Set the text to iterate through.
  iter->setText(str);

  // Iterate through the graphemes.
  auto current = iter->current();
  while (iter->next() != icu::BreakIterator::DONE) {
    offsets.push_back(current);
    current = iter->current();
  }
  offsets.push_back(current);

  return offsets;
}

UnicodeString::UnicodeString(const string & src) : src{src} {}

std::string UnicodeString::substr(size_t position, size_t length) const {
  // First sanity check.
  if (length < 1) {
    return "";
  }

  // Compute the offsets.
  auto uString = icu::UnicodeString::fromUTF8(this->src);
  auto offsets = getGraphemeOffsets(uString);

  // Second sanity check.
  if (position >= offsets.size()) {
    return "";
  }

  // Perform the substring.
  string out;
  return uString.tempSubString(offsets[position], offsets[min(position + length, offsets.size() - 1)] - offsets[position]).toUTF8String(out);
}

bool UnicodeString::operator==(const UnicodeString & rhs) const {
  return this->src == rhs.src;
}

bool UnicodeString::operator<(const UnicodeString & rhs) const {
  return this->src < rhs.src;
}

UnicodeString UnicodeString::operator+(const UnicodeString & rhs) const {
  return this->src + rhs.src;
}

UnicodeString::operator std::string() const {
  return this->src;
}

size_t UnicodeString::length() const {
  auto offsets = getGraphemeOffsets(icu::UnicodeString::fromUTF8(this->src));
  return offsets.size() - 1;
}

size_t UnicodeString::bytesLength() const {
  return this->src.length();
}

