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
     * @param location The location associated with the expression.
     */
    AstNodeLibrary(const std::string & libraryName, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

    /**
     * The library name.
     */
    std::string libraryName;
  };
}

#endif // TANG_ASTNODELIBRARY_HPP

