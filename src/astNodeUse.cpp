/**
 * @file
 * Define the Tang::AstNodeUse class.
 */

#include <bit>
#include "opcode.hpp"
#include "astNodeUse.hpp"
#include "astNodeIdentifier.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeUse::AstNodeUse(shared_ptr<AstNode> expression, const string & alias, Tang::location location) : AstNode(location), alias{alias}, expression{expression} {}

string AstNodeUse::dump(string indent) const {
  return indent + "Use:\n"
    + indent + "  Expression:\n"
    + this->expression->dump(indent + "    ")
    + indent + "  Alias: " + this->alias + "\n";
}

void AstNodeUse::compilePreprocess(Program & program, PreprocessState state) const {
  // Add the alias to the environment.
  program.addLibraryAlias(this->alias);
  // Add the alias as an identifier.
  program.addIdentifier(this->alias);
  // Let the expression do whatever it needs to.
  this->expression->compilePreprocess(program, state);
}

void AstNodeUse::compile(Tang::Program & program) const {
  auto & identifiers = program.getIdentifiers();
  // Load the library expression.
  this->expression->compile(program);

  // Save the library into its proper stack location.
  program.addBytecode((uinteger_t)Opcode::POKE);
  program.addBytecode((uinteger_t)identifiers.at(this->alias));

  // Save the library into the libraryAliasStack
  auto & aliases = program.getLibraryAliases();
  if (aliases.count(this->alias)) {
    program.addBytecode((uinteger_t)Opcode::LIBRARYSAVE);
    program.addBytecode(aliases.at(this->alias));
  }
}
