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

ComputedExpressionNativeBoundFunction::ComputedExpressionNativeBoundFunction(NativeBoundFunction nativeBoundFunction, size_t argc, type_index targetTypeIndex) : nativeBoundFunction{nativeBoundFunction}, argc{argc}, targetTypeIndex{targetTypeIndex} {}

string ComputedExpressionNativeBoundFunction::dump() const {
  return "Native Bound Function()";
}

SPCE ComputedExpressionNativeBoundFunction::makeCopy() const {
  auto tmp = make_shared<ComputedExpressionNativeBoundFunction>(this->nativeBoundFunction, this->argc, this->targetTypeIndex);
  static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = (*this->target)->makeCopy();
  return tmp;
}

SPCE ComputedExpressionNativeBoundFunction::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNativeBoundFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionNativeBoundFunction&>(*rhs);
    // TODO Add check for equality of target value, too.
    return make_shared<ComputedExpressionBoolean>(
      (this->nativeBoundFunction == rhsConv.nativeBoundFunction)
      && (this->argc == rhsConv.argc)
      && (this->targetTypeIndex == rhsConv.targetTypeIndex));
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

NativeBoundFunction ComputedExpressionNativeBoundFunction::getFunction() const{
  return this->nativeBoundFunction;
}

size_t ComputedExpressionNativeBoundFunction::getArgc() const {
  return this->argc;
}

const type_index & ComputedExpressionNativeBoundFunction::getTargetTypeIndex() const {
  return this->targetTypeIndex;
}

