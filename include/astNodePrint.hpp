/**
 * @file
 * Declare the Tang::AstNodePrint class.
 */

#ifndef TANG_ASTNODEPRINT_HPP
#define TANG_ASTNODEPRINT_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a print typeeration.
   */
  class AstNodePrint : public AstNode {
  public:
    /**
     * The type of print() requested.
     */
    enum Type {
      Default, ///< Use the default print.
    };

    /**
     * The constructor.
     *
     * @param type The Tang::AstNodePrint::Type being requested.
     * @param expression The expression to be printed.
     * @param location The location associated with the expression.
     */
    AstNodePrint(Type type, std::shared_ptr<AstNode> expression, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The type of print() being requested.
     */
    Type type;

    /**
     * The expression to be printed.
     */
    std::shared_ptr<AstNode> expression;
  };
}

#endif // TANG_ASTNODEPRINT_HPP

