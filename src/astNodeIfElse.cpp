/**
 * @file
 * Define the Tang::AstNodeIfElse class.
 */

#include <string>
#include <bit>
#include "astNodeIfElse.hpp"
#include "opcode.hpp"
#include "program.hpp"

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
  auto conditionFalseJump = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMPF_POP);
  program.addBytecode(0);

  // Compile the then block, and jump past the else block.
  this->thenBlock->compile(program);
  
  // Compile differently depending on whether or not there is an else block.
  if (this->elseBlock) {
    // We must tell the then block to jump past the else block.
    auto thenBlockJump = program.getBytecode().size();
    program.addBytecode((uinteger_t)Opcode::JMP);
    program.addBytecode(0);

    // Add the else Block.
    auto elseBlockStart = program.getBytecode().size();
    this->elseBlock->compile(program);

    // Set jump locations.
    program.setJumpTarget(conditionFalseJump, elseBlockStart);
    program.setJumpTarget(thenBlockJump, program.getBytecode().size());
  }
  else {
    // The condition should jump past the then block.
    program.setJumpTarget(conditionFalseJump, program.getBytecode().size());

    // Leave something on the stack.
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

void AstNodeIfElse::compilePreprocess(Program & program, PreprocessState state) const {
  this->condition->compilePreprocess(program, state);
  this->thenBlock->compilePreprocess(program, state);
  if (this->elseBlock) {
    this->elseBlock->compilePreprocess(program, state);
  }
}

