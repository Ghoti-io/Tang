/**
 * @file
 */

#include <sstream>
#include <iomanip>
#include <cmath>
#include <bit>
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

/**
 * Verify the size of the Bytecode vector so that it may be safely accessed.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define EXECUTEPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) { \
    /* TODO push an error on to the stack! */ \
    pc = this->bytecode.size(); \
    break; \
  }

/**
 * Verify the size of the stack vector so that it may be safely accessed.
 *
 * @param x The number of entries that should exist in the stack.
 */
#define STACKCHECK(x) \
  if (stack.size() < (fp + (x))) { \
    /* TODO push an error on to the stack! */ \
    pc = this->bytecode.size(); \
    break; \
  }

Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr}, error{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

Program::~Program() {
  if (this->error) {
    delete this->error;
  }
  if (this->ast) {
    delete this->ast;
  }
}

Program::Program(const Program & program) {
  this->code = program.code;
  this->codeType = program.codeType;
  this->ast = program.ast->makeCopy();
  this->error = new Error(*program.error);
  this->result = program.result;
}

Program::Program(Program && program) {
  swap(this->code, program.code);
  swap(this->codeType, program.codeType);
  swap(this->ast, program.ast);
  swap(this->error, program.error);
  swap(this->result, program.result);
}

Program & Program::operator=(const Program & program) {
  this->code = program.code;
  this->codeType = program.codeType;

  // `ast` is a pointer, so cleanup before replacing.
  if (this->ast) {
    delete this->ast;
    this->ast = nullptr;
  }
  if (program.ast) {
    this->ast = program.ast->makeCopy();
  }

  // `error` is a pointer, so cleanup before replacing.
  if (this->error) {
    delete this->error;
    this->error = nullptr;
  }
  if (program.error) {
    this->error = new Error(*program.error);
  }

  this->result = program.result;
  return *this;
}

Program & Program::operator=(Program && program) {
  swap(this->code, program.code);
  swap(this->codeType, program.codeType);
  swap(this->ast, program.ast);
  swap(this->error, program.error);
  swap(this->result, program.result);
  return *this;
}

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

optional<const GarbageCollected> Program::getResult() const {
  return this->result;
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
      default: {}
    }
    out << endl;
  }
  return out.str();
}

Program& Program::execute() {
  size_t pc{0};
  size_t fp{0};
  vector<GarbageCollected> stack;

  while (pc < this->bytecode.size()) {
    switch ((Opcode)this->bytecode[pc]) {
      case Opcode::INTEGER: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionInteger>((int64_t)this->bytecode[pc + 1]));
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionFloat>(bit_cast<double>(this->bytecode[pc + 1])));
        pc += 2;
        break;
      }
      case Opcode::ADD: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(rhs + lhs);
        ++pc;
        break;
      }
      default: {}
    }
  }

  // Verify that there is at least one value on the stack.  If not, set a
  // runtime error.
  if (!stack.size()) {
    // TODO Set a runtime error!
    return *this;
  }

  // Empty the stack, but save the top of the stack.
  this->result = stack.back();
  stack.clear();

  return *this;
}

