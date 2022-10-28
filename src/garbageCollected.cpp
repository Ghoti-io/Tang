#include "garbageCollected.hpp"

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

GarbageCollected GarbageCollected::operator+(const GarbageCollected & rhs) const {
  auto result = this->ref->__add(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator-(const GarbageCollected & rhs) const {
  auto result = this->ref->__subtract(rhs);
  return result;
}

GarbageCollected GarbageCollected::operator-() const {
  auto result = this->ref->__negative();
  return result;
}

