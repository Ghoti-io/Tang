/**
 * @file
 * Define the Tang::ComputedExpressionLibraryMath class.
 */

#include <typeinfo>
#include <cmath>
#include "tangBase.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionLibraryMath.hpp"
#include "computedExpressionNativeLibraryFunction.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionLibraryMath::ComputedExpressionLibraryMath() {}

GarbageCollected ComputedExpressionLibraryMath::makeCopy() const {
  return GarbageCollected::make<ComputedExpressionLibraryMath>();
}

LibraryFunctionMap ComputedExpressionLibraryMath::getLibraryAttributes() {
  return {
    // Return the "floor" of a value.
    {"floor", []([[maybe_unused]] Context & context) {
      return GarbageCollected::make<ComputedExpressionNativeFunction>(
        [](vector<GarbageCollected> & args, [[maybe_unused]] Context & context) {
          if (typeid(*args.at(0)) == typeid(ComputedExpressionInteger)) {
            return args.at(0);
          }
          if (typeid(*args.at(0)) == typeid(ComputedExpressionFloat)) {
            return GarbageCollected::make<ComputedExpressionInteger>((uinteger_t)floor(static_cast<ComputedExpressionFloat&>(*args.at(0)).getValue()));
          }
          return GarbageCollected::make<ComputedExpressionError>(Error{"Unknown argument type."});
        }, (size_t)1);
      }
    },
  };
}

