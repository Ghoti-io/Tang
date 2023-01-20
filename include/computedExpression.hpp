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
#include <vector>
#include <memory>
#include "macros.hpp"
#include "garbageCollected.hpp"
#include "error.hpp"

namespace Tang {
  class TangBase;

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
       * Output the contents of the ComputedExpression as a string similar to
       * how it would be represented as code.
       *
       * @returns A code-string representation of the computed expression.
       */
      virtual std::string __asCode() const;

      /**
       * Determine whether or not a copy is needed.
       *
       * Copying is only required for ComputedExpressions which serve as
       * containers, such as ComputedExpressionArray and
       * ComputedExpressionObject.
       *
       * @return Whether or not a copy is needed.
       */
      virtual bool isCopyNeeded() const;

      /**
       * Make a copy of the ComputedExpression (recursively, if appropriate).
       *
       * @return A Tang::SPCE value for the new ComputedExpression.
       */
      virtual SPCE makeCopy() const;

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
      virtual bool is_equal(const std::string & val) const;

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
      virtual SPCE __assign_index(const SPCE & index, const SPCE & value);

      /**
       * Compute the result of adding this value and the supplied value.
       *
       * @param rhs The SPCE value to add to this.
       * @return The result of the operation.
       */
      virtual SPCE __add(const SPCE & rhs) const;

      /**
       * Compute the result of subtracting this value and the supplied value.
       *
       * @param rhs The SPCE value to subtract from this.
       * @return The result of the operation.
       */
      virtual SPCE __subtract(const SPCE & rhs) const;

      /**
       * Compute the result of multiplying this value and the supplied value.
       *
       * @param rhs The SPCE value to multiply to this.
       * @return The result of the operation.
       */
      virtual SPCE __multiply(const SPCE & rhs) const;

      /**
       * Compute the result of dividing this value and the supplied value.
       *
       * @param rhs The SPCE value to divide this by.
       * @return The result of the operation.
       */
      virtual SPCE __divide(const SPCE & rhs) const;

      /**
       * Compute the result of moduloing this value and the supplied value.
       *
       * @param rhs The SPCE value to modulo this by.
       * @return The result of the operation.
       */
      virtual SPCE __modulo(const SPCE & rhs) const;

      /**
       * Compute the result of negating this value.
       *
       * @return The result of the operation.
       */
      virtual SPCE __negative() const;

      /**
       * Compute the logical not of this value.
       *
       * @return The result of the operation.
       */
      virtual SPCE __not() const;

      /**
       * Compute the "less than" comparison.
       *
       * @param rhs The SPCE value to compare against.
       * @return The result of the the operation.
       */
      virtual SPCE __lessThan(const SPCE & rhs) const;

      /**
       * Perform an equality test.
       *
       * @param rhs The SPCE value to compare against.
       * @return The result of the the operation.
       */
      virtual SPCE __equal(const SPCE & rhs) const;

      /**
       * Perform a member access (period) operation.
       *
       * @param member The member expression provided by the script.
       * @return The result of the operation.
       */
      virtual SPCE __period(const SPCE & member, std::shared_ptr<TangBase> & tang) const;

      /**
       * Perform an index operation.
       *
       * @param index The index expression provided by the script.
       * @return The result of the operation.
       */
      virtual SPCE __index(const SPCE & index) const;

      /**
       * Perform a slice operation.
       *
       * Convention will follow Python semantics, in which a slice will start
       * at the provided index position, and go up to but not including the end
       * index.  The slice will default to an index increment of 1, but can be
       * defined as another integer value.
       *
       * @param begin The begin index expression provided by the script.
       * @param end The end index expression provided by the script.
       * @param skip The skip index expression provided by the script.
       * @return The result of the operation.
       */
      virtual SPCE __slice(const SPCE & begin, const SPCE & end, const SPCE & skip) const;

      /**
       * Get an iterator for the expression.
       *
       * @param collection The SPCE value that will serve as the
       *   collection through which to iterate.
       */
      virtual SPCE __getIterator(const SPCE & collection) const;

      /**
       * Get the next iterative value.
       *
       * @param index The desired index value.
       */
      virtual SPCE __iteratorNext(size_t index = 0) const;

      /**
       * Perform a type cast to integer.
       *
       * @return The result of the the operation.
       */
      virtual SPCE __integer() const;

      /**
       * Perform a type cast to float.
       *
       * @return The result of the the operation.
       */
      virtual SPCE __float() const;

      /**
       * Perform a type cast to boolean.
       *
       * @return The result of the the operation.
       */
      virtual SPCE __boolean() const;

      /**
       * Perform a type cast to string.
       *
       * @return The result of the the operation.
       */
      virtual SPCE __string() const;
  };

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const Tang::integer_t & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const Tang::float_t & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const bool & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const std::string & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const char * const & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const Error & val);

  /**
   * Compare the ComputedExpression with a supplied value.
   *
   * @param val The value to compare the tracked object against.
   * @return True if they are equal, false otherwise.
   */
  bool operator==(const ComputedExpression & lhs, const nullptr_t & null);

  /**
   * Add friendly output.
   *
   * @param out The output stream.
   * @param rhs The SPCE value.
   * @return The output stream.
   */
  std::ostream & operator<<(std::ostream & out, const SPCE & rhs);

  /**
   * Perform an addition between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator+(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a subtraction between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator-(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a multiplication between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator*(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a division between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator/(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a modulo between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator%(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a negation on the SPCE value.
   *
   * @return The result of the operation.
   */
  SPCE operator-(const SPCE & lhs);

  /**
   * Perform a logical not on the SPCE value.
   *
   * @return The result of the operation.
   */
  SPCE operator!(const SPCE & lhs);

  /**
   * Perform a < between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator<(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a <= between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator<=(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a > between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator>(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a >= between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator>=(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a == between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator==(const SPCE & lhs, const SPCE & rhs);

  /**
   * Perform a != between two SPCE values.
   *
   * @param rhs The right hand side operand.
   * @return The result of the operation.
   */
  SPCE operator!=(const SPCE & lhs, const SPCE & rhs);

}

#endif // TANG_COMPUTEDEXPRESSION_HPP

