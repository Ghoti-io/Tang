/**
 * @file
 * Define the Tang::Program::analyze method.
 */

#include <sstream>
#include <iomanip>
#include <bit>
#include <cmath>
#include "program.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

/**
 * Verify the size of the Bytecode vector so that it may be safely accessed.
 *
 * If the vector is not large enough, an empty result is returned.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define DUMPPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) \
    return {{},{}}

pair<OpcodeOffsets, OpcodePositions> Program::analyze() const {
  // Map of Opcode to a vector of position pairs, with the first position
  // being the Bytecode offset, and the second position being the position of
  // the Opcode relative to other Opcodes (e.g., the Nth position).
  OpcodeOffsets opOffsets{};

  // Vector of Opcodes in the order that they appear in the bytecode,
  // followed by their offset within the bytecode.
  OpcodePositions ops{};

  size_t pc{0};

  while(pc < this->bytecode.size()) {
    // Track the position of the opcode.
    opOffsets[(Opcode)this->bytecode[pc]].push_back({pc, ops.size()});
    ops.push_back({(Opcode)this->bytecode[pc], pc});

    switch((Opcode)this->bytecode[pc]) {
      case Opcode::POP: {
        ++pc;
        break;
      }
      case Opcode::PEEK: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::POKE: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::COPY: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::JMP: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::JMPF: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::JMPF_POP: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::JMPT: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::JMPT_POP: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::NULLVAL: {
        ++pc;
        break;
      }
      case Opcode::INTEGER: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::BOOLEAN: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::STRING: {
        DUMPPROGRAMCHECK(2);
        auto size = this->bytecode[pc + 2];
        auto bytes = ceil((double)size / sizeof(uinteger_t));
        DUMPPROGRAMCHECK(2 + bytes);
        pc += bytes + 3;
        break;
      }
      case Opcode::ARRAY: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::MAP: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::LIBRARY: {
        ++pc;
        break;
      }
      case Opcode::LIBRARYSAVE: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::LIBRARYCOPY: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::FUNCTION: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::ASSIGNINDEX: {
        ++pc;
        break;
      }
      case Opcode::ADD_SS: {
        ++pc;
        break;
      }
      case Opcode::ADD_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::ADD_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::ADD_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::SUBTRACT_SS: {
        ++pc;
        break;
      }
      case Opcode::SUBTRACT_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::SUBTRACT_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::SUBTRACT_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::MULTIPLY_SS: {
        ++pc;
        break;
      }
      case Opcode::MULTIPLY_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::MULTIPLY_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::MULTIPLY_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::DIVIDE_SS: {
        ++pc;
        break;
      }
      case Opcode::DIVIDE_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::DIVIDE_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::DIVIDE_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::MODULO_SS: {
        ++pc;
        break;
      }
      case Opcode::MODULO_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::MODULO_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::MODULO_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::NEGATIVE: {
        ++pc;
        break;
      }
      case Opcode::NOT: {
        ++pc;
        break;
      }
      case Opcode::LT_SS: {
        ++pc;
        break;
      }
      case Opcode::LT_SI: {
        pc += 2;
        break;
      }
      case Opcode::LT_IS: {
        pc += 2;
        break;
      }
      case Opcode::LT_II: {
        pc += 3;
        break;
      }
      case Opcode::LTE_SS: {
        ++pc;
        break;
      }
      case Opcode::LTE_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::LTE_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::LTE_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::GT_SS: {
        ++pc;
        break;
      }
      case Opcode::GT_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::GT_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::GT_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::GTE_SS: {
        ++pc;
        break;
      }
      case Opcode::GTE_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::GTE_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::GTE_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::EQ_SS: {
        ++pc;
        break;
      }
      case Opcode::EQ_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::EQ_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::EQ_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::NEQ_SS: {
        ++pc;
        break;
      }
      case Opcode::NEQ_SI: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::NEQ_IS: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::NEQ_II: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::PERIOD: {
        ++pc;
        break;
      }
      case Opcode::INDEX: {
        ++pc;
        break;
      }
      case Opcode::SLICE: {
        ++pc;
        break;
      }
      case Opcode::GETITERATOR: {
        ++pc;
        break;
      }
      case Opcode::ITERATORNEXT: {
        ++pc;
        break;
      }
      case Opcode::ISITERATOREND: {
        ++pc;
        break;
      }
      case Opcode::CASTINTEGER: {
        ++pc;
        break;
      }
      case Opcode::CASTFLOAT: {
        ++pc;
        break;
      }
      case Opcode::CASTBOOLEAN: {
        ++pc;
        break;
      }
      case Opcode::CASTSTRING: {
        ++pc;
        break;
      }
      case Opcode::CALLFUNC: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::CALLFUNC_I: {
        DUMPPROGRAMCHECK(2);
        pc += 3;
        break;
      }
      case Opcode::RETURN: {
        DUMPPROGRAMCHECK(1);
        pc += 2;
        break;
      }
      case Opcode::PRINT: {
        ++pc;
        break;
      }
      default: {}
    }
  }
  return {opOffsets, ops};
}

