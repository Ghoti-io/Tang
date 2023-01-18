/**
 * @file
 * Define the Tang::ComputedExpressionCompiledFunction class.
 */

#include "computedExpressionCompiledFunction.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionCompiledFunction::ComputedExpressionCompiledFunction(uint32_t argc, integer_t pc) : argc{argc}, pc{pc} {}

string ComputedExpressionCompiledFunction::dump() const {
  return "Compiled Function()";
}

SPCE ComputedExpressionCompiledFunction::makeCopy() const {
  return make_shared<ComputedExpressionCompiledFunction>(this->argc, this->pc);
}

SPCE ComputedExpressionCompiledFunction::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionCompiledFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionCompiledFunction&>(*rhs);
    return make_shared<ComputedExpressionBoolean>((this->argc == rhsConv.argc) && (this->pc == rhsConv.pc));
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

uint32_t ComputedExpressionCompiledFunction::getArgc() const {
  return this->argc;
}

Tang::integer_t ComputedExpressionCompiledFunction::getPc() const {
  return this->pc;
}

