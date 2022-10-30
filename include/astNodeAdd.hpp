/**
 * @file
 * Declare the Tang::AstNodeAdd class.
 */

#ifndef TANG_ASTNODEADD_HPP
#define TANG_ASTNODEADD_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a "+" expression
   */
  class AstNodeAdd: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param location The location associated with the expression.
     */
    AstNodeAdd(AstNode * lhs, AstNode * rhs, Tang::location location);

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

#endif // TANG_ASTNODEADD_HPP

