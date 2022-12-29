/**
 * @file
 * Contains generic macros.
 */

#ifndef TANG_MACROS_HPP
#define TANG_MACROS_HPP

#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <any>

#define LIBRARYFUNCTIONWRAPPER (body, argc) \
  ([]([[maybe_unused]] Context & context) { \
  return GarbageCollected::make<ComputedExpressionNativeFunction>( \
    [](vector<GarbageCollected> & args, [[maybe_unused]] Context & context) body , (size_t)argc); \
  })


namespace Tang {
  class Context;
  class GarbageCollected;

  /**
   * Define the size of signed integers used by Tang.
   */
  using integer_t = int32_t;

  /**
   * Define the size of integers used by Tang.
   */
  using uinteger_t = int32_t;

  /**
   * Define the size of floats used by Tang.
   */
  using float_t = float;

  static_assert(sizeof(integer_t) == sizeof(float_t), "Integer and float sizes must be the same.");

  /**
   * A function pointer that will be executed.
   */
  using LibraryFunction = GarbageCollected (*) (Context &);

  /**
   * A function pointer that will be executed as bound to an object.
   */
  using NativeFunction = GarbageCollected (*) (std::vector<GarbageCollected> &, Context &);

  /**
   * A function pointer that will be executed as bound to an object.
   */
  using NativeBoundFunction = GarbageCollected (*) (GarbageCollected &, std::vector<GarbageCollected> &);

  /**
   * A map of method names to LibraryFunction objects.
   */
  using LibraryFunctionMap = std::map<std::string, LibraryFunction>;

  /**
   * A map of method names to NativeBoundFunction objects.
   */
  using NativeBoundFunctionMap = std::map<std::string, std::pair<size_t, NativeBoundFunction>>;

  /**
   * Used to hold arbitrary data which should be made available to a program
   * during the program execution.
   */
  using ContextData = std::unordered_map<std::string, std::any>;
}
#endif // TANG_MACROS_HPP

