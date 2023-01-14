/**
 * @file
 * Define the Tang::AstNodeBinary class.
 */

#include <string>
#include "astNodeBinary.hpp"
#include "astNodeIdentifier.hpp"
#include "astNodeString.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

#define LOGICALOP(OP_S, OP_I) \
  integer_t lhsIndex{-1}; \
  OPCODE_FIND_INDEX(this->lhs, lhsIndex); \
  size_t conditionJump{0}; \
  if (lhsIndex >= 0) { \
    conditionJump = program.getBytecode().size(); \
    program.addBytecode((uinteger_t)Opcode:: OP_I); \
    program.addBytecode(lhsIndex); \
    program.addBytecode(0); \
    this->rhs->compile(program); \
    auto rhsLeapfrog = program.getBytecode().size(); \
    program.addBytecode((uinteger_t)Opcode::JMP); \
    program.addBytecode(0); \
    program.setJumpTarget(conditionJump, program.getBytecode().size()); \
    program.addBytecode((uinteger_t)Opcode::PEEK); \
    program.addBytecode(lhsIndex); \
    program.setJumpTarget(rhsLeapfrog, program.getBytecode().size()); \
  } \
  else { \
    this->lhs->compile(program); \
    conditionJump = program.getBytecode().size(); \
    program.addBytecode((uinteger_t)Opcode:: OP_S); \
    program.addBytecode(0); \
    program.addBytecode((uinteger_t)Opcode::POP); \
    this->rhs->compile(program); \
    program.setJumpTarget(conditionJump, program.getBytecode().size()); \
  }

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
      BINARYOP(this->lhs, this->rhs, ADD_SS, ADD_SI, ADD_IS, ADD_II);
      break;
    }
    case Subtract: {
      BINARYOP(this->lhs, this->rhs, SUBTRACT_SS, SUBTRACT_SI, SUBTRACT_IS, SUBTRACT_II);
      break;
    }
    case Multiply: {
      BINARYOP(this->lhs, this->rhs, MULTIPLY_SS, MULTIPLY_SI, MULTIPLY_IS, MULTIPLY_II);
      break;
    }
    case Divide: {
      BINARYOP(this->lhs, this->rhs, DIVIDE_SS, DIVIDE_SI, DIVIDE_IS, DIVIDE_II);
      break;
    }
    case Modulo: {
      BINARYOP(this->lhs, this->rhs, MODULO_SS, MODULO_SI, MODULO_IS, MODULO_II);
      break;
    }
    case LessThan : {
      BINARYOP(this->lhs, this->rhs, LT_SS, LT_SI, LT_IS, LT_II);
      break;
    }
    case LessThanEqual : {
      BINARYOP(this->lhs, this->rhs, LTE_SS, LTE_SI, LTE_IS, LTE_II);
      break;
    }
    case GreaterThan : {
      BINARYOP(this->lhs, this->rhs, GT_SS, GT_SI, GT_IS, GT_II);
      break;
    }
    case GreaterThanEqual : {
      BINARYOP(this->lhs, this->rhs, GTE_SS, GTE_SI, GTE_IS, GTE_II);
      break;
    }
    case Equal : {
      BINARYOP(this->lhs, this->rhs, EQ_SS, EQ_SI, EQ_IS, EQ_II);
      break;
    }
    case NotEqual : {
      BINARYOP(this->lhs, this->rhs, NEQ_SS, NEQ_SI, NEQ_IS, NEQ_II);
      break;
    }
    case And : {
      LOGICALOP(JMPF_S, JMPF_I);
      break;
    }
    case Or : {
      LOGICALOP(JMPT_S, JMPT_I);
      break;
    }
  }
}

