/**
 * @file
 * Declare the Tang::AstNodeNull class.
 */

#ifndef TANG_ASTNODENULL_HPP
#define TANG_ASTNODENULL_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a NULL value
   */
  class AstNodeNull : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param location The location associated with the expression.
     */
    AstNodeNull(Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual shared_ptr<AstNode> makeCopy() const override;

  private:
  };
}

#endif // TANG_ASTNODENULL_HPP

