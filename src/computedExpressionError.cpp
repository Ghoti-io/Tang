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

GarbageCollected ComputedExpressionError::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionError>(*this);
}

bool ComputedExpressionError::is_equal(const Error & val) const {
  return this->error.message == val.message;
}

GarbageCollected ComputedExpressionError::__add([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__subtract([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__multiply([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__divide([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__modulo([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__negative() const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__not() const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__lessThan([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__equal([[maybe_unused]] const GarbageCollected & rhs) const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__integer() const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__float() const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

GarbageCollected ComputedExpressionError::__boolean() const {
  return GarbageCollected::make<ComputedExpressionError>(this->error.message);
}

