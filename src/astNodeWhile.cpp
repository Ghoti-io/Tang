/**
 * @file
 * Define the Tang::AstNodeWhile class.
 */

#include <string>
#include <bit>
#include "astNodeWhile.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeWhile::AstNodeWhile(shared_ptr<AstNode> condition, shared_ptr<AstNode> codeBlock, Tang::location location) : AstNode(location), condition{condition}, codeBlock{codeBlock} {}

string AstNodeWhile::dump(string indent) const {
  return indent + "While:"
    + indent + "  Condition:\n"
    + this->condition->dump(indent + "    ")
    + indent + "  Code Block:\n"
    + this->codeBlock->dump(indent + "    ");
}

void AstNodeWhile::compile(Tang::Program & program) const {
  // Start new environments for `break` and `continue` statements.
  program.pushBreakStack();
  program.pushContinueStack();

  // Start compiling the `while` statement.
  auto conditionStart = program.getBytecode().size();
  this->condition->compile(program);

  // If condition is false, jump to the end of the if..else statement.
  program.addBytecode((uinteger_t)Opcode::JMPF_POP);
  auto conditionFalseJump = program.getBytecode().size() - 1;
  program.addBytecode(0);

  // Compile the code block and clean up the stack afterwards.
  this->codeBlock->compile(program);
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
  program.popContinueStack(conditionStart);
}

void AstNodeWhile::compilePreprocess(Program & program, PreprocessState state) const {
  this->condition->compilePreprocess(program, state);
  this->codeBlock->compilePreprocess(program, state);
}

