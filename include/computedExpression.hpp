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

  private:
    /**
     * The integer value.
     */
    int64_t val;
  };
}

#endif // TANG_COMPUTEDEXPRESSION_HPP

