/**
 * @file
 * Declare the Tang::ComputedExpressionNativeBoundFunction class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP
#define TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP

#include <optional>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a NativeBound Function declared in the script.
   */
  class ComputedExpressionNativeBoundFunction : public ComputedExpression {
    public:
      /**
       * Construct an NativeBoundFunction.
       *
       * @param argc The count of arguments that this function expects.
       * @param pc The bytecode address of the start of the function.
       */
      ComputedExpressionNativeBoundFunction(NativeBoundFunction nativeBoundFunction);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;

      /**
       * The target object that the function is bound to.
       */
      std::optional<GarbageCollected> target;

      /**
       * The native bound function to be executed.
       */
      NativeBoundFunction nativeBoundFunction;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONNATIVEBOUNDFUNCTION_HPP

