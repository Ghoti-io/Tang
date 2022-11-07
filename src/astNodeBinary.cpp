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
    "And",
    "Or",
  };

  return indent + "Binary (" + description[this->op] + "):\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeBinary::collectIdentifiers(Program & program) const {
  this->lhs->collectIdentifiers(program);
  this->rhs->collectIdentifiers(program);
}

void AstNodeBinary::compile(Tang::Program & program) const {
  // All binary operators require that the lhs be compiled first.
  this->lhs->compile(program);

  // And and Or require short-circuit evaluation, so don't compile rhs yet.
  // Everything else needs the rhs compiled.
  if (this->op != And && this->op != Or) {
    this->rhs->compile(program);
  }

  // This is a standard binary operator.
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
    case And : {
      // Evaluate the lhs.
      auto conditionFalseJump = program.getBytecode().size();
      program.addBytecode((uint64_t)Opcode::JMPF);
      program.addBytecode(0);

      // Remove lhs from stack, evaluate rhs.
      program.addBytecode((uint64_t)Opcode::POP);
      this->rhs->compile(program);

      // Set the lhs JMPF target
      program.setJumpTarget(conditionFalseJump, program.getBytecode().size());
      break;
    }
    case Or : {
      // Evaluate the lhs.
      auto conditionTrueJump = program.getBytecode().size();
      program.addBytecode((uint64_t)Opcode::JMPT);
      program.addBytecode(0);

      // Remove lhs from stack, evaluate rhs.
      program.addBytecode((uint64_t)Opcode::POP);
      this->rhs->compile(program);

      // Set the lhs JMPT target
      program.setJumpTarget(conditionTrueJump, program.getBytecode().size());
      break;
    }
  }
}

