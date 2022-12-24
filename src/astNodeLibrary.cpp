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

AstNodeLibrary::AstNodeLibrary(shared_ptr<AstNode> expression, const string & alias, Tang::location location) : AstNode(location), alias{alias}, expression{expression} {}

string AstNodeLibrary::dump(string indent) const {
  return indent + "Library:\n"
    + indent + "  Alias: " + this->alias + "\n"
    + indent + "  Expression:\n"
    + this->expression->dump(indent + "    ");
}

void AstNodeLibrary::compilePreprocess(Program & program, [[maybe_unused]] PreprocessState state) const {
  // Add the alias as an identifier.
  program.addIdentifier(this->alias);
  // Add the expression as strings so that they can be used by the bytecode to
  // load the library/attributes.
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) {
    program.addString(static_cast<AstNodeIdentifier &>(*this->expression).name, true);
  }
}

void AstNodeLibrary::compile(Tang::Program & program) const {
  auto & strings = program.getStrings();
  auto & identifiers = program.getIdentifiers();
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) {
    auto & libraryName = static_cast<AstNodeIdentifier &>(*this->expression).name;
    if (strings.count({libraryName, true}) && identifiers.count(this->alias)) {
      // Load the library onto the stack.
      program.addBytecode((uinteger_t)Opcode::PEEK);
      program.addBytecode((uinteger_t)(strings.at({libraryName, true}) + identifiers.size()));
      program.addBytecode((uinteger_t)Opcode::LIBRARY);

      // Save the library into its proper stack location.
      program.addBytecode((uinteger_t)Opcode::POKE);
      program.addBytecode((uinteger_t)identifiers.at(this->alias));
    }
    else {
      program.addBytecode((uinteger_t)Opcode::NULLVAL);
    }
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}
