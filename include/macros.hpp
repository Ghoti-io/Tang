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

#define TANGVERSION "0.0.0 alpha"

#define OPCODE_FIND_INDEX(EXPRESSION, INDEX) \
  {\
    auto & identifier = program.getIdentifiers(); \
    if (typeid(*(EXPRESSION)) == typeid(AstNodeIdentifier)) { \
      auto & name = static_cast<AstNodeIdentifier &>(*(EXPRESSION)).name; \
      if (identifier.count(name)) { \
        INDEX = identifier.at(name); \
      } \
    } \
    else if (typeid(*(EXPRESSION)) == typeid(AstNodeString)) { \
      auto & strings = program.getStrings(); \
      auto & stringConv = static_cast<AstNodeString &>(*(EXPRESSION)); \
      auto & val = stringConv.getVal(); \
      auto & type = stringConv.getType(); \
      if (strings.count({val, type})) { \
        INDEX = strings.at({val, type}) + program.getIdentifiers().size(); \
      } \
    } \
  }

#define UNARYOP(OPERAND, OP_S, OP_I) \
  integer_t index{-1}; \
  OPCODE_FIND_INDEX((OPERAND), index); \
  if (index >= 0) { \
    program.addBytecode((uinteger_t)Opcode:: OP_I); \
    program.addBytecode((uinteger_t)index); \
  } \
  else { \
    (OPERAND)->compile(program); \
    program.addBytecode((uinteger_t)Opcode:: OP_S); \
  }

#define BINARYOP(LHS, RHS, OP_SS, OP_SI, OP_IS, OP_II) \
  integer_t lhsIndex{-1}, rhsIndex{-1}; \
  OPCODE_FIND_INDEX((LHS), lhsIndex); \
  OPCODE_FIND_INDEX((RHS), rhsIndex); \
  if (lhsIndex >= 0) { \
    if (rhsIndex >= 0) { \
      program.addBytecode((uinteger_t)Opcode:: OP_II); \
      program.addBytecode((uinteger_t)lhsIndex); \
      program.addBytecode((uinteger_t)rhsIndex); \
    } \
    else { \
      (RHS)->compile(program); \
      program.addBytecode((uinteger_t)Opcode:: OP_IS); \
      program.addBytecode((uinteger_t)lhsIndex); \
    } \
  } \
  else { \
    if (rhsIndex >= 0) { \
      (LHS)->compile(program); \
      program.addBytecode((uinteger_t)Opcode:: OP_SI); \
      program.addBytecode((uinteger_t)rhsIndex); \
    } \
    else { \
      (LHS)->compile(program); \
      (RHS)->compile(program); \
      program.addBytecode((uinteger_t)Opcode:: OP_SS); \
    } \
  }

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
  using uinteger_t = uint32_t;

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

