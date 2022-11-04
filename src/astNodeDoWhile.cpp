/**
 * @file
 * Define the Tang::AstNodeDoWhile class.
 */

#include <string>
#include <bit>
#include "astNodeDoWhile.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeDoWhile::AstNodeDoWhile(shared_ptr<AstNode> condition, shared_ptr<AstNode> codeBlock, Tang::location location) : AstNode(location), condition{condition}, codeBlock{codeBlock} {}

string AstNodeDoWhile::dump(string indent) const {
  return indent + "Do..While:"
    + indent + "  Condition:\n"
    + this->condition->dump(indent + "    ")
    + indent + "  Code Block:\n"
    + this->codeBlock->dump(indent + "    ");
}

void AstNodeDoWhile::compile(Tang::Program & program) const {
  // Initial jump past the condition to the code block.
  program.addBytecode((uint64_t)Opcode::JMP);
  auto initialJump = program.getBytecode().size() - 1;
  program.addBytecode(0);

  // Compile the condition.
  auto conditionStart = program.getBytecode().size();
  this->condition->compile(program);

  // If condition is false, jump to the end of the if..else statement.
  program.addBytecode((uint64_t)Opcode::JMPF_POP);
  auto conditionFalseJump = program.getBytecode().size() - 1;
  program.addBytecode(0);

  // Compile the code block and clean up the stack afterwards.
  program.setJumpTarget(initialJump, program.getBytecode().size());
  this->codeBlock->compile(program);
  program.addBytecode((uint64_t)Opcode::POP);

  // Jump back up to the condition.
  program.addBytecode((uint64_t)Opcode::JMP);
  program.addBytecode((uint64_t)conditionStart);

  // We now know where the code after the while statement will be.
  // The parent will add a POP instruction, so account for that by using "+ 1".
  program.setJumpTarget(conditionFalseJump, program.getBytecode().size() + 1);
}

void AstNodeDoWhile::compileIdentifiers(Program & program) const {
  this->condition->compileIdentifiers(program);
  this->codeBlock->compileIdentifiers(program);
}

