/**
 * @file
 * Declare the Tang::ComputedExpressionNull class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONNULL_HPP
#define TANG_COMPUTEDEXPRESSIONNULL_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Null that is the result of a computation.
   */
  class ComputedExpressionNull : public ComputedExpression {
    public:
      /**
       * Construct an Null result.
       */
      ComputedExpressionNull();

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      bool is_equal(const nullptr_t & val) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;

    private:
  };
}

#endif // TANG_COMPUTEDEXPRESSIONNULL_HPP

