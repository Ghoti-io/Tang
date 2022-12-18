/**
 * @file
 * Declare the Tang::ComputedExpressionNativeFunction class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONNATIVEFUNCTION_HPP
#define TANG_COMPUTEDEXPRESSIONNATIVEFUNCTION_HPP

#include <optional>
#include <typeindex>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Native Function provided by compiled C++ code.
   */
  class ComputedExpressionNativeFunction : public ComputedExpression {
    public:
      /**
       * Construct an NativeFunction.
       *
       * The object itself is designed to be safe in that, once it is
       * constructed, the method function pointer, and argument count
       * cannot be changed, but can only be accessible through a getter.
       *
       * @param nativeFunction The native function to be executed.
       * @param argc The count of arguments that this function expects.
       */
      ComputedExpressionNativeFunction(NativeFunction nativeFunction, size_t argc);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;

      /**
       * Get the native bound function to be executed.
       *
       * @return The native bound function to be executed.
       */
      NativeFunction getFunction() const;

      /**
       * Get the count of arguments that this function expects.
       *
       * @return The count of arguments that this function expects.
       */
      size_t getArgc() const;

    private:
      /**
       * The native bound function to be executed.
       */
      NativeFunction nativeFunction;

      /**
       * The count of arguments that this function expects.
       */
      size_t argc;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONNATIVEFUNCTION_HPP

