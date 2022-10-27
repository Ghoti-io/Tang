/**
 * @file
 */

namespace Tang {
  class ComputedExpression;
  class ComputedExpressionInteger;
  class ComputedExpressionFloat;
}

#ifndef TANG_COMPUTEDEXPRESSION_HPP
#define TANG_COMPUTEDEXPRESSION_HPP

#include <cstdint>
#include <string>
#include "garbageCollected.hpp"

namespace Tang {
  /**
   * Represents the result of a computation that has been executed.
   */
  class ComputedExpression {
    public:
      /**
       * The object destructor.
       */
      virtual ~ComputedExpression();

      /**
       * Output the contents of the ComputedExpression as a string.
       *
       * @returns A string representation of the computed expression.
       */
      virtual std::string dump() const;

      /**
       * Make a copy of the ComputedExpression (recursively, if appropriate).
       *
       * @return A pointer to the new ComputedExpression.
       */
      virtual ComputedExpression * makeCopy() const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const int & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const double & val) const;

      /**
       * Compute the result of adding this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to add to this.
       * @return The result of the operation.
       */
      virtual GarbageCollected __add(const GarbageCollected & rhs) const;
  };
}

#endif // TANG_COMPUTEDEXPRESSION_HPP
