/**
 * @file
 * Declare the Tang::AstNodeBoolean class.
 */

#ifndef TANG_ASTNODECASTBOOLEAN_HPP
#define TANG_ASTNODECASTBOOLEAN_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a typecast to a boolean.
   */
  class AstNodeCastBoolean : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param expression The expression to be typecast.
     * @param location The location associated with this node.
     */
    AstNodeCastBoolean(shared_ptr<AstNode> expression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual shared_ptr<AstNode> makeCopy() const override;

  private:
    /**
     * The expression being typecast.
     */
    shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODECASTBOOLEAN_HPP

