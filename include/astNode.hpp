/**
 * @file
 * Declare the Tang::AstNode base class.
 */

#ifndef TANG_ASTNODE_HPP
#define TANG_ASTNODE_HPP

#include <memory>
#include <string>
#include "location.hh"
#include "macros.hpp"
#include "program.hpp"

namespace Tang {
  class Program;

  /**
   * Base class for representing nodes of an Abstract Syntax Tree (AST).
   *
   * By default, it will represent a NULL value.
   * There will be *many* derived classes, each one conveying the syntactic
   * meaning of the code that it represents.
   */
  class AstNode {
  public:
    /**
     * The generic constructor.  It should never be called on its own.
     *
     * @param location The location associated with this node.
     */
    AstNode(Tang::location location);

    /**
     * The object destructor.
     */
    virtual ~AstNode();

    /**
     * Return a string that describes the contents of the node.
     *
     * @param indent A string used to indent the dump.
     * @return The value as a string.
     */
    virtual std::string dump(std::string indent = "") const;

    /**
     * Compile the ast of the provided Tang::Program.
     *
     * @param program The Program which will hold the generated Bytecode.
     */
    virtual void compile(Tang::Program & program) const;

    /**
     * Run any preprocess analysis needed before compilation.
     *
     * @param program The Tang::Program that is being compiled.
     */
    virtual void compilePreprocess(Program & program) const;

  private:
    /**
     * The location associated with this node.
     */
    Tang::location location;

  };
}

#endif // TANG_ASTNODE_HPP

