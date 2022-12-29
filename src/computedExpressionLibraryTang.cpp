/**
 * @file
 * Define the Tang::ComputedExpressionLibraryTang class.
 */

#include <typeinfo>
#include <cmath>
#include "tangBase.hpp"
#include "computedExpressionLibraryTang.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

// Return the "version" of a value.
static LibraryFunction versionFunction = []([[maybe_unused]] Context & context) {
  return GarbageCollected::make<ComputedExpressionString>(TANGVERSION);
};

LibraryFunctionMap ComputedExpressionLibraryTang::getLibraryAttributes() {
  return {
    {"version", versionFunction},
  };
}

