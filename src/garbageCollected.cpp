#include "garbageCollected.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

namespace Tang {
  std::ostream & operator<<(std::ostream & out, const GarbageCollected & gc) {
    return out << (gc.ref ? gc.ref->dump() : "");
  }
}

bool GarbageCollected::operator==(const int & val) const {
  return this->ref && this->ref->is_equal(val);
}

bool GarbageCollected::operator==(const double & val) const {
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


