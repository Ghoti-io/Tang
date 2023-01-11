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

#define BINARYOP(OP_SS, OP_SI, OP_IS, OP_II) \
    integer_t lhsIndex{-1}, rhsIndex{-1}; \
    auto & identifier = program.getIdentifiers(); \
    if (typeid(*this->lhs) == typeid(AstNodeIdentifier)) { \
      auto & name = static_cast<AstNodeIdentifier &>(*this->lhs).name; \
      if (identifier.count(name)) { \
        lhsIndex = identifier.at(name); \
      } \
    } \
    if (typeid(*this->rhs) == typeid(AstNodeIdentifier)) { \
      auto & name = static_cast<AstNodeIdentifier &>(*this->rhs).name; \
      if (identifier.count(name)) { \
        rhsIndex = identifier.at(name); \
      } \
    } \
    if (lhsIndex >= 0) { \
      if (rhsIndex >= 0) { \
        program.addBytecode((uinteger_t)Opcode:: OP_II); \
        program.addBytecode((uinteger_t)lhsIndex); \
        program.addBytecode((uinteger_t)rhsIndex); \
      } \
      else { \
        this->rhs->compile(program); \
        program.addBytecode((uinteger_t)Opcode:: OP_IS); \
        program.addBytecode((uinteger_t)lhsIndex); \
      } \
    } \
    else { \
      if (rhsIndex >= 0) { \
        this->lhs->compile(program); \
        program.addBytecode((uinteger_t)Opcode:: OP_SI); \
        program.addBytecode((uinteger_t)rhsIndex); \
      } \
      else { \
        this->lhs->compile(program); \
        this->rhs->compile(program); \
        program.addBytecode((uinteger_t)Opcode:: OP_SS); \
      } \
    } \
    return;

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
  // This is a standard binary operator.
  switch (this->op) {
    case Add: {
      BINARYOP(ADD_SS, ADD_SI, ADD_IS, ADD_II);
      break;
    }
    case Subtract: {
      BINARYOP(SUBTRACT_SS, SUBTRACT_SI, SUBTRACT_IS, SUBTRACT_II);
      break;
    }
    case Multiply: {
      BINARYOP(MULTIPLY_SS, MULTIPLY_SI, MULTIPLY_IS, MULTIPLY_II);
      break;
    }
    case Divide: {
      BINARYOP(DIVIDE_SS, DIVIDE_SI, DIVIDE_IS, DIVIDE_II);
      break;
    }
    case Modulo: {
      BINARYOP(MODULO_SS, MODULO_SI, MODULO_IS, MODULO_II);
      break;
    }
    case LessThan : {
      BINARYOP(LT_SS, LT_SI, LT_IS, LT_II);
      break;
    }
    case LessThanEqual : {
      BINARYOP(LTE_SS, LTE_SI, LTE_IS, LTE_II);
      break;
    }
    case GreaterThan : {
      BINARYOP(GT_SS, GT_SI, GT_IS, GT_II);
      break;
    }
    case GreaterThanEqual : {
      BINARYOP(GTE_SS, GTE_SI, GTE_IS, GTE_II);
      break;
    }
    case Equal : {
      BINARYOP(EQ_SS, EQ_SI, EQ_IS, EQ_II);
      break;
    }
    case NotEqual : {
      BINARYOP(NEQ_SS, NEQ_SI, NEQ_IS, NEQ_II);
      break;
    }
    case And : {
      // Evaluate the lhs.
      this->lhs->compile(program);
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
      this->lhs->compile(program);
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

