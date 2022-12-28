/**
 * @file
 * Define the Tang::Program::dumpBytecode method.
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
    if (this->annotations.count(pc)) {
      // There is an annotation for this bytecode offset.
      out << setw(offsetWidth + 3) << right << "; " << this->annotations.at(pc) << endl;
    }
    out << setw(offsetWidth) << setfill('0') << right << pc << " "
      << setw(opcodeWidth) << setfill(' ') << left;

    switch((Opcode)this->bytecode[pc]) {
      case Opcode::POP: {
        out << "POP";
        ++pc;
        break;
      }
      case Opcode::PEEK: {
        DUMPPROGRAMCHECK(1);
        out << "PEEK" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::POKE: {
        DUMPPROGRAMCHECK(1);
        out << "POKE" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::COPY: {
        DUMPPROGRAMCHECK(1);
        out << "COPY" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::JMP: {
        DUMPPROGRAMCHECK(1);
        out << "JMP" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::JMPF: {
        DUMPPROGRAMCHECK(1);
        out << "JMPF" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::JMPF_POP: {
        DUMPPROGRAMCHECK(1);
        out << "JMPF_POP" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::JMPT: {
        DUMPPROGRAMCHECK(1);
        out << "JMPT" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::JMPT_POP: {
        DUMPPROGRAMCHECK(1);
        out << "JMPT_POP" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::NULLVAL: {
        out << "NULLVAL";
        ++pc;
        break;
      }
      case Opcode::INTEGER: {
        DUMPPROGRAMCHECK(1);
        out << "INTEGER" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        DUMPPROGRAMCHECK(1);
        out << "FLOAT" << bit_cast<float_t>(this->bytecode[pc + 1]);
        pc += 2;
        break;
      }
      case Opcode::BOOLEAN: {
        DUMPPROGRAMCHECK(1);
        out << "BOOLEAN" << (this->bytecode[pc + 1] ? "true" : "false");
        pc += 2;
        break;
      }
      case Opcode::STRING: {
        DUMPPROGRAMCHECK(2);
        UnicodeString::Type type = (UnicodeString::Type)this->bytecode[pc + 1];
        auto size = this->bytecode[pc + 2];
        auto bytes = ceil((double)size / sizeof(uinteger_t));
        DUMPPROGRAMCHECK(2 + bytes);
        string temp{};
        for (size_t i = 0; i < bytes; ++i) {
          for (size_t j = 0; j < sizeof(uinteger_t); ++j) {
            if ((integer_t)((i * sizeof(uinteger_t)) + j) < size) {
              temp += (unsigned char)((this->bytecode[pc + 3 + i] >> (8 * (sizeof(uinteger_t) - 1 - j))) & 0xFF);
            }
          }
        }
        out << "STRING" << (
          type == UnicodeString::Type::Trusted
            ? "\""
            : type == UnicodeString::Type::Untrusted
              ? "!\""
              : "%\""
        ) << temp << "\"";
        pc += bytes + 3;
        break;
      }
      case Opcode::ARRAY: {
        DUMPPROGRAMCHECK(1);
        out << "ARRAY" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::MAP: {
        DUMPPROGRAMCHECK(1);
        out << "MAP" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::LIBRARY: {
        out << "LIBRARY";
        ++pc;
        break;
      }
      case Opcode::LIBRARYSAVE: {
        DUMPPROGRAMCHECK(1);
        out << "LIBRARYSAVE" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::LIBRARYCOPY: {
        DUMPPROGRAMCHECK(1);
        out << "LIBRARYCOPY" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::FUNCTION: {
        DUMPPROGRAMCHECK(2);
        out << "FUNCTION" << this->bytecode[pc + 1] << " " << this->bytecode[pc + 2];
        pc += 3;
        break;
      }
      case Opcode::ASSIGNINDEX: {
        out << "ASSIGNINDEX";
        ++pc;
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
      case Opcode::NOT: {
        out << "NOT";
        ++pc;
        break;
      }
      case Opcode::LT: {
        out << "LT";
        ++pc;
        break;
      }
      case Opcode::LTE: {
        out << "LTE";
        ++pc;
        break;
      }
      case Opcode::GT: {
        out << "GT";
        ++pc;
        break;
      }
      case Opcode::GTE: {
        out << "GTE";
        ++pc;
        break;
      }
      case Opcode::EQ: {
        out << "EQ";
        ++pc;
        break;
      }
      case Opcode::NEQ: {
        out << "NEQ";
        ++pc;
        break;
      }
      case Opcode::PERIOD: {
        out << "PERIOD";
        ++pc;
        break;
      }
      case Opcode::INDEX: {
        out << "INDEX";
        ++pc;
        break;
      }
      case Opcode::SLICE: {
        out << "SLICE";
        ++pc;
        break;
      }
      case Opcode::GETITERATOR: {
        out << "GETITERATOR";
        ++pc;
        break;
      }
      case Opcode::ITERATORNEXT: {
        out << "ITERATORNEXT";
        ++pc;
        break;
      }
      case Opcode::ISITERATOREND: {
        out << "ISITERATOREND";
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
      case Opcode::CASTBOOLEAN: {
        out << "CASTBOOLEAN";
        ++pc;
        break;
      }
      case Opcode::CASTSTRING: {
        out << "CASTSTRING";
        ++pc;
        break;
      }
      case Opcode::CALLFUNC: {
        DUMPPROGRAMCHECK(1);
        out << "CALLFUNC" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::RETURN: {
        DUMPPROGRAMCHECK(1);
        out << "RETURN" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      case Opcode::PRINT: {
        out << "PRINT";
        ++pc;
        break;
      }
      default: {}
    }
    out << endl;
  }
  return out.str();
}

