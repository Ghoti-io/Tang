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
#include "program.hpp"
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
    Context();

    /**
     * Holds arbitrary data for use in the program execution.
     */
    std::map<std::string, std::any> data;

    /**
     * The output result from the program execution.
     */
    std::string out;

    /**
     * The output result from the program execution, as a
     * ComputedExpressionString.
     */
    GarbageCollected computedExpressionOut;

    /**
     * The result of the Program execution.
     */
    std::optional<GarbageCollected> result;

    /**
     * The program counter of the current instruction.
     */
    size_t pc{0};

    /**
     * The frame pointer (an index into the stack frame).
     */
    size_t fp{0};

    /**
     * The execution stack.
     */
    vector<GarbageCollected> stack;

    /**
     * The stack of program counters used to recover the previous pc when
     * returning from a function.
     */
    vector<size_t> pcStack{};

    /**
     * The stack of frame pointers, used to recover the previous fp when
     * returning from a function.
     */
    vector<size_t> fpStack{};
  };
}

#endif // TANG_CONTEXT_HPP

