/**
 * @file
 * Declare the Tang::AstNodeReturn class.
 */

#ifndef TANG_ASTNODERETURN_HPP
#define TANG_ASTNODERETURN_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a `return` statement.
   */
  class AstNodeReturn : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param expression The expression to be returned.
     * @param location The location associated with the return statement.
     */
    AstNodeReturn(std::shared_ptr<AstNode> expression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The expression to which the operation will be applied.
     */
    std::shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODERETURN_HPP

