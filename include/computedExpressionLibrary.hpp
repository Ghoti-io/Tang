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
       */
      ComputedExpressionLibrary();

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      GarbageCollected __period(const GarbageCollected & member, std::shared_ptr<TangBase> & tang) const override;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONLIBRARY_HPP

