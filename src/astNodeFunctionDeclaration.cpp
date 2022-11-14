/**
 * @file
 * Define the Tang::AstNodeFunctionDeclaration class.
 */

#include <string>
#include <bit>
#include "astNodeFunctionDeclaration.hpp"
#include "astNodeString.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeFunctionDeclaration::AstNodeFunctionDeclaration(string name, vector<string>arguments, shared_ptr<AstNode> codeBlock, Tang::location location) : AstNode(location), name{name}, arguments{arguments}, codeBlock{codeBlock} {}

string AstNodeFunctionDeclaration::dump(string indent) const {
  string temp{};
  for (auto & s : this->arguments) {
    temp += s + " ";
  }
  return indent + "FunctionDeclaration:"
    + indent + "  Name:\n"
    + this->name
    + indent + "  Arguments:\n"
    + indent + "    " + temp
    + indent + "  Code Block:\n"
    + this->codeBlock->dump(indent + "    ");
}

void AstNodeFunctionDeclaration::compile(Tang::Program & program) const {
  // Jump past the function Bytecode (that we are about to compile).
  auto jumpPastFunction = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode(0);

  // Prepare for a new function environment.
  program.pushEnvironment(this->codeBlock);

  // Ensure that arguments are listed as identifiers in the order that they
  // appear in the function declaration.
  for (size_t i = 0; i < this->arguments.size(); ++i) {
    program.addIdentifier(this->arguments[i], i);
  }

  // Save the start position of the function.
  auto functionStart = program.getBytecode().size();

  // Reserve stack positions for any variable in the body that is not in the
  // arguments.
  for (size_t i = this->arguments.size(); i < program.getIdentifiers().size(); ++i) {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }

  // Put the string literals on the stack.
  // We must be careful to add them in the expected order, so figure out the
  // order first, and put that into `stringLiterals`.
  auto & strings = program.getStrings();
  vector<string> stringLiterals(strings.size());
  for (auto & item : strings) {
    stringLiterals[item.second] = item.first;
  }
  // Now that the strings are in the correct order, push them onto the stack.
  for (auto & literal : stringLiterals) {
    AstNodeString(literal, Tang::location{}).compileLiteral(program);
  }

  // Compile the program.
  // Do not pop the result.  It will be the "default" return value of the
  // function, if a `return;` statement is not otherwise used.
  this->codeBlock->compile(program);

  // Ensure that the function is cleaned up by calling `RETURN`
  program.addBytecode((uinteger_t)Opcode::RETURN);
  program.addBytecode((uinteger_t)program.getIdentifiers().size() + program.getStrings().size());

  // Set the jump target, now that we are at the end of the function Bytecode.
  program.setJumpTarget(jumpPastFunction, program.getBytecode().size());
  
  // Push a ComputedExpressionCompiledFunction onto the stack.
  program.addBytecode((uinteger_t)Opcode::FUNCTION);
  program.addBytecode(program.getIdentifiers().size() + program.getStrings().size());
  program.addBytecode(functionStart);

  // Restore the environment because we have finished with the function.
  program.popEnvironment();

  // Copy the ComputedExpressionCompiledFunction into the variable name that
  // was reserved for it.
  auto & identifier = program.getIdentifiers();
  if (identifier.count(this->name)) {
    program.addBytecode((uinteger_t)Opcode::POKE);
    program.addBytecode(identifier.at(this->name));
  }
}

void AstNodeFunctionDeclaration::collectIdentifiers(Program & program) const {
  program.addIdentifier(this->name);
}

