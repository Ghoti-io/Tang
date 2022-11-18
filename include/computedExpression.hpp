/**
 * @file
 * Declare the Tang::ComputedExpression base class.
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
#include "macros.hpp"
#include "garbageCollected.hpp"
#include "error.hpp"

namespace Tang {
  /**
   * Represents the result of a computation that has been executed.
   *
   * By default, it will represent a NULL value.
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
       * @return A Tang::GarbageCollected value for the new ComputedExpression.
       */
      virtual GarbageCollected makeCopy() const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const Tang::integer_t & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const Tang::float_t & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const bool & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const string & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const Error & val) const;

      /**
       * Check whether or not the computed expression is equal to another value.
       *
       * @param val The value to compare against.
       * @return True if equal, false if not.
       */
      virtual bool is_equal(const std::nullptr_t & val) const;

      /**
       * Perform an index assignment to the supplied value.
       *
       * @param index The index to which the value should be applied.
       * @param value The value to store.
       * @return The result of the operation.
       */
      virtual GarbageCollected __assign_index(const GarbageCollected & index, const GarbageCollected & value);

      /**
       * Compute the result of adding this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to add to this.
       * @return The result of the operation.
       */
      virtual GarbageCollected __add(const GarbageCollected & rhs) const;

      /**
       * Compute the result of subtracting this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to subtract from this.
       * @return The result of the operation.
       */
      virtual GarbageCollected __subtract(const GarbageCollected & rhs) const;

      /**
       * Compute the result of multiplying this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to multiply to this.
       * @return The result of the operation.
       */
      virtual GarbageCollected __multiply(const GarbageCollected & rhs) const;

      /**
       * Compute the result of dividing this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to divide this by.
       * @return The result of the operation.
       */
      virtual GarbageCollected __divide(const GarbageCollected & rhs) const;

      /**
       * Compute the result of moduloing this value and the supplied value.
       *
       * @param rhs The GarbageCollected value to modulo this by.
       * @return The result of the operation.
       */
      virtual GarbageCollected __modulo(const GarbageCollected & rhs) const;

      /**
       * Compute the result of negating this value.
       *
       * @return The result of the operation.
       */
      virtual GarbageCollected __negative() const;

      /**
       * Compute the logical not of this value.
       *
       * @return The result of the operation.
       */
      virtual GarbageCollected __not() const;

      /**
       * Compute the "less than" comparison.
       *
       * @param rhs The GarbageCollected value to compare against.
       * @return The result of the the operation.
       */
      virtual GarbageCollected __lessThan(const GarbageCollected & rhs) const;

      /**
       * Perform an equality test.
       *
       * @param rhs The GarbageCollected value to compare against.
       * @return The result of the the operation.
       */
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const;

      /**
       * Perform an index operation.
       *
       * @param index The index expression provided by the script.
       * @return The result of the operation.
       */
      virtual GarbageCollected __index(const GarbageCollected & index) const;

      /**
       * Perform a type cast to integer.
       *
       * @return The result of the the operation.
       */
      virtual GarbageCollected __integer() const;

      /**
       * Perform a type cast to float.
       *
       * @return The result of the the operation.
       */
      virtual GarbageCollected __float() const;

      /**
       * Perform a type cast to boolean.
       *
       * @return The result of the the operation.
       */
      virtual GarbageCollected __boolean() const;

      /**
       * Perform a type cast to string.
       *
       * @return The result of the the operation.
       */
      virtual GarbageCollected __string() const;
  };
}

#endif // TANG_COMPUTEDEXPRESSION_HPP

