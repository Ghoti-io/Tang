/**
 * @file
 */

#ifndef TANG_COMPUTEDEXPRESSIONERROR_HPP
#define TANG_COMPUTEDEXPRESSIONERROR_HPP

#include "computedExpression.hpp"
#include "error.hpp"

namespace Tang {
  /**
   * Represents a Runtime Error.
   */
  class ComputedExpressionError: public ComputedExpression {
    public:
      /**
       * Construct a Runtime Error
       *
       * @param error The Tang::Error object.
       */
      ComputedExpressionError(Tang::Error error);

      virtual std::string dump() const override;
      ComputedExpression * makeCopy() const override;
      virtual bool is_equal(const Error & val) const override;

    private:
      /**
       * The Error object
       */
      Tang::Error error;
  };

}

#endif // TANG_COMPUTEDEXPRESSIONERROR_HPP

