/**
 * @file
 * Declare the Tang::AstNodeFunctionCall class.
 */

#ifndef TANG_ASTNODEFUNCTIONCALL_HPP
#define TANG_ASTNODEFUNCTIONCALL_HPP

#include <vector>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a function call.
   */
  class AstNodeFunctionCall: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param function The function being invoked.
     * @param argv The list of arguments provided to the function.
     * @param location The location associated with the expression.
     */
    AstNodeFunctionCall(std::shared_ptr<AstNode> function, std::vector<std::shared_ptr<AstNode>> argv, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void collectIdentifiers(Program & program) const override;
    virtual void collectStrings(Program & program) const override;

  private:
    /**
     * The function being invoked.
     */
    std::shared_ptr<AstNode> function;

    /**
     * The list of arguments provided to the function.
     */
    std::vector<std::shared_ptr<AstNode>> argv;
  };
}

#endif // TANG_ASTNODEFUNCTIONCALL_HPP

