/**
 * @file
 * Define the Tang::AstNodeBlock class.
 */

#include <bit>
#include "astNodeBlock.hpp"
#include "opcode.hpp"
#include "program.hpp"

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

void AstNodeBlock::compilePreprocess(Program & program, PreprocessState state) const {
  for (auto x : this->statements) {
    x->compilePreprocess(program, state);
  }
}

void AstNodeBlock::compile(Tang::Program & program) const {
  if (this->statements.size()) {
    // Compile all but the last statement, adding POP after the statement.
    for (size_t i = 0; i < this->statements.size() - 1; ++i) {
      this->statements[i]->compile(program);
      program.addBytecode((uinteger_t)Opcode::POP);
    }
    // Compile the last statement without a POP so that its value is left on
    // the stack.
    this->statements.back()->compile(program);
  }
  else {
    // This compile *must* leave something on the stack, so leave a NULL
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

