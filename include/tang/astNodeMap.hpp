/**
 * @file
 * Declare the Tang::AstNodeMap class.
 */

#ifndef TANG_ASTNODEMAP_HPP
#define TANG_ASTNODEMAP_HPP

#include <vector>
#include <map>
#include <string>
#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a map literal.
   *
   * Keys can only be strings.
   */
  class AstNodeMap : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param contents The contents of the map.
     * @param location The location associated with the expression.
     */
    AstNodeMap(std::vector<std::pair<std::string, std::shared_ptr<Tang::AstNode>>> contents, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The contents of the array.
     */
    std::vector<std::pair<std::string, std::shared_ptr<Tang::AstNode>>> contents;
  };
}

#endif // TANG_ASTNODEMAP_HPP

