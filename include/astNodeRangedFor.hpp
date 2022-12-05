/**
 * @file
 * Declare the Tang::AstNodeRangedFor class.
 */

#ifndef TANG_ASTNODERANGEDFOR_HPP
#define TANG_ASTNODERANGEDFOR_HPP

#include "astNode.hpp"
#include "astNodeIdentifier.hpp"

namespace Tang {
  /**
   * An AstNode that represents a ranged for() statement.
   */
  class AstNodeRangedFor : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param target The target variable to hold the value for the current
     *   loop iteration.
     * @param collection The collection through which to iterate.
     * @param codeBlock The statement executed when the condition is true.
     * @param location The location associated with the expression.
     */
    AstNodeRangedFor(shared_ptr<AstNodeIdentifier> target, shared_ptr<AstNode> collection, shared_ptr<AstNode> codeBlock, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The target variable to hold the value for the current loop iteration.
     */
    shared_ptr<AstNodeIdentifier> target;

    /**
     * The collection through which to iterate.
     */
    shared_ptr<AstNode> collection;

    /**
     * The code block executed when the condition is true.
     */
    shared_ptr<AstNode> codeBlock;

    /**
     * The unique variable name that this iterator will use to persist its
     * state on the stack.
     */
    string iteratorVariableName;
  };
}

#endif // TANG_ASTNODERANGEDFOR_HPP

