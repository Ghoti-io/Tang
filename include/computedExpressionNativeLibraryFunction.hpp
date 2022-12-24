/**
 * @file
 * Declare the Tang::ComputedExpressionNativeLibraryFunction class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION_HPP
#define TANG_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION_HPP

#include <optional>
#include <typeindex>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Native Function provided by compiled C++ code that is
   * executed to create a library or one of its attributes.
   *
   * The purpose of this function is to be able to construct a library or the
   * library attributes as needed at runtime.
   */
  class ComputedExpressionNativeLibraryFunction : public ComputedExpression {
    public:
      /**
       * Construct a NativeLibraryFunction.
       *
       * @param libraryFunction The library function to be executed.
       */
      ComputedExpressionNativeLibraryFunction(LibraryFunction nativeFunction);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;

      /**
       * Get the native bound function to be executed.
       *
       * @return The native bound function to be executed.
       */
      LibraryFunction getFunction() const;

    private:
      /**
       * The library function to be executed.
       */
      LibraryFunction libraryFunction;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONNATIVELIBRARYFUNCTION_HPP

