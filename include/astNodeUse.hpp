/**
 * @file
 * Declare the Tang::AstNodeUse class.
 */

#ifndef TANG_ASTNODEUSE_HPP
#define TANG_ASTNODEUSE_HPP

#include <string>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents the inclusion of a library into the script.
   *
   * A library or the library attributes will be represented by the `alias`
   * within the script.
   */
  class AstNodeUse : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param expression The library expression.
     * @param alias An alias used to access the library expression within the
     *   script.
     * @param location The location associated with the expression.
     */
    AstNodeUse(std::shared_ptr<AstNode> expression, const std::string & alias, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

    /**
     * The alias to use for the library expression.
     */
    std::string alias;

    /**
     * The library expression.
     */
    std::shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODEUSE_HPP

