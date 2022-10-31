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
      ComputedExpressionFloat(double val);

      virtual std::string dump() const override;
      ComputedExpression * makeCopy() const override;
      virtual bool is_equal(const int & val) const override;
      virtual bool is_equal(const double & val) const override;
      virtual GarbageCollected __add(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __negative() const override;
      virtual GarbageCollected __not() const override;
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;
      virtual GarbageCollected __integer() const override;
      virtual GarbageCollected __float() const override;
      virtual GarbageCollected __boolean() const override;

      friend class ComputedExpressionInteger;

    private:
      /**
       * The float value.
       */
      double val;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONFLOAT_HPP

