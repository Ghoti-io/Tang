#include "garbageCollected.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

namespace Tang {
  std::ostream & operator<<(std::ostream & out, const GarbageCollected & gc) {
    return out << (gc.ref ? gc.ref->dump() : "");
  }
}

GarbageCollected::GarbageCollected(const GarbageCollected & other) {
  this->count = other.count;
  ++*this->count;
  this->ref = other.ref;
  this->recycle = other.recycle;
}

GarbageCollected::GarbageCollected(GarbageCollected && other) {
  // Move the other item's attributes.
  this->ref = other.ref;
  this->count = other.count;
  ++*this->count;
  this->recycle = std::move(other.recycle);
}

GarbageCollected & GarbageCollected::operator=(const GarbageCollected & other) {
  // Remove references from the current object.
  this->~GarbageCollected();

  // Copy the other item's attributes.
  this->ref = other.ref;
  this->count = other.count;
  ++*this->count;
  this->recycle = other.recycle;

  return *this;
}

GarbageCollected & GarbageCollected::operator=(GarbageCollected && other) {
  // Remove references from the current object.
  this->~GarbageCollected();

  // Move the other item's attributes.
  this->ref = other.ref;
  this->count = other.count;
  ++*this->count;
  this->recycle = std::move(other.recycle);

  return *this;
}

GarbageCollected::~GarbageCollected() {
  if (--*this->count == 0) {
    if (this->ref) {
      this->recycle();
    }
    if (this->count) {
      delete this->count;
    }
  }
}

GarbageCollected GarbageCollected::makeCopy() const {
  return this->ref->makeCopy();
}

ComputedExpression* GarbageCollected::operator->() const {
  return this->ref;
}

ComputedExpression& GarbageCollected::operator*() const {
  return *this->ref;
}

bool GarbageCollected::operator==(const integer_t & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const float_t & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const bool & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const string & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const char * const & val) const {
  return this->ref && this->ref->is_equal(string(val));
}

bool GarbageCollected::operator==(const Error & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const std::nullptr_t & val) const {
  return this->ref && this->ref->is_equal(val);
}

GarbageCollected GarbageCollected::operator+(const GarbageCollected & rhs) const {
  auto result = this->ref->__add(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator-(const GarbageCollected & rhs) const {
  auto result = this->ref->__subtract(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator*(const GarbageCollected & rhs) const {
  auto result = this->ref->__multiply(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator/(const GarbageCollected & rhs) const {
  auto result = this->ref->__divide(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator%(const GarbageCollected & rhs) const {
  auto result = this->ref->__modulo(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator-() const {
  auto result = this->ref->__negative();
  return result;
}

GarbageCollected GarbageCollected::operator!() const {
  auto result = this->ref->__not();
  return result;
}

GarbageCollected GarbageCollected::operator<(const GarbageCollected & rhs) const {
  return this->ref->__lessThan(rhs);
}

GarbageCollected GarbageCollected::operator<=(const GarbageCollected & rhs) const {
  auto result1 = *this < rhs;
  if (typeid(*result1) == typeid(ComputedExpressionError)) {
    return result1;
  }
  if (result1->is_equal(true)) {
    return result1;
  }
  return *this == rhs;
}

GarbageCollected GarbageCollected::operator>(const GarbageCollected & rhs) const {
  return !(*this <= rhs);
}

GarbageCollected GarbageCollected::operator>=(const GarbageCollected & rhs) const {
  return !this->ref->__lessThan(rhs);
}

GarbageCollected GarbageCollected::operator==(const GarbageCollected & rhs) const {
  return this->ref->__equal(rhs);
}

GarbageCollected GarbageCollected::operator!=(const GarbageCollected & rhs) const {
  return !this->ref->__equal(rhs);
}


