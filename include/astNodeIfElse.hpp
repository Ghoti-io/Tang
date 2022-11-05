/**
 * @file
 * Declare the Tang::AstNodeIfElse class.
 */

#ifndef TANG_ASTNODEIFELSE_HPP
#define TANG_ASTNODEIFELSE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an if..else statement.
   */
  class AstNodeIfElse : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param condition The expression which determines whether the thenBlock
     *   or elseBlock is executed.
     * @param thenBlock The statement executed when the condition is true.
     * @param elseBlock The statement executed when the condition is false.
     * @param location The location associated with the expression.
     */
    AstNodeIfElse(shared_ptr<AstNode> condition, shared_ptr<AstNode> thenBlock, shared_ptr<AstNode> elseBlock, Tang::location location);

    /**
     * The constructor.
     *
     * @param condition The expression which determines whether the thenBlock
     *   or elseBlock is executed.
     * @param thenBlock The statement executed when the condition is true.
     * @param location The location associated with the expression.
     */
    AstNodeIfElse(shared_ptr<AstNode> condition, shared_ptr<AstNode> thenBlock, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void collectIdentifiers(Program & program) const override;

  private:
    /**
     * The expression which determines whether the thenBlock or elseBlock is
     * executed.
     */
    shared_ptr<AstNode> condition;

    /**
     * The statement executed when the condition is true.
     */
    shared_ptr<AstNode> thenBlock;

    /**
     * The statement executed when the condition is false.
     */
    shared_ptr<AstNode> elseBlock;
  };
}

#endif // TANG_ASTNODEIFELSE_HPP

