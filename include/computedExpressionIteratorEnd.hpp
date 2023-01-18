/**
 * @file
 * Declare the Tang::ComputedExpressionIteratorEnd class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONITERATOREND_HPP
#define TANG_COMPUTEDEXPRESSIONITERATOREND_HPP

#include <vector>
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents that a collection has no more values through which to iterate.
   */
  class ComputedExpressionIteratorEnd : public ComputedExpression {
    public:
      /**
       * Construct an IteratorEnd result.
       */
      ComputedExpressionIteratorEnd();

      virtual std::string dump() const override;
      virtual SPCE __string() const override;

    private:
  };
}

#endif // TANG_COMPUTEDEXPRESSIONITERATOREND_HPP

