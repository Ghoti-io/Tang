/**
 * @file
 * Define the Tang::ComputedExpressionLibrary class.
 */

#include "computedExpressionLibrary.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionLibrary::ComputedExpressionLibrary(const Tang::NativeFunctionMap * library) : library{library} {}

std::string ComputedExpressionLibrary::dump() const {
  return string("Library");
}

GarbageCollected ComputedExpressionLibrary::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionLibrary>(this->library);
}

