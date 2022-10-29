/**
 * @file
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
 * If the vector is not large enough, an error message is appended to the
 * output string and no further opcodes are printed.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define DUMPPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) \
    return out.str() + "Error: Opcode truncated\n"

string Program::dumpBytecode() const {
  stringstream out;
  int opcodeWidth{12};
  int offsetWidth{(int)ceil(log10(this->bytecode.size()))};
  size_t pc{0};

  while(pc < this->bytecode.size()) {
    out << setw(offsetWidth) << setfill('0') << right << pc << " "
      << setw(opcodeWidth) << setfill(' ') << left;

    switch((Opcode)this->bytecode[pc]) {
      case Opcode::INTEGER: {
        DUMPPROGRAMCHECK(1);
        out << "INTEGER" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        DUMPPROGRAMCHECK(1);
        out << "FLOAT" << bit_cast<double>(this->bytecode[pc + 1]);
        pc += 2;
        break;
      }
      case Opcode::ADD: {
        out << "ADD";
        ++pc;
        break;
      }
      case Opcode::SUBTRACT: {
        out << "SUBTRACT";
        ++pc;
        break;
      }
      case Opcode::MULTIPLY: {
        out << "MULTIPLY";
        ++pc;
        break;
      }
      case Opcode::DIVIDE: {
        out << "DIVIDE";
        ++pc;
        break;
      }
      case Opcode::MODULO: {
        out << "MODULO";
        ++pc;
        break;
      }
      case Opcode::NEGATIVE: {
        out << "NEGATIVE";
        ++pc;
        break;
      }
      case Opcode::CASTINTEGER: {
        out << "CASTINTEGER";
        ++pc;
        break;
      }
      case Opcode::CASTFLOAT: {
        out << "CASTFLOAT";
        ++pc;
        break;
      }
      default: {}
    }
    out << endl;
  }
  return out.str();
}

