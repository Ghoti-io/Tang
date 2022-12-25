/**
 * @file
 * Declare the Tang::AstNodeFor class.
 */

#ifndef TANG_ASTNODEFOR_HPP
#define TANG_ASTNODEFOR_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an if() statement.
   */
  class AstNodeFor : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param initialization The expression to be executed first.
     * @param condition The expression which determines whether the codeBlock
     *   is executed.
     * @param increment The expression to be executed after each codeBlock.
     * @param codeBlock The statement executed when the condition is true.
     * @param location The location associated with the expression.
     */
    AstNodeFor(std::shared_ptr<AstNode> initialization, std::shared_ptr<AstNode> condition, std::shared_ptr<AstNode> increment, std::shared_ptr<AstNode> codeBlock, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The expression to be executed first to set up the for() loop.
     */
    std::shared_ptr<AstNode> initialization;

    /**
     * The expression which determines whether or not the code block will
     * continue to be executed.
     */
    std::shared_ptr<AstNode> condition;

    /**
     * The expression to be executed immediately after the code block.
     */
    std::shared_ptr<AstNode> increment;

    /**
     * The code block executed when the condition is true.
     */
    std::shared_ptr<AstNode> codeBlock;
  };
}

#endif // TANG_ASTNODEFOR_HPP

