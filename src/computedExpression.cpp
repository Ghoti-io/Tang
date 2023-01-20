/**
 * @file
 * Define the Tang::ComputedExpression class.
 */

#include <typeinfo>
#include "computedExpression.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionError.hpp"
#include "tangBase.hpp"

using namespace std;
using namespace Tang;

ComputedExpression::~ComputedExpression() {}

string ComputedExpression::dump() const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? "null"
    : "UNKNOWN";
}

string ComputedExpression::__asCode() const {
  return this->dump();
}

bool ComputedExpression::isCopyNeeded() const {
  // By default, we will not request a copy of this ComputedExpression.
  return false;
}

SPCE ComputedExpression::makeCopy() const {
  return make_shared<ComputedExpression>();
}

bool ComputedExpression::is_equal([[maybe_unused]] const Tang::integer_t & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const Tang::float_t & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const bool & val) const {
  return typeid(*this) == typeid(ComputedExpression)
    ? val == false
    : false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const string & val) const {
  return false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const nullptr_t & val) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  return typeid(*this) == typeid(ComputedExpression)
    ? true
    : false;
}

bool ComputedExpression::is_equal([[maybe_unused]] const Error & val) const {
  return false;
}

SPCE ComputedExpression::__assign_index([[maybe_unused]] const SPCE & index, [[maybe_unused]] const SPCE & value) {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to assign this value to the index location."});
}

SPCE ComputedExpression::__add([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to add these values."});
}

SPCE ComputedExpression::__subtract([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to subtract these values."});
}

SPCE ComputedExpression::__multiply([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to multiply these values."});
}

SPCE ComputedExpression::__divide([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to divide these values."});
}

SPCE ComputedExpression::__modulo([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to modulo these values."});
}

SPCE ComputedExpression::__negative() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to negate this value."});
}

SPCE ComputedExpression::__not() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to compute the logical not of this value."});
}

SPCE ComputedExpression::__lessThan([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

SPCE ComputedExpression::__equal([[maybe_unused]] const SPCE & rhs) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually ComputedExpression, and not a derived type that forgot to
  // override the virtual method.
  if (typeid(*this) == typeid(ComputedExpression)) {
    if (typeid(*rhs) == typeid(ComputedExpression)) {
      return make_shared<ComputedExpressionBoolean>(true);
    }
    return make_shared<ComputedExpressionBoolean>(false);
  }
  return make_shared<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

SPCE ComputedExpression::__period([[maybe_unused]] const SPCE & member, [[maybe_unused]] shared_ptr<TangBase> & tang) const {
  if (typeid(*member) == typeid(ComputedExpressionString)) {
    auto & objectMethods = tang->getObjectMethods();
    auto thisType = type_index(typeid(*this));
    if (objectMethods.count(thisType)) {
      auto & methods = objectMethods.at(thisType);
      string name = static_cast<ComputedExpressionString &>(*member).dump();
      if (methods.count(name)) {
        auto & fn = methods.at(name);
        return make_shared<ComputedExpressionNativeBoundFunction>(fn.second, fn.first, type_index(typeid(*this)));
      }
    }
  }

  return make_shared<ComputedExpressionError>(Error{"Member not found."});
}

SPCE ComputedExpression::__index([[maybe_unused]] const SPCE & index) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to index this expression."});
}

SPCE ComputedExpression::__slice([[maybe_unused]] const SPCE & begin, [[maybe_unused]] const SPCE & end, [[maybe_unused]] const SPCE & skip) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to slice this expression."});
}

SPCE ComputedExpression::__getIterator([[maybe_unused]] const SPCE & collection) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to iterate over this expression."});
}

SPCE ComputedExpression::__iteratorNext([[maybe_unused]] size_t index) const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to iterate over this expression."});
}

SPCE ComputedExpression::__integer() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to cast this value to an integer."});
}

SPCE ComputedExpression::__float() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to cast this value to a float."});
}

SPCE ComputedExpression::__boolean() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to cast this value to a boolean."});
}

SPCE ComputedExpression::__string() const {
  return make_shared<ComputedExpressionError>(Error{"Don't know how to cast this value to a string."});
}

bool Tang::operator==(const ComputedExpression & lhs, const integer_t & val) {
  return (&lhs)->is_equal(val);
}

bool Tang::operator==(const ComputedExpression & lhs, const float_t & val) {
  return (&lhs)->is_equal(val);
}

bool Tang::operator==(const ComputedExpression & lhs, const bool & val) {
  return (&lhs)->is_equal(val);
}

bool Tang::operator==(const ComputedExpression & lhs, const string & val) {
  return (&lhs)->is_equal(val);
}

bool Tang::operator==(const ComputedExpression & lhs, const char * const & val) {
  return (&lhs)->is_equal(string(val));
}

bool Tang::operator==(const ComputedExpression & lhs, const Error & val) {
  return (&lhs)->is_equal(val);
}

bool Tang::operator==(const ComputedExpression & lhs, [[maybe_unused]] const nullptr_t & val) {
  return (&lhs)->is_equal(nullptr);
}

SPCE Tang::operator+(const SPCE & lhs, const SPCE & rhs) {
  auto result = lhs->__add(rhs);
  return result;
}

SPCE Tang::operator-(const SPCE & lhs, const SPCE & rhs) {
  auto result = lhs->__subtract(rhs);
  return result;
}

SPCE Tang::operator*(const SPCE & lhs, const SPCE & rhs) {
  auto result = lhs->__multiply(rhs);
  return result;
}

SPCE Tang::operator/(const SPCE & lhs, const SPCE & rhs) {
  auto result = lhs->__divide(rhs);
  return result;
}

SPCE Tang::operator%(const SPCE & lhs, const SPCE & rhs) {
  auto result = lhs->__modulo(rhs);
  return result;
}

SPCE Tang::operator-(const SPCE & lhs) {
  auto result = lhs->__negative();
  return result;
}

SPCE Tang::operator!(const SPCE & lhs) {
  auto result = lhs->__not();
  return result;
}

SPCE Tang::operator<(const SPCE & lhs, const SPCE & rhs) {
  return lhs->__lessThan(rhs);
}

SPCE Tang::operator<=(const SPCE & lhs, const SPCE & rhs) {
  auto result1 = lhs < rhs;
  if (typeid(*result1) == typeid(ComputedExpressionError)) {
    return result1;
  }
  if (result1->is_equal(true)) {
    return result1;
  }
  return lhs == rhs;
}

SPCE Tang::operator>(const SPCE & lhs, const SPCE & rhs) {
  return !(lhs <= rhs);
}

SPCE Tang::operator>=(const SPCE & lhs, const SPCE & rhs) {
  return !lhs->__lessThan(rhs);
}

SPCE Tang::operator==(const SPCE & lhs, const SPCE & rhs) {
  return lhs->__equal(rhs);
}

SPCE Tang::operator!=(const SPCE & lhs, const SPCE & rhs) {
  return !lhs->__equal(rhs);
}

std::ostream & Tang::operator<<(std::ostream & out, const SPCE & rhs) {
  return out << (rhs.use_count() ? rhs->dump() : "");
}

