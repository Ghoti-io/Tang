/**
 * @file
 * Define the Tang::AstNode and its associated/derivative classes.
 */

#ifndef TANG_ASTNODE_HPP
#define TANG_ASTNODE_HPP

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
     * @param loc The location associated with this node.
     */
    AstNode(Tang::location loc) : location {loc} {}

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
     * Provide a copy of the AstNode (recursively, if appropriate).
     *
     * @return A pointer to a new AstNode that is a copy of the current
     *   AstNode.
     */
    virtual AstNode * makeCopy() const;
  };
}

#endif // TANG_ASTNODE_HPP

