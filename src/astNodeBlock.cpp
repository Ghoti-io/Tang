/**
 * @file
 * Define the Tang::AstNodeBlock class.
 */

#include <bit>
#include "astNodeBlock.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeBlock::AstNodeBlock(const vector<shared_ptr<AstNode>> & statements, Tang::location location) : AstNode(location), statements{statements} {}

string AstNodeBlock::dump(string indent) const {
  string out = indent + "Block:\n";
  for (auto x : this->statements) {
    out += x->dump(indent + "  ");
  }
  return out;
}

void AstNodeBlock::compileIdentifiers(Program & program) const {
  for (auto x : this->statements) {
    x->compileIdentifiers(program);
  }
}

void AstNodeBlock::compile(Tang::Program & program) const {
  if (this->statements.size()) {
    // Compile all but the last statement, adding POP after the statement.
    for (size_t i = 0; i < this->statements.size() - 1; ++i) {
      this->statements[i]->compile(program);
      program.addBytecode((uint64_t)Opcode::POP);
    }
    // Compile the last statement without a POP so that its value is left on
    // the stack.
    this->statements.back()->compile(program);
  }
}

shared_ptr<AstNode> AstNodeBlock::makeCopy() const {
  return make_shared<AstNodeBlock>(this->statements, this->location);
}

