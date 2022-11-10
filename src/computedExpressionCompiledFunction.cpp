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

ComputedExpressionCompiledFunction::ComputedExpressionCompiledFunction(integer_t pc) : pc{pc} {}

string ComputedExpressionCompiledFunction::dump() const {
  return "Compiled Function()";
}

GarbageCollected ComputedExpressionCompiledFunction::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionCompiledFunction>(this->pc);
}

GarbageCollected ComputedExpressionCompiledFunction::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionCompiledFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionCompiledFunction&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
        this->pc == rhsConv.pc);
  }

  return GarbageCollected::make<ComputedExpressionError>(Error{"Don't know how to compare these values."});
}

