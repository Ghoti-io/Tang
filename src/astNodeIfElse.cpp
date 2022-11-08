/**
 * @file
 * Define the Tang::AstNodeIfElse class.
 */

#include <string>
#include <bit>
#include "astNodeIfElse.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeIfElse::AstNodeIfElse(shared_ptr<AstNode> condition, shared_ptr<AstNode> thenBlock, shared_ptr<AstNode> elseBlock, Tang::location location) : AstNode(location), condition{condition}, thenBlock{thenBlock}, elseBlock{elseBlock} {}

AstNodeIfElse::AstNodeIfElse(shared_ptr<AstNode> condition, shared_ptr<AstNode> thenBlock, Tang::location location) : AstNode(location), condition{condition}, thenBlock{thenBlock}, elseBlock{nullptr} {}

string AstNodeIfElse::dump(string indent) const {
  return indent + "If..Else:\n"
    + indent + "  Condition:\n"
    + this->condition->dump(indent + "    ")
    + indent + "  Then Block:\n"
    + this->thenBlock->dump(indent + "    ")
    + (
        this->elseBlock
        ? (
            indent + "  Else Block:\n"
            + this->elseBlock->dump(indent + "    ")
          )
        : string{}
      );
}

void AstNodeIfElse::compile(Tang::Program & program) const {
  this->condition->compile(program);

  // If condition is false, jump to the end of the if..else statement.
  program.addBytecode((uint64_t)Opcode::JMPF_POP);
  auto conditionFalseJump = program.getBytecode().size() - 1;
  program.addBytecode(0);

  // Compile the then block, and jump past the else block.
  this->thenBlock->compile(program);
  
  // Compile differently depending on whether or not there is an else block.
  if (this->elseBlock) {
    // Clean up the stack from the then block.
    program.addBytecode((uint64_t)Opcode::POP);

    // We must tell the then block to jump past the else block.
    program.addBytecode((uint64_t)Opcode::JMP);
    auto thenBlockJump = program.getBytecode().size() - 1;
    program.addBytecode(0);

    // Add the else Block.
    auto elseBlockStart = program.getBytecode().size();
    this->elseBlock->compile(program);

    // Set jump locations.
    program.setJumpTarget(conditionFalseJump, elseBlockStart);
    program.setJumpTarget(thenBlockJump, program.getBytecode().size() + 1);
  }
  else {
    // The condition should jump past the then block.
    program.setJumpTarget(conditionFalseJump, program.getBytecode().size() + 1);
  }
}

void AstNodeIfElse::collectIdentifiers(Program & program) const {
  this->condition->collectIdentifiers(program);
  this->thenBlock->collectIdentifiers(program);
  if (this->elseBlock) {
    this->elseBlock->collectIdentifiers(program);
  }
}

void AstNodeIfElse::collectStrings(Program & program) const {
  this->condition->collectStrings(program);
  this->thenBlock->collectStrings(program);
  if (this->elseBlock) {
    this->elseBlock->collectStrings(program);
  }
}

