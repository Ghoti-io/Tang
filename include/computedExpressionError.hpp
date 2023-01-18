/**
 * @file
 * Declare the Tang::ComputedExpressionError class.
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
      SPCE makeCopy() const override;
      virtual bool is_equal(const Error & val) const override;
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

    private:
      /**
       * The Error object
       */
      Tang::Error error;
  };

}

#endif // TANG_COMPUTEDEXPRESSIONERROR_HPP

