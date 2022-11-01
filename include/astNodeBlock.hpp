/**
 * @file
 * Declare the Tang::AstNodeBlock class.
 */

#ifndef TANG_ASTNODEBLOCK_HPP
#define TANG_ASTNODEBLOCK_HPP

#include <vector>
#include <memory>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a code block.
   */
  class AstNodeBlock : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param statements The statements of the code block.
     * @param location The location associated with the expression.
     */
    AstNodeBlock(const std::vector<std::shared_ptr<AstNode>> & statements, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual shared_ptr<AstNode> makeCopy() const override;
    virtual void compileIdentifiers(Program & program) const override;

  private:
    /**
     * The statements included in the code block.
     */
    std::vector<std::shared_ptr<AstNode>> statements;
  };
}

#endif // TANG_ASTNODEBLOCK_HPP

