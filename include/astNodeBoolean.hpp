/**
 * @file
 * Declare the Tang::AstNodeBoolean class.
 */

#ifndef TANG_ASTNODEBOOLEAN_HPP
#define TANG_ASTNODEBOOLEAN_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a boolean literal.
   */
  class AstNodeBoolean : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param val The boolean to represent.
     * @param location The location associated with the expression.
     */
    AstNodeBoolean(bool val, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The boolean value being stored.
     */
    bool val;
  };
}

#endif // TANG_ASTNODEBOOLEAN_HPP

