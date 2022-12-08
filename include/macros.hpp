/**
 * @file
 * Contains generic macros.
 */

#ifndef TANG_MACROS_HPP
#define TANG_MACROS_HPP

#include <vector>

namespace Tang {
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
}

namespace Tang {
  class GarbageCollected;

  /**
   * A function pointer that will be executed as bound to an object.
   */
  using NativeBoundFunction = GarbageCollected (*) (GarbageCollected &, std::vector<GarbageCollected> &);
}
#endif // TANG_MACROS_HPP

