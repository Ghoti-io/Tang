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
  auto & identifiers = program.identifierStack.back();
  if (identifiers.count(this->name) == 0) {
    identifiers[this->name] = identifiers.size();
  }
}

void AstNodeIdentifier::compile(Tang::Program & program) const {
  auto & identifier = program.identifierStack.back();
  if (identifier.count(this->name)) {
    program.addBytecode((uint64_t)Opcode::PEEK);
    program.addBytecode((uint64_t)identifier[this->name]);
  }
  else {
    program.addBytecode((uint64_t)Opcode::NULLVAL);
  }
}

