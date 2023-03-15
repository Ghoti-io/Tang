/**
 * @file
 * Declare the Tang::Context class.
 */

namespace Tang {
  class Context;
}

#ifndef TANG_CONTEXT_HPP
#define TANG_CONTEXT_HPP

#include <any>
#include <map>
#include <string>
#include <vector>
#include "macros.hpp"
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Holds all environment variables specific to the execution of a program.
   */
  class Context {
  public:
    /**
     * Default constructor.
     */
    Context(ContextData && data);

    /**
     * Holds arbitrary data for use in the program execution.
     */
    ContextData data;

    /**
     * The output result from the program execution.
     */
    std::string out;

    /**
     * The output result from the program execution, as a
     * ComputedExpressionString.
     */
    SPCE computedExpressionOut;

    /**
     * The result of the Program execution.
     */
    SPCE result;
  };
}

#endif // TANG_CONTEXT_HPP

