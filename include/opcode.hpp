/**
 * @file
 * Declare the Opcodes used in the Bytecode representation of a program.
 */

namespace Tang {
  enum class Opcode {
    INTEGER,  ///< Push an integer onto the stack
    FLOAT,    ///< Push a floating point number onto the stack
    BOOLEAN,  ///< Push a boolean onto the stack
    ADD,      ///< Pop rhs, pop lhs, push lhs + rhs
    SUBTRACT, ///< Pop rhs, pop lhs, push lhs - rhs
    MULTIPLY, ///< Pop rhs, pop lhs, push lhs * rhs
    DIVIDE,   ///< Pop rhs, pop lhs, push lhs / rhs
    MODULO,   ///< Pop rhs, pop lhs, push lhs % rhs
    NEGATIVE, ///< Pop val, push negative val
    NOT,      ///< Pop val, push logical not of val
    LT,       ///< Pop rhs, pop lhs, push lhs < rhs
    LTE,      ///< Pop rhs, pop lhs, push lhs <= rhs
    GT,       ///< Pop rhs, pop lhs, push lhs > rhs
    GTE,      ///< Pop rhs, pop lhs, push lhs >= rhs
    EQ,       ///< Pop rhs, pop lhs, push lhs == rhs
    NEQ,      ///< Pop rhs, pop lhs, push lhs != rhs
    CASTINTEGER, ///< Pop a val, typecast to int, push
    CASTFLOAT,   ///< Pop a val, typecast to float, push
    CASTBOOLEAN, ///< Pop a val, typecast to boolean, push
  };
}

