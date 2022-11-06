/**
 * @file
 * Declare the Tang::AstNodeString class.
 */

#ifndef TANG_ASTNODESTRING_HPP
#define TANG_ASTNODESTRING_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a string literal.
   */
  class AstNodeString : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param text The string to represent.
     * @param location The location associated with the expression.
     */
    AstNodeString(const string & text, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;

  private:
    /**
     * The string value being stored.
     */
    std::string val;
  };
}

#endif // TANG_ASTNODESTRING_HPP

