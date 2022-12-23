/**
 * @file
 * Declare the Tang::ComputedExpressionLibrary class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONLIBRARY_HPP
#define TANG_COMPUTEDEXPRESSIONLIBRARY_HPP

#include "macros.hpp"
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Runtime Library.
   */
  class ComputedExpressionLibrary: public ComputedExpression {
    public:
      /**
       * Construct a Runtime Library
       *
       * @param library The NativeFunctionMap this library represents.
       */
      ComputedExpressionLibrary(const Tang::NativeFunctionMap * library);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;

    private:
      /**
       * Reference to the NativeFunctionMap this library represents.
       */
      const NativeFunctionMap* library;
  };

}

#endif // TANG_COMPUTEDEXPRESSIONLIBRARY_HPP

