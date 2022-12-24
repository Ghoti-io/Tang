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

GarbageCollected ComputedExpressionNativeLibraryFunction::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionNativeLibraryFunction>(this->libraryFunction);
}

GarbageCollected ComputedExpressionNativeLibraryFunction::__equal(const GarbageCollected & rhs) const {
  if (typeid(*rhs) == typeid(ComputedExpressionNativeLibraryFunction)) {
    auto & rhsConv = static_cast<ComputedExpressionNativeLibraryFunction&>(*rhs);
    return GarbageCollected::make<ComputedExpressionBoolean>(this->libraryFunction == rhsConv.libraryFunction);
  }

  // Return the default error.
  return ComputedExpression::__equal(rhs);
}

LibraryFunction ComputedExpressionNativeLibraryFunction::getFunction() const{
  return this->libraryFunction;
}

