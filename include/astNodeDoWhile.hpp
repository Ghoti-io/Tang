/**
 * @file
 * Declare the Tang::AstNodeDoWhile class.
 */

#ifndef TANG_ASTNODEDOWHILE_HPP
#define TANG_ASTNODEDOWHILE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a do..while statement.
   */
  class AstNodeDoWhile : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param condition The expression which determines whether the thenBlock
     *   or elseBlock is executed.
     * @param codeBlock The statement executed when the condition is true.
     * @param location The location associated with the expression.
     */
    AstNodeDoWhile(shared_ptr<AstNode> condition, shared_ptr<AstNode> codeBlock, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The expression which determines whether or not the code block will
     * continue to be executed.
     */
    shared_ptr<AstNode> condition;

    /**
     * The code block executed when the condition is true.
     */
    shared_ptr<AstNode> codeBlock;
  };
}

#endif // TANG_ASTNODEDOWHILE_HPP

