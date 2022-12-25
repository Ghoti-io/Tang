/**
 * @file
 * Define the Tang::AstNodeArray class.
 */

#include <bit>
#include "astNodeArray.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeArray::AstNodeArray(vector<shared_ptr<AstNode>> contents, Tang::location location) : AstNode(location), contents{contents} {}

string AstNodeArray::dump(string indent) const {
  string s = indent + "Array (" + to_string(this->contents.size()) + " items):\n";
  int i = 0; 
  for (auto & item : this->contents) {
    s += item->dump(indent + "  " + to_string(i++) + " ");
  }
  return s; 
}

void AstNodeArray::compilePreprocess(Program & program, PreprocessState state) const {
  for (auto & item : this->contents) {
    item->compilePreprocess(program, state);
  }
}

void AstNodeArray::compile(Tang::Program & program) const {
  for (auto & item : this->contents) {
    item->compile(program);
  }
  program.addBytecode((uinteger_t)Opcode::ARRAY);
  program.addBytecode((uinteger_t)this->contents.size());
}

