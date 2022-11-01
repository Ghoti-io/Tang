/**
 * @file
 * Define the Tang::AstNodeBinary class.
 */

#include <string>
#include "astNodeBinary.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeBinary::AstNodeBinary(Operation op, shared_ptr<AstNode> lhs, shared_ptr<AstNode> rhs, Tang::location location) : AstNode(location), op{op}, lhs{lhs}, rhs{rhs} {}

string AstNodeBinary::dump(string indent) const {
  string description[] = {
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Modulo",
    "Less Than",
    "Less Than or Equal",
    "Greater Than",
    "Greater Than or Equal",
    "Equal",
    "Not Equal",
  };

  return indent + "Binary (" + description[this->op] + "):\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeBinary::compileIdentifiers(Program & program) const {
  this->lhs->compileIdentifiers(program);
  this->rhs->compileIdentifiers(program);
}

void AstNodeBinary::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  switch (this->op) {
    case Add: {
      program.addBytecode((uint64_t)Opcode::ADD);
      break;
    }
    case Subtract: {
      program.addBytecode((uint64_t)Opcode::SUBTRACT);
      break;
    }
    case Multiply: {
      program.addBytecode((uint64_t)Opcode::MULTIPLY);
      break;
    }
    case Divide: {
      program.addBytecode((uint64_t)Opcode::DIVIDE);
      break;
    }
    case Modulo: {
      program.addBytecode((uint64_t)Opcode::MODULO);
      break;
    }
    case LessThan : {
      program.addBytecode((uint64_t)Opcode::LT);
      break;
    }
    case LessThanEqual : {
      program.addBytecode((uint64_t)Opcode::LTE);
      break;
    }
    case GreaterThan : {
      program.addBytecode((uint64_t)Opcode::GT);
      break;
    }
    case GreaterThanEqual : {
      program.addBytecode((uint64_t)Opcode::GTE);
      break;
    }
    case Equal : {
      program.addBytecode((uint64_t)Opcode::EQ);
      break;
    }
    case NotEqual : {
      program.addBytecode((uint64_t)Opcode::NEQ);
      break;
    }
  }
}

shared_ptr<AstNode> AstNodeBinary::makeCopy() const {
  return make_shared<AstNodeBinary>(this->op, this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

