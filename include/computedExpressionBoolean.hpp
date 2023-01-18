/**
 * @file
 * Declare the Tang::ComputedExpressionBoolean class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONBOOLEAN_HPP
#define TANG_COMPUTEDEXPRESSIONBOOLEAN_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Boolean that is the result of a computation.
   */
  class ComputedExpressionBoolean : public ComputedExpression {
    public:
      /**
       * Construct an Boolean result.
       *
       * @param val The boolean value.
       */
      ComputedExpressionBoolean(bool val);

      virtual std::string dump() const override;
      SPCE makeCopy() const override;
      virtual bool is_equal(const bool & val) const override;
      virtual SPCE __not() const override;
      virtual SPCE __equal(const SPCE & rhs) const override;
      virtual SPCE __integer() const override;
      virtual SPCE __float() const override;
      virtual SPCE __boolean() const override;

    private:
      /**
       * The boolean value.
       */
      bool val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONBOOLEAN_HPP

