/**
 * @file
 * Declare the Tang::AstNodeNegative class.
 */

#ifndef TANG_ASTNODENEGATIVE_HPP
#define TANG_ASTNODENEGATIVE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a unary negation.
   */
  class AstNodeNegative : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param operand The expression to negate.
     * @param location The location associated with the expression.
     */
    AstNodeNegative(AstNode * operand, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The operand to which the unary minus will be applied.
     */
    AstNode * operand;
  };
}

#endif // TANG_ASTNODENEGATIVE_HPP

