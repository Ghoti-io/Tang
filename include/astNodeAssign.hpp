/**
 * @file
 * Declare the Tang::AstNodeAssign class.
 */

#ifndef TANG_ASTNODEASSIGN_HPP
#define TANG_ASTNODEASSIGN_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a binary expression.
   */
  class AstNodeAssign: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param location The location associated with the expression.
     */
    AstNodeAssign(std::shared_ptr<AstNode> lhs, std::shared_ptr<AstNode> rhs, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual shared_ptr<AstNode> makeCopy() const override;
    virtual void compileIdentifiers(Program & program) const override;

  private:
    /**
     * The left hand side expression.
     */
    std::shared_ptr<AstNode> lhs;

    /**
     * The right hand side expression.
     */
    std::shared_ptr<AstNode> rhs;
  };
}

#endif // TANG_ASTNODEASSIGN_HPP

