/**
 * @file
 */

#include "computedExpression.hpp"

using namespace std;
using namespace Tang;

ComputedExpression::~ComputedExpression() {}

string ComputedExpression::dump() const {
  return "";
}

ComputedExpression * ComputedExpression::makeCopy() const {
  return new ComputedExpression();
}

bool ComputedExpression::is_equal([[maybe_unused]] const int & val) const {
  return false;
}

ComputedExpressionInteger::ComputedExpressionInteger(int64_t val) : val{val} {}

string ComputedExpressionInteger::dump() const {
  return to_string(this->val);
}

ComputedExpression * ComputedExpressionInteger::makeCopy() const {
  return new ComputedExpressionInteger(this->val);
}

bool ComputedExpressionInteger::is_equal(const int & val) const {
  return val == this->val;
}

