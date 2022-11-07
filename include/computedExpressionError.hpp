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
      GarbageCollected makeCopy() const override;
      virtual bool is_equal(const Error & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __modulo(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __negative() const override;
      virtual GarbageCollected __not() const override;
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __integer() const override;
      virtual GarbageCollected __float() const override;
      virtual GarbageCollected __boolean() const override;
      virtual GarbageCollected __string() const override;

    private:
      /**
       * The Error object
       */
      Tang::Error error;
  };

}

#endif // TANG_COMPUTEDEXPRESSIONERROR_HPP

