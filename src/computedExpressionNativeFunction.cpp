/**
 * @file
 * Define the Tang::ComputedExpressionNativeFunction class.
 */

#include "context.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionNativeFunction::ComputedExpressionNativeFunction(NativeFunction nativeFunction, size_t argc) : nativeFunction{nativeFunction}, argc{argc} {}

string ComputedExpressionNativeFunction::dump() const {
  return "Native Function()";
}

GarbageCollected ComputedExpressionNativeFunction::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionNativeFunction>(this->nativeFunction, this->argc);
}

GarbageCollected ComputedExpressionNativeFunction::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNativeFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionNativeFunction&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(
      (this->nativeFunction == rhsConv.nativeFunction)
      && (this->argc == rhsConv.argc));
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

NativeFunction ComputedExpressionNativeFunction::getFunction() const{
  return this->nativeFunction;
}

size_t ComputedExpressionNativeFunction::getArgc() const {
  return this->argc;
}

