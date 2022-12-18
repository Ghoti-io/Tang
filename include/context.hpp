/**
 * @file
 * Declare the Tang::Context class.
 */

namespace Tang {
  class Context;
}

#ifndef TANG_CONTEXT_HPP
#define TANG_CONTEXT_HPP

#include <vector>
#include "program.hpp"
#include "computedExpression.hpp"

namespace Tang {
  /**
   * Holds all environment variables specific to the execution of a program.
   */
  class Context {
  public:
    Context();
  };
}

#endif // TANG_CONTEXT_HPP

