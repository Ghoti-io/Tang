/**
 * @file
 * Declare the Tang::ComputedExpressionLibraryMath class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONLIBRARYMATH_HPP
#define TANG_COMPUTEDEXPRESSIONLIBRARYMATH_HPP

#include "macros.hpp"
#include "computedExpressionLibrary.hpp"

namespace Tang {
  /**
   * Represents a Runtime LibraryMath.
   */
  class ComputedExpressionLibraryMath: public ComputedExpressionLibrary {
    public:
      /**
       * Construct a Runtime Library for Math operations.
       */
      ComputedExpressionLibraryMath();

      GarbageCollected makeCopy() const override;
      
      /**
       * Construct the LibararyFunctionMap for this map's attributes.
       *
       * @returns The library attribute functions for this library.
       */
      static LibraryFunctionMap getLibraryAttributes();
  };
}

#endif // TANG_COMPUTEDEXPRESSIONLIBRARYMATH_HPP

