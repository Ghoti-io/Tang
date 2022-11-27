/**
 * @file
 * Declare the Tang::ComputedExpressionArray class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONARRAY_HPP
#define TANG_COMPUTEDEXPRESSIONARRAY_HPP

#include <vector>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Array that is the result of a computation.
   */
  class ComputedExpressionArray : public ComputedExpression {
    public:
      /**
       * Construct an Array result.
       *
       * @param val The integer value.
       */
      ComputedExpressionArray(std::vector<Tang::GarbageCollected> contents);

      virtual std::string dump() const override;
      virtual bool isCopyNeeded() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __index(const GarbageCollected & index) const override;
      virtual GarbageCollected __assign_index(const GarbageCollected & index, const GarbageCollected & value) override;
      virtual GarbageCollected __string() const override;

    private:
      /**
       * The array contents.
       */
      std::vector<Tang::GarbageCollected> contents;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONARRAY_HPP

