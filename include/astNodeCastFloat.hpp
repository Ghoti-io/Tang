/**
 * @file
 * Declare the Tang::AstNodeFloat class.
 */

#ifndef TANG_ASTNODECASTFLOAT_HPP
#define TANG_ASTNODECASTFLOAT_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a typecast to a float.
   */
  class AstNodeCastFloat : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param expression The expression to be typecast.
     * @param location The location associated with this node.
     */
    AstNodeCastFloat(AstNode * expression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The expression being typecast.
     */
    AstNode * expression;
  };
}

#endif // TANG_ASTNODECASTFLOAT_HPP

