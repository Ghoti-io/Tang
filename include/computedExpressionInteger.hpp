/**
 * @file
 * Declare the Tang::ComputedExpressionInteger class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONINTEGER_HPP
#define TANG_COMPUTEDEXPRESSIONINTEGER_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents an Integer that is the result of a computation.
   */
  class ComputedExpressionInteger : public ComputedExpression {
    public:
      /**
       * Construct an Integer result.
       *
       * @param val The integer value.
       */
      ComputedExpressionInteger(Tang::integer_t val);

      virtual std::string dump() const override;
      SPCE makeCopy() const override;
      virtual bool is_equal(const Tang::integer_t & val) const override;
      virtual bool is_equal(const Tang::float_t & val) const override;
      virtual bool is_equal(const bool & val) const override;
      virtual SPCE __add(const SPCE & rhs) const override;
      virtual SPCE __subtract(const SPCE & rhs) const override;
      virtual SPCE __multiply(const SPCE & rhs) const override;
      virtual SPCE __divide(const SPCE & rhs) const override;
      virtual SPCE __modulo(const SPCE & rhs) const override;
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
      Tang::integer_t getValue() const;

    private:
      /**
       * The integer value.
       */
      Tang::integer_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONINTEGER_HPP

