/**
 * @file
 * Declare the Tang::AstNodeBinary class.
 */

#ifndef TANG_ASTNODEBINARY_HPP
#define TANG_ASTNODEBINARY_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a binary expression.
   */
  class AstNodeBinary: public AstNode {
  public:
    /**
     * Indicates the type of binary expression that this node represents.
     */
    enum Operation {
      Add,              ///< Indicates lhs + rhs
      Subtract,         ///< Indicates lhs - rhs
      Multiply,         ///< Indicates lhs * rhs
      Divide,           ///< Indicates lhs / rhs
      Modulo,           ///< Indicates lhs % rhs
      LessThan,         ///< Indicates lhs < rhs
      LessThanEqual,    ///< Indicates lhs <= rhs
      GreaterThan,      ///< Indicates lhs > rhs
      GreaterThanEqual, ///< Indicates lhs >= rhs
      Equal,            ///< Indicates lhs == rhs
      NotEqual,         ///< Indicates lhs != rhs
      And,              ///< Indicates lhs && rhs with short-circuit evaluation
      Or,               ///< Indicates lhs || rhs with short-circuit evaluation
    };

    /**
     * The constructor.
     *
     * @param op The Tang::AstNodeBinary::Operation to perform.
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param location The location associated with the expression.
     */
    AstNodeBinary(Operation op, std::shared_ptr<AstNode> lhs, std::shared_ptr<AstNode> rhs, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void collectIdentifiers(Program & program) const override;
    virtual void collectStrings(Program & program) const override;

  private:
    /**
     * The binary operation performed.
     */
    Operation op;

    /**
     * The left hand side expression.
     */
    std::shared_ptr<AstNode> lhs;

    /**
     * The right hand side expression.
     */
    std::shared_ptr<AstNode> rhs;
  };
}

#endif // TANG_ASTNODEBINARY_HPP

