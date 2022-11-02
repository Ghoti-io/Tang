/**
 * @file
 * Declare the Tang::AstNodeIdentifier class.
 */

#ifndef TANG_ASTNODEIDENTIFIER_HPP
#define TANG_ASTNODEIDENTIFIER_HPP

#include <string>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an identifier.
   *
   * Identifier names are represented by a string.
   */
  class AstNodeIdentifier : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param name The name of the identifier
     * @param location The location associated with the expression.
     */
    AstNodeIdentifier(const std::string & name, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compileIdentifiers(Program & program) const override;

    /**
     * The name of the identifier.
     */
    std::string name;
  };
}

#endif // TANG_ASTNODEIDENTIFIER_HPP

