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

    /**
     * Return a shared pointer to the AstNode serving as the Collection.
     *
     * @return The collection into which we will index.
     */
    const std::shared_ptr<const AstNode> getCollection() const;

    /**
     * Return a shared pointer to the AstNode serving as the Index.
     *
     * @return The index expression.
     */
    const std::shared_ptr<const AstNode> getIndex() const;

  private:
    /**
     * The collection into which we will index.
     */
    std::shared_ptr<AstNode> collection;

    /**
     * The index expression.
     */
    std::shared_ptr<AstNode> index;
  };
}

#endif // TANG_ASTNODEINDEX_HPP

