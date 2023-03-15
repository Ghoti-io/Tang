/**
 * @file
 * Declare the Tang::AstNodeContinue class.
 */

#ifndef TANG_ASTNODECONTINUE_HPP
#define TANG_ASTNODECONTINUE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a `continue` statement.
   */
  class AstNodeContinue : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param location The location associated with the expression.
     */
    AstNodeContinue(Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
  };
}

#endif // TANG_ASTNODECONTINUE_HPP

