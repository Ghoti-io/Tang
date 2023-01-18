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

// Return the "floor" of a value.
static LibraryFunction floorFunction = []([[maybe_unused]] Context & context) -> SPCE {
  return make_shared<ComputedExpressionNativeFunction>(
    [](vector<SPCE> & args, [[maybe_unused]] Context & context) -> SPCE {
      if (typeid(*args.at(0)) == typeid(ComputedExpressionInteger)) {
        return args.at(0);
      }
      if (typeid(*args.at(0)) == typeid(ComputedExpressionFloat)) {
        return make_shared<ComputedExpressionInteger>((integer_t)floor(static_cast<ComputedExpressionFloat&>(*args.at(0)).getValue()));
      }
      return make_shared<ComputedExpressionError>(Error{"Unknown argument type."});
    }, (size_t)1);
};

LibraryFunctionMap ComputedExpressionLibraryMath::getLibraryAttributes() {
  return {
    {"floor", floorFunction},
  };
}

