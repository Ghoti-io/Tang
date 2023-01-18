/**
 * @file
 * Define the Tang::ComputedExpressionError class.
 */

#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionError::ComputedExpressionError(Tang::Error error) : error{error} {}

std::string ComputedExpressionError::dump() const {
  return string("Error: ") + this->error.message;
}

SPCE ComputedExpressionError::makeCopy() const {
  return make_shared<ComputedExpressionError>(*this);
}

bool ComputedExpressionError::is_equal(const Error & val) const {
  return this->error.message == val.message;
}

SPCE ComputedExpressionError::__add([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__subtract([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__multiply([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__divide([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__modulo([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__negative() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__not() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__lessThan([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__equal([[maybe_unused]] const SPCE & rhs) const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__integer() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__float() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__boolean() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

SPCE ComputedExpressionError::__string() const {
  return make_shared<ComputedExpressionError>(this->error.message);
}

