/**
 * @file
 * Define the Tang::AstNodeTernary class.
 */

#include <string>
#include <bit>
#include "astNodeTernary.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeTernary::AstNodeTernary(shared_ptr<AstNode> condition, shared_ptr<AstNode> trueExpression, shared_ptr<AstNode> falseExpression, Tang::location location) : AstNode(location), condition{condition}, trueExpression{trueExpression}, falseExpression{falseExpression} {}

string AstNodeTernary::dump(string indent) const {
  return indent + "Ternary:"
    + indent + "  Condition:\n"
    + this->condition->dump(indent + "    ")
    + indent + "  Expression if True:\n"
    + this->trueExpression->dump(indent + "    ")
    + indent + "  Expression if False:\n"
    + this->falseExpression->dump(indent + "    ");
}

void AstNodeTernary::compile(Tang::Program & program) const {
  this->condition->compile(program);

  // If condition is false, jump to the falseExpression.
  auto conditionFalseJump = program.getBytecode().size();
  program.addBytecode((uint64_t)Opcode::JMPF_POP);
  program.addBytecode(0);

  // Compile the then block, and jump past the else block.
  this->trueExpression->compile(program);
  
  // Jump past falseExpression.
  auto trueExpressionJump = program.getBytecode().size();
  program.addBytecode((uint64_t)Opcode::JMP);
  program.addBytecode(0);

  // Add the falseExpression.
  auto falseExpressionStart = program.getBytecode().size();
  this->falseExpression->compile(program);

  // Set jump locations.
  program.setJumpTarget(conditionFalseJump, falseExpressionStart);
  program.setJumpTarget(trueExpressionJump, program.getBytecode().size());
}

void AstNodeTernary::collectIdentifiers(Program & program) const {
  this->condition->collectIdentifiers(program);
  this->trueExpression->collectIdentifiers(program);
  this->falseExpression->collectIdentifiers(program);
}

void AstNodeTernary::collectStrings(Program & program) const {
  this->condition->collectStrings(program);
  this->trueExpression->collectStrings(program);
  this->falseExpression->collectStrings(program);
}

