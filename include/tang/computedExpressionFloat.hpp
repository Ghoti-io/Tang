/**
 * @file
 * Declare the Tang::ComputedExpressionFloat class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONFLOAT_HPP
#define TANG_COMPUTEDEXPRESSIONFLOAT_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Float that is the result of a computation.
   */
  class ComputedExpressionFloat: public ComputedExpression {
    public:
      /**
       * Construct a Float result.
       *
       * @param val The float value.
       */
      ComputedExpressionFloat(Tang::float_t val);

      virtual std::string dump() const override;
      SPCE makeCopy() const override;
      virtual bool is_equal(const Tang::integer_t & val) const override;
      virtual bool is_equal(const Tang::float_t & val) const override;
      virtual bool is_equal(const bool & val) const override;
      virtual SPCE __add(const SPCE & rhs) const override;
      virtual SPCE __subtract(const SPCE & rhs) const override;
      virtual SPCE __multiply(const SPCE & rhs) const override;
      virtual SPCE __divide(const SPCE & rhs) const override;
      virtual SPCE __negative() const override;
      virtual SPCE __not() const override;
      virtual SPCE __lessThan(const SPCE & rhs) const override;
      virtual SPCE __equal(const SPCE & rhs) const override;
      virtual SPCE __integer() const override;
      virtual SPCE __float() const override;
      virtual SPCE __boolean() const override;
      virtual SPCE __string() const override;

      /**
       * Helper function to get the value associated with this expression.
       *
       * @return The value associated with this expression.
       */
      Tang::float_t getValue() const;

    private:
      /**
       * The float value.
       */
      Tang::float_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONFLOAT_HPP

