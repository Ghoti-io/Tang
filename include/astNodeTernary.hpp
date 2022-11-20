/**
 * @file
 * Declare the Tang::AstNodeTernary class.
 */

#ifndef TANG_ASTNODETERNARY_HPP
#define TANG_ASTNODETERNARY_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a ternary expression.
   */
  class AstNodeTernary : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param condition The expression which determines whether the trueExpression
     *   or falseExpression is executed.
     * @param trueExpression The expression executed when the condition is true.
     * @param falseExpression The expression executed when the condition is false.
     * @param location The location associated with the expression.
     */
    AstNodeTernary(shared_ptr<AstNode> condition, shared_ptr<AstNode> trueExpression, shared_ptr<AstNode> falseExpression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The expression which determines whether the trueExpression or
     * falseExpression is executed.
     */
    shared_ptr<AstNode> condition;

    /**
     * The expression executed when the condition is true.
     */
    shared_ptr<AstNode> trueExpression;

    /**
     * The expression executed when the condition is false.
     */
    shared_ptr<AstNode> falseExpression;
  };
}

#endif // TANG_ASTNODETERNARY_HPP

