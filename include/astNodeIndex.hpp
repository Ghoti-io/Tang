/**
 * @file
 * Declare the Tang::AstNodeIndex class.
 */

#ifndef TANG_ASTNODEINDEX_HPP
#define TANG_ASTNODEINDEX_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents an index into a collection.
   */
  class AstNodeIndex : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param collection The collection into which we will index.
     * @param index The index expression.
     * @param location The location associated with the expression.
     */
    AstNodeIndex(std::shared_ptr<AstNode> collection, std::shared_ptr<AstNode> index, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program) const override;

  private:
    /**
     * The collection into which we will index.
     */
    shared_ptr<AstNode> collection;

    /**
     * The index expression.
     */
    shared_ptr<AstNode> index;
  };
}

#endif // TANG_ASTNODEINDEX_HPP

