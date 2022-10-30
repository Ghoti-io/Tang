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

ComputedExpression * ComputedExpressionError::makeCopy() const {
  return new ComputedExpressionError(*this);
}

bool ComputedExpressionError::is_equal(const Error & val) const {
  return this->error.message == val.message;
}

