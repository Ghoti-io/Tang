/**
 * @file
 * Declare the Tang::ComputedExpressionCompiledFunction class.
 */

#ifndef TANG_COMPUTEDEXPRESSIONCOMPILEDFUNCTION_HPP
#define TANG_COMPUTEDEXPRESSIONCOMPILEDFUNCTION_HPP

#include "computedExpression.hpp"

namespace Tang {
  /**
   * Represents a Compiled Function declared in the script.
   */
  class ComputedExpressionCompiledFunction : public ComputedExpression {
    public:
      /**
       * Construct an CompiledFunction.
       *
       * @param pc The bytecode address of the start of the function.
       */
      ComputedExpressionCompiledFunction(Tang::integer_t pc);

      virtual std::string dump() const override;
      GarbageCollected makeCopy() const override;
      virtual GarbageCollected __equal(const GarbageCollected & rhs) const override;

    private:
      /**
       * The bytecode addres of the start of the function.
       */
      Tang::integer_t pc;
  };
}

#endif // TANG_COMPUTEDEXPRESSIONCOMPILEDFUNCTION_HPP

