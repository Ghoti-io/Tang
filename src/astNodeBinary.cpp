/**
 * @file
 * Define the Tang::AstNodeBinary class.
 */

#include <string>
#include "astNodeBinary.hpp"
#include "astNodeIdentifier.hpp"
#include "opcode.hpp"
#include "program.hpp"

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

void AstNodeBinary::compilePreprocess(Program & program, PreprocessState state) const {
  this->lhs->compilePreprocess(program, state);
  this->rhs->compilePreprocess(program, state);
}

void AstNodeBinary::compile(Tang::Program & program) const {
  if (this->op == Operation::Subtract) {
    integer_t lhsIndex{-1}, rhsIndex{-1};
    auto & identifier = program.getIdentifiers();
    if (typeid(*this->lhs) == typeid(AstNodeIdentifier)) {
      auto & name = static_cast<AstNodeIdentifier &>(*this->lhs).name;
      if (identifier.count(name)) {
        lhsIndex = identifier.at(name);
      }
    }
    if (typeid(*this->rhs) == typeid(AstNodeIdentifier)) {
      auto & name = static_cast<AstNodeIdentifier &>(*this->rhs).name;
      if (identifier.count(name)) {
        rhsIndex = identifier.at(name);
      }
    }
    if (lhsIndex >= 0) {
      if (rhsIndex >= 0) {
        program.addBytecode((uinteger_t)Opcode::SUBTRACT_II);
        program.addBytecode((uinteger_t)lhsIndex);
        program.addBytecode((uinteger_t)rhsIndex);
      }
      else {
        this->rhs->compile(program);
        program.addBytecode((uinteger_t)Opcode::SUBTRACT_IS);
        program.addBytecode((uinteger_t)lhsIndex);
      }
    }
    else {
      if (rhsIndex >= 0) {
        this->lhs->compile(program);
        program.addBytecode((uinteger_t)Opcode::SUBTRACT_SI);
        program.addBytecode((uinteger_t)rhsIndex);
      }
      else {
        this->lhs->compile(program);
        this->rhs->compile(program);
        program.addBytecode((uinteger_t)Opcode::SUBTRACT_SS);
      }
    }
    return;
  }

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
      program.addBytecode((uinteger_t)Opcode::ADD);
      break;
    }
    case Subtract: {
      //program.addBytecode((uinteger_t)Opcode::SUBTRACT);
      break;
    }
    case Multiply: {
      program.addBytecode((uinteger_t)Opcode::MULTIPLY);
      break;
    }
    case Divide: {
      program.addBytecode((uinteger_t)Opcode::DIVIDE);
      break;
    }
    case Modulo: {
      program.addBytecode((uinteger_t)Opcode::MODULO);
      break;
    }
    case LessThan : {
      program.addBytecode((uinteger_t)Opcode::LT);
      break;
    }
    case LessThanEqual : {
      program.addBytecode((uinteger_t)Opcode::LTE);
      break;
    }
    case GreaterThan : {
      program.addBytecode((uinteger_t)Opcode::GT);
      break;
    }
    case GreaterThanEqual : {
      program.addBytecode((uinteger_t)Opcode::GTE);
      break;
    }
    case Equal : {
      program.addBytecode((uinteger_t)Opcode::EQ);
      break;
    }
    case NotEqual : {
      program.addBytecode((uinteger_t)Opcode::NEQ);
      break;
    }
    case And : {
      // Evaluate the lhs.
      auto conditionFalseJump = program.getBytecode().size();
      program.addBytecode((uinteger_t)Opcode::JMPF);
      program.addBytecode(0);

      // Remove lhs from stack, evaluate rhs.
      program.addBytecode((uinteger_t)Opcode::POP);
      this->rhs->compile(program);

      // Set the lhs JMPF target
      program.setJumpTarget(conditionFalseJump, program.getBytecode().size());
      break;
    }
    case Or : {
      // Evaluate the lhs.
      auto conditionTrueJump = program.getBytecode().size();
      program.addBytecode((uinteger_t)Opcode::JMPT);
      program.addBytecode(0);

      // Remove lhs from stack, evaluate rhs.
      program.addBytecode((uinteger_t)Opcode::POP);
      this->rhs->compile(program);

      // Set the lhs JMPT target
      program.setJumpTarget(conditionTrueJump, program.getBytecode().size());
      break;
    }
  }
}

