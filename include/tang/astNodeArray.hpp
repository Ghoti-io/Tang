/**
 * @file
 * Declare the Tang::AstNodeArray class.
 */

#ifndef TANG_ASTNODEARRAY_HPP
#define TANG_ASTNODEARRAY_HPP

#include <vector>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an array literal.
   */
  class AstNodeArray : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param contents The contents of the array.
     * @param location The location associated with the expression.
     */
    AstNodeArray(std::vector<std::shared_ptr<Tang::AstNode>> contents, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The contents of the array.
     */
    std::vector<std::shared_ptr<Tang::AstNode>> contents;
  };
}

#endif // TANG_ASTNODEARRAY_HPP

