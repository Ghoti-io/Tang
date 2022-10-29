/**
 * @file
 */

#ifndef TANG_ASTNODEMULTIPLY_HPP
#define TANG_ASTNODEMULTIPLY_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a "*" expression
   */
  class AstNodeMultiply: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param loc The location associated with the expression.
     * @location The location associated with this node.
     */
    AstNodeMultiply(AstNode * lhs, AstNode * rhs, Tang::location loc) : AstNode(loc), lhs{lhs}, rhs{rhs} {}

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The left hand side expression.
     */
    AstNode * lhs;

    /**
     * The right hand side expression.
     */
    AstNode * rhs;
  };
}

#endif // TANG_ASTNODEMULTIPLY_HPP

