/**
 * @file
 */

#include <sstream>
#include <iomanip>
#include <cmath>
#include "program.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"
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

Tang::Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr}, error{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

void Program::execute() {}

void Program::parse() {
  stringstream ss{this->code};
  TangScanner scanner{ss, std::cout};
  TangParser parser{scanner, this->ast, this->error};
  parser.parse();
}

void Program::compile() {
  this->ast->compile(*this);
}

string Program::getCode() const {
  return this->code;
}

optional<const AstNode *> Program::getAst() const {
  if (this->ast) {
    return this->ast;
  }
  return nullopt;
}

void Program::addBytecode(uint64_t op) {
  this->bytecode.push_back(op);
}

string Program::dumpBytecode() const {
  stringstream out;
  int opcodeWidth{12};
  int offsetWidth{(int)ceil(log10(this->bytecode.size()))};
  size_t pc{0};

  while(pc < this->bytecode.size()) {
    out << setw(offsetWidth) << setfill('0') << right << pc << " "
      << setw(opcodeWidth) << setfill(' ') << left;

    switch((Opcode)this->bytecode[pc]) {
      case Opcode::OP_INTEGER: {
        DUMPPROGRAMCHECK(1);
        out << "OP_INTEGER" << this->bytecode[pc + 1];
        pc += 2;
        break;
      }
      default: {}
    }
    out << endl;
  }
  return out.str();
}

