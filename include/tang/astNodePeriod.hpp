/**
 * @file
 * Declare the Tang::AstNodePeriod class.
 */

#ifndef TANG_ASTNODEPERIOD_HPP
#define TANG_ASTNODEPERIOD_HPP

#include "astNode.hpp"

namespace Tang {
  /**
   * An AstNode that represents a member access (period) into an object.
   */
  class AstNodePeriod : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The lhs on which the member access will be performed
     * @param rhs The rhs identifier.
     * @param location The location associated with the expression.
     */
    AstNodePeriod(std::shared_ptr<AstNode> lhs, std::string rhs, Tang::location location);

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual void compilePreprocess(Program & program, PreprocessState state) const override;

  private:
    /**
     * The lhs into which we will rhs.
     */
    std::shared_ptr<AstNode> lhs;

    /**
     * The rhs expression.
     */
    std::string rhs;
  };
}

#endif // TANG_ASTNODEPERIOD_HPP

