/**
 * @file
 * Declare the Tang::AstNode base class.
 */

#ifndef TANG_ASTNODE_HPP
#define TANG_ASTNODE_HPP

#include <memory>
#include <string>
#include "location.hh"
#include "program.hpp"

namespace Tang {
  class Program;

  /**
   * Base class for representing nodes of an Abstract Syntax Tree (AST).
   *
   * There will be *many* derived classes, each one conveying the syntactic
   * meaning of the code that it represents.
   */
  class AstNode {
  protected:
    /**
     * The generic constructor.  It should never be called on its own.
     *
     * @param location The location associated with this node.
     */
    AstNode(Tang::location location);

    /**
     * The location associated with this node.
     */
    Tang::location location;

  public:
    /**
     * The object destructor.
     */
    virtual ~AstNode();

    /**
     * Return a string that describes the contents of the node.
     */
    virtual std::string dump(std::string indent = "") const;

    /**
     * Compile the ast of the provided Tang::Program.
     */
    virtual void compile(Tang::Program & program) const;

    /**
     * Compile a list of all variables in the scope.
     *
     * @param program The Tang::Program that is being compiled.
     */
    virtual void compileIdentifiers(Program & program) const;
  };
}

#endif // TANG_ASTNODE_HPP

