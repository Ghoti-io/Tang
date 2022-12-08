/**
 * @file
 * Define the Tang::ComputedExpressionNativeBoundFunction class.
 */

#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionNativeBoundFunction::ComputedExpressionNativeBoundFunction(NativeBoundFunction nativeBoundFunction) : nativeBoundFunction{nativeBoundFunction} {}

string ComputedExpressionNativeBoundFunction::dump() const {
  return "Native Bound Function()";
}

GarbageCollected ComputedExpressionNativeBoundFunction::makeCopy() const {
  auto tmp = GarbageCollected::make<ComputedExpressionNativeBoundFunction>(this->nativeBoundFunction);
  static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = this->target->makeCopy();
  return tmp;
}

GarbageCollected ComputedExpressionNativeBoundFunction::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNativeBoundFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionNativeBoundFunction&>(*rhs);
    // TODO Add check for equality of target value, too.
    return GarbageCollected::make<ComputedExpressionBoolean>(this->nativeBoundFunction == rhsConv.nativeBoundFunction);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

