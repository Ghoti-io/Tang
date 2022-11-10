/**
 * @file
 * Define the Tang::AstNodeIdentifier class.
 */

#include <bit>
#include "astNodeIdentifier.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeIdentifier::AstNodeIdentifier(const string & name, Tang::location location) : AstNode(location), name{name} {}

string AstNodeIdentifier::dump(string indent) const {
  return indent + "Identifier: " + this->name + "\n";
}

void AstNodeIdentifier::collectIdentifiers(Program & program) const {
  program.addIdentifier(this->name);
}

void AstNodeIdentifier::compile(Tang::Program & program) const {
  auto & identifier = program.getIdentifiers();
  if (identifier.count(this->name)) {
    program.addBytecode((uinteger_t)Opcode::PEEK);
    program.addBytecode((uinteger_t)identifier.at(this->name));
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

