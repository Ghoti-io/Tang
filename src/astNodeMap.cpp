/**
 * @file
 * Define the Tang::AstNodeMap class.
 */

#include <bit>
#include "astNodeMap.hpp"
#include "astNodeString.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeMap::AstNodeMap(vector<std::pair<string, shared_ptr<AstNode>>> contents, Tang::location location) : AstNode(location), contents{contents} {}

string AstNodeMap::dump(string indent) const {
  string s = indent + "Map (" + to_string(this->contents.size()) + " items):\n";
  for (auto & item : this->contents) {
    s += item.first
      + " :\n"
      + item.second->dump(indent + "    ");
  }
  return s; 
}

void AstNodeMap::compilePreprocess(Program & program, PreprocessState state) const {
  for (auto & item : this->contents) {
    AstNodeString(item.first, this->location).compilePreprocess(program, state);
    item.second->compilePreprocess(program, state);
  }
}

void AstNodeMap::compile(Tang::Program & program) const {
  for (auto & item : this->contents) {
    AstNodeString(item.first, this->location).compile(program);
    item.second->compile(program);
  }
  program.addBytecode((uinteger_t)Opcode::MAP);
  program.addBytecode((uinteger_t)this->contents.size());
}

