/**
 * @file
 * Declare the Tang::AstNodeLibrary class.
 */

#ifndef TANG_ASTNODELIBRARY_HPP
#define TANG_ASTNODELIBRARY_HPP

#include <string>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an identifier.
   *
   * Library names are represented by a string.
   */
  class AstNodeLibrary : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param expression The library expression.
     * @param name The name of the identifier.
     * @param location The location associated with the expression.
     */
    AstNodeLibrary(std::shared_ptr<AstNode> expression, const std::string & name, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

    /**
     * The alias to use for the library expression.
     */
    std::string name;

    /**
     * The library expression.
     */
    std::shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODELIBRARY_HPP

