/**
 * @file
 * Declare the Tang::AstNodeFunctionDeclaration class.
 */

#ifndef TANG_ASTNODEFUNCTIONDECLARATION_HPP
#define TANG_ASTNODEFUNCTIONDECLARATION_HPP

#include <string>
#include <vector>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a function declaration.
   */
  class AstNodeFunctionDeclaration : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param name The name of the function.
     * @param arguments The arguments expected to be provided.
     * @param codeBlock The code executed as part of the function. 
     * @param location The location associated with the function declaration.
     */
    AstNodeFunctionDeclaration(std::string name, std::vector<std::string> arguments, shared_ptr<AstNode> codeBlock, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The name of the function.
     */
    std::string name;

    /**
     * The arguments expected to be provided.
     */
    std::vector<std::string> arguments;

    /**
     * The code block executed when the condition is true.
     */
    shared_ptr<AstNode> codeBlock;
  };
}

#endif // TANG_ASTNODEFUNCTIONDECLARATION_HPP

