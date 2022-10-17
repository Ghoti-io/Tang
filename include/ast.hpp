/**
 * @file
 * Define the Tang::AstNode and its associated/derivative classes.
 */

#ifndef TANG_AST_HPP
#define TANG_AST_HPP

#include <string>
#include "location.hh"

namespace Tang {
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

  public:
    /**
     * Return a string that describes the contents of the node.
     */
    virtual std::string dump(std::string indent = "") const;

  private:
    /**
     * The location associated with this node.
     */
    Tang::location location;
  };

  /**
   * An AstNode that represents an integer literal.
   *
   * Integers are represented by the `int64_t` type, and so are limited in
   * range by that of the underlying type.
   */
  class AstNodeInteger : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param number The number to represent.
     * @location The location associated with this node.
     */
    AstNodeInteger(int64_t number, Tang::location loc) : AstNode(loc), val{number} {}

    virtual std::string dump(std::string indent = "") const override;

  private:
    /**
     * The integer value being stored.
     */
    int64_t val;
  };
}

#endif // TANG_AST_HPP

