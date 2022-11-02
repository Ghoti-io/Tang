/**
 * @file
 * Declare the Tang::AstNodeFloat class.
 */

#ifndef TANG_ASTNODEFLOAT_HPP
#define TANG_ASTNODEFLOAT_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an float literal.
   *
   * Integers are represented by the `long double` type, and so are limited in
   * range by that of the underlying type.
   */
  class AstNodeFloat: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param number The number to represent.
     * @param location The location associated with the expression.
     */
    AstNodeFloat(double number, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;

  private:
    /**
     * The float value being stored.
     */
    double val;
  };
}

#endif // TANG_ASTNODEFLOAT_HPP

