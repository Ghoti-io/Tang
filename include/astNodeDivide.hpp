/**
 * @file
 * Declare the Tang::AstNodeDivide class.
 */

#ifndef TANG_ASTNODEDIVIDE_HPP
#define TANG_ASTNODEDIVIDE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a "/" expression
   */
  class AstNodeDivide: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param location The location associated with the expression.
     */
    AstNodeDivide(AstNode * lhs, AstNode * rhs, Tang::location location);

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

#endif // TANG_ASTNODEDIVIDE_HPP

