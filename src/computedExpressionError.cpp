/**
 * @file
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

