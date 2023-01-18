/**
 * @file
 * Define the Tang::ComputedExpressionNativeLibraryFunction class.
 */

#include "context.hpp"
#include "computedExpressionNativeLibraryFunction.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionNativeLibraryFunction::ComputedExpressionNativeLibraryFunction(LibraryFunction libraryFunction) : libraryFunction{libraryFunction} {}

string ComputedExpressionNativeLibraryFunction::dump() const {
  return "Library Function()";
}

SPCE ComputedExpressionNativeLibraryFunction::makeCopy() const {
  return make_shared<ComputedExpressionNativeLibraryFunction>(this->libraryFunction);
}

SPCE ComputedExpressionNativeLibraryFunction::__equal(const SPCE & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNativeLibraryFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionNativeLibraryFunction&>(*rhs);
    return make_shared<ComputedExpressionBoolean>(this->libraryFunction == rhsConv.libraryFunction);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

LibraryFunction ComputedExpressionNativeLibraryFunction::getFunction() const{
  return this->libraryFunction;
}

