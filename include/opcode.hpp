/**
 * @file
 * Declare the Opcodes used in the Bytecode representation of a program.
 */

namespace Tang {
  enum class Opcode {
    INTEGER,  ///< Push an integer onto the stack
    FLOAT,    ///< Push a floating point number onto the stack
  };
}

