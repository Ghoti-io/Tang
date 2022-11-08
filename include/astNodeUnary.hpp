/**
 * @file
 * Declare the Tang::AstNodeUnary class.
 */

#ifndef TANG_ASTNODEUNARY_HPP
#define TANG_ASTNODEUNARY_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a unary negation.
   */
  class AstNodeUnary : public AstNode {
  public:
    /**
     * The type of operation.
     */
    enum Operator {
      Negative, ///< Compute the negative (-).
      Not,      ///< Compute the logical not (!).
    };

    /**
     * The constructor.
     *
     * @param op The Tang::AstNodeUnary::Operator to apply to the operand.
     * @param operand The expression to be operated on.
     * @param location The location associated with the expression.
     */
    AstNodeUnary(Operator op, shared_ptr<AstNode> operand, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void collectIdentifiers(Program & program) const override;
    virtual void collectStrings(Program & program) const override;

  private:
    /**
     * The operation which will be applied to the operand.
     */
    Operator op;

    /**
     * The operand to which the operation will be applied.
     */
    shared_ptr<AstNode> operand;
  };
}

#endif // TANG_ASTNODEUNARY_HPP

