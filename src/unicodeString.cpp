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
#include <sstream>
#include <unicode/uconfig.h>
#include <unicode/ustring.h>
#include <unicode/brkiter.h>
#include "unicodeString.hpp"
#include "unescape.hpp"
#include "htmlEscape.hpp"
#include "htmlEscapeAscii.hpp"
#include "percentEncode.hpp"

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

string Tang::unescape(const string & str) {
  stringstream ss{str};
  Unescape u{ss, cout};
  string out{}, next;
  while ((next = u.get_next_token()).length()) {
    out += next;
  }
  return out;
}

string Tang::htmlEscape(const string & str) {
  stringstream ss{str};
  HtmlEscape h{ss, cout};
  string out{}, next;
  while ((next = h.get_next_token()).length()) {
    out += next;
  }
  return out;
}

string Tang::htmlEscapeAscii(const string & str, UnicodeString::Type type) {
  stringstream ss{str};
  HtmlEscapeAscii h{ss, cout, type};
  string out{}, next;
  while ((next = h.get_next_token()).length()) {
    out += next;
  }
  return out;
}

std::string Tang::percentEncode(const std::string & str) {
  stringstream ss{str};
  PercentEncode p{ss, cout};
  string out{}, next;
  while ((next = p.get_next_token()).length()) {
    out += next;
  }
  return out;
}

UnicodeString::UnicodeString() : src{}, type{UnicodeString::Type::Trusted} {}

UnicodeString::UnicodeString(const UnicodeString & source) : src{source.src}, type{source.type} {}

UnicodeString::UnicodeString(const string & src) : src{src}, type{UnicodeString::Type::Trusted} {}

std::string UnicodeString::substr(size_t position, size_t length) const {
  // First sanity check.
  if (length < 1) {
    return "";
  }

  // Compute the grapheme offsets
  this->generateCachedValues();

  // Second sanity check.
  if (position >= this->graphemeOffsets->size()) {
    return "";
  }

  // Perform the substring.
  string out;
  return static_pointer_cast<icu::UnicodeString>(this->uString)->tempSubString(this->graphemeOffsets->at(position), this->graphemeOffsets->at(min(position + length, this->graphemeOffsets->size() - 1)) - this->graphemeOffsets->at(position)).toUTF8String(out);
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

UnicodeString & UnicodeString::operator+=(const UnicodeString & rhs) {
  this->src += rhs.src;
  return *this;
}

UnicodeString::operator std::string() const {
  return this->src;
}

size_t UnicodeString::length() const {
  this->generateCachedValues();
  return this->graphemeOffsets->size() - 1;
}

size_t UnicodeString::bytesLength() const {
  return this->src.length();
}

void UnicodeString::generateCachedValues() const {
  if (!this->uString) {
    this->uString = make_shared<icu::UnicodeString>(icu::UnicodeString::fromUTF8(this->src));
  }
  if (!this->graphemeOffsets) {
    this->graphemeOffsets = make_shared<vector<size_t>>(getGraphemeOffsets(*static_pointer_cast<icu::UnicodeString>(this->uString)));
  }
}

string UnicodeString::render() const {
  return (this->type == Type::Trusted)
    ? this->src
    : this->type == Type::Percent
      ? percentEncode(this->src)
      : htmlEscape(this->src);
}

string UnicodeString::renderAscii() const {
  return htmlEscapeAscii(this->src, this->type);
}

void UnicodeString::setUntrusted() {
  this->type = UnicodeString::Type::Untrusted;
}

void UnicodeString::setPercent() {
  this->type = UnicodeString::Type::Percent;
}

