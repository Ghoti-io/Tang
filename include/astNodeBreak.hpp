/**
 * @file
 * Declare the Tang::AstNodeBreak class.
 */

#ifndef TANG_ASTNODEBREAK_HPP
#define TANG_ASTNODEBREAK_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a `break` statement.
   */
  class AstNodeBreak : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param location The location associated with the expression.
     */
    AstNodeBreak(Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
  };
}

#endif // TANG_ASTNODEBREAK_HPP

