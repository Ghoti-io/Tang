/**
 * @file
 * Declare the Tang::AstNodeSlice class.
 */

#ifndef TANG_ASTNODESLICE_HPP
#define TANG_ASTNODESLICE_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a ternary expression.
   */
  class AstNodeSlice : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param collection The collection which will be sliced.
     * @param begin The begin index position of the slice.
     * @param end The end index position of the slice.
     * @param skip The skip index position of the slice.
     * @param location The location associated with the expression.
     */
    AstNodeSlice(std::shared_ptr<AstNode> collection, std::shared_ptr<AstNode> begin, std::shared_ptr<AstNode> end, std::shared_ptr<AstNode> slice, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The collection which will be sliced.
     */
    std::shared_ptr<AstNode> collection;

    /**
     * The begin index position of the slice.
     */
    std::shared_ptr<AstNode> begin;

    /**
     * The end index position of the slice.
     */
    std::shared_ptr<AstNode> end;

    /**
     * The skip index position of the slice.
     */
    std::shared_ptr<AstNode> skip;
  };
}

#endif // TANG_ASTNODESLICE_HPP

