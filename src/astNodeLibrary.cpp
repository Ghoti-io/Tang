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

AstNodeLibrary::AstNodeLibrary(const std::string & libraryName, Tang::location location) : AstNode(location), libraryName{libraryName} {}

string AstNodeLibrary::dump(string indent) const {
  return indent + "Library: " + this->libraryName + "\n";
}

void AstNodeLibrary::compilePreprocess(Program & program, [[maybe_unused]] PreprocessState state) const {
  // Add the library name to the program strings so that it can be used by the
  // bytecode to load the library.
  program.addString(this->libraryName, true);
}

void AstNodeLibrary::compile(Tang::Program & program) const {
  auto & strings = program.getStrings();
  auto & identifiers = program.getIdentifiers();

  if (strings.count({this->libraryName, true})) {
    // Load the library onto the stack.
    program.addBytecode((uinteger_t)Opcode::PEEK);
    program.addBytecode((uinteger_t)(strings.at({this->libraryName, true}) + identifiers.size()));
    program.addBytecode((uinteger_t)Opcode::LIBRARY);

  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}
