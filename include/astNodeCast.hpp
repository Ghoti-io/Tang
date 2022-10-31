/**
 * @file
 * Declare the Tang::AstNodeCast class.
 */

#ifndef TANG_ASTNODECAST_HPP
#define TANG_ASTNODECAST_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a typecast of an expression.
   */
  class AstNodeCast : public AstNode {
  public:
    /**
     * The possible types that can be cast to.
     */
    enum Type {
      Integer,
      Float,
      Boolean,
    };

    /**
     * The constructor.
     *
     * @param targetType The target type that the expression will be cast to.
     * @param expression The expression to be typecast.
     * @param location The location associated with this node.
     */
    AstNodeCast(Type targetType, shared_ptr<AstNode> expression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual shared_ptr<AstNode> makeCopy() const override;

  private:
    /**
     * The target type.
     */
    Type targetType;

    /**
     * The expression being typecast.
     */
    shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODECAST_HPP

