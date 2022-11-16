/**
 * @file
 * Define the Tang::AstNodeFor class.
 */

#include <string>
#include <bit>
#include "astNodeFor.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeFor::AstNodeFor(shared_ptr<AstNode> initialization, shared_ptr<AstNode> condition, shared_ptr<AstNode> increment, shared_ptr<AstNode> codeBlock, Tang::location location) : AstNode(location), initialization{initialization}, condition{condition}, increment{increment}, codeBlock{codeBlock} {}

string AstNodeFor::dump(string indent) const {
  return indent + "For:"
    + indent + "  Initialization:\n"
    + this->initialization->dump(indent + "    ")
    + indent + "  Condition:\n"
    + this->condition->dump(indent + "    ")
    + indent + "  Increment:\n"
    + this->increment->dump(indent + "    ")
    + indent + "  Code Block:\n"
    + this->codeBlock->dump(indent + "    ");
}

void AstNodeFor::compile(Tang::Program & program) const {
  // Start new environments for `break` and `continue` statements.
  program.pushBreakStack();
  program.pushContinueStack();

  // Compile the Initialization expression.
  this->initialization->compile(program);
  program.addBytecode((uinteger_t)Opcode::POP);

  // Store the location for the start condition.
  auto conditionStart = program.getBytecode().size();
  this->condition->compile(program);

  // If condition is false, jump to the end of the if..else statement.
  auto conditionFalseJump = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMPF_POP);
  program.addBytecode(0);

  // Compile the code block and clean up the stack afterwards.
  this->codeBlock->compile(program);
  program.addBytecode((uinteger_t)Opcode::POP);

  // Compile the increment expression.
  auto incrementStart = program.getBytecode().size();
  this->increment->compile(program);
  program.addBytecode((uinteger_t)Opcode::POP);

  // Jump back up to the condition.
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode((uinteger_t)conditionStart);

  // We now know where the code after the while statement will be.
  // The parent will add a POP instruction, so account for that by using "+ 1".
  program.setJumpTarget(conditionFalseJump, program.getBytecode().size() + 1);

  // We now know where a `break` statement should jump to.
  // The parent will add a POP instruction, so account for that by using "+ 1".
  program.popBreakStack(program.getBytecode().size() + 1);

  // We now know where a `continue` statement should jump to.
  program.popContinueStack(incrementStart);
}

void AstNodeFor::compilePreprocess(Program & program) const {
  this->initialization->compilePreprocess(program);
  this->condition->compilePreprocess(program);
  this->increment->compilePreprocess(program);
  this->codeBlock->compilePreprocess(program);
}

