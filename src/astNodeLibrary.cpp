/**
 * @file
 * Define the Tang::AstNodeLibrary class.
 */

#include <bit>
#include "astNodeLibrary.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeLibrary::AstNodeLibrary(shared_ptr<AstNode> & expression, const string & name, Tang::location location) : AstNode(location), name{name}, expression{expression} {}

string AstNodeLibrary::dump(string indent) const {
  return indent + "Library: " + this->name + "\n";
}

void AstNodeLibrary::compilePreprocess(Program & program, PreprocessState state) const {
  program.addIdentifier(this->name);
  if (state & AstNode::IsAssignment) {
    // This identifier appears on the LHS of an assignment expression, so
    // inform the current scope so that any necessary actions are taken.
    program.addIdentifierAssigned(this->name);
  }
}

void AstNodeLibrary::compile(Tang::Program & program) const {
  auto & identifier = program.getIdentifiers();
  if (identifier.count(this->name)) {
    program.addBytecode((uinteger_t)Opcode::PEEK);
    program.addBytecode((uinteger_t)identifier.at(this->name));
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

