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
  // Compile the code block and clean up the stack afterwards.
  auto codeBlockStart = program.getBytecode().size();
  this->codeBlock->compile(program);
  program.addBytecode((uint64_t)Opcode::POP);

  // Compile the condition.
  this->condition->compile(program);

  // If condition is true, jump up to the start of the code block.
  program.addBytecode((uint64_t)Opcode::JMPT_POP);
  program.addBytecode(codeBlockStart);

  // Add extra stack push, which will be removed by the parent AST compile.
  program.addBytecode((uint64_t)Opcode::NULLVAL);
}

void AstNodeDoWhile::collectIdentifiers(Program & program) const {
  this->condition->collectIdentifiers(program);
  this->codeBlock->collectIdentifiers(program);
}

