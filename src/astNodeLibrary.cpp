/**
 * @file
 * Define the Tang::AstNodeLibrary class.
 */

#include <bit>
#include "opcode.hpp"
#include "astNodeLibrary.hpp"
#include "astNodeIdentifier.hpp"

using namespace std;
using namespace Tang;

AstNodeLibrary::AstNodeLibrary(shared_ptr<AstNode> expression, const string & name, Tang::location location) : AstNode(location), name{name}, expression{expression} {}

string AstNodeLibrary::dump(string indent) const {
  return indent + "Library:\n"
    + indent + "  Alias: " + this->name + "\n"
    + indent + "  Expression:\n"
    + this->expression->dump(indent + "    ");
}

void AstNodeLibrary::compilePreprocess(Program & program, PreprocessState state) const {
  program.addIdentifier(this->name);
  if (state & AstNode::IsAssignment) {
    // This identifier appears on the LHS of an assignment expression, so
    // inform the current scope so that any necessary actions are taken.
    program.addIdentifierAssigned(this->name);
  }
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) {
    program.addString(static_cast<AstNodeIdentifier &>(*this->expression).name, true);
  }
}

void AstNodeLibrary::compile(Tang::Program & program) const {
  auto & strings = program.getStrings();
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) {
    auto & name = static_cast<AstNodeIdentifier &>(*this->expression).name;
    if (strings.count({name, true})) {
      program.addBytecode((uinteger_t)Opcode::PEEK);
      program.addBytecode((uinteger_t)(strings.at({name, true}) + program.getIdentifiers().size()));
      program.addBytecode((uinteger_t)Opcode::LIBRARY);
    }
    else {
      program.addBytecode((uinteger_t)Opcode::NULLVAL);
    }
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}
