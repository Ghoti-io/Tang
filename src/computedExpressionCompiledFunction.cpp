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

GarbageCollected ComputedExpressionCompiledFunction::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionCompiledFunction>(this->argc, this->pc);
}

GarbageCollected ComputedExpressionCompiledFunction::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionCompiledFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionCompiledFunction&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>((this->argc == rhsConv.argc) && (this->pc == rhsConv.pc));
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

