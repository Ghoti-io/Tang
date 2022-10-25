/**
 * @file
 */

#ifndef TANG_COMPUTEDEXPRESSION_HPP
#define TANG_COMPUTEDEXPRESSION_HPP

#include <cstdint>
#include <string>

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

  };

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
    ComputedExpressionInteger(int64_t val);

    virtual std::string dump() const override;
    ComputedExpression * makeCopy() const override;
    virtual bool is_equal(const int & val) const override;
    virtual bool is_equal(const double & val) const override;

  private:
    /**
     * The integer value.
     */
    int64_t val;
  };

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

  private:
    /**
     * The float value.
     */
    double val;
  };
}

#endif // TANG_COMPUTEDEXPRESSION_HPP

