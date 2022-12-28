/**
 * @file
 * Define the Tang::AstNodeFunctionDeclaration class.
 */

#include <string>
#include <bit>
#include "astNodeFunctionDeclaration.hpp"
#include "astNodeString.hpp"
#include "opcode.hpp"
#include "program.hpp"

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
  string annotation = "FUNCTION (" + this->name + ") : ";
  // Jump past the function Bytecode (that we are about to compile).
  auto jumpPastFunction = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode(0);
  program.setAnnotation(jumpPastFunction, annotation + "Jump past function declaration");

  // Prepare for a new function environment.
  // pushEnvironment() will collect all of the expected variable names,
  // string literals, function declarations, and library aliases.
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
  // First, get a vector of stack names in the correct order.
  vector<string> identifiers(program.getIdentifiers().size());
  for (auto & [name, position] : program.getIdentifiers()) {
    if (position < identifiers.size()) {
      identifiers[position] = name;
    }
  }

  // Second, add an entry for each identifier.  If the identifier is a
  // function name, then leave enough room in the bytecode.
  // The arguments will have already been placed on the stack by the calling
  // code, so they can be skipped.
  if (this->arguments.size() < identifiers.size()) {
    program.setAnnotation(program.getBytecode().size(), annotation + "Reserve stack space for function identifiers");
  }
  for (size_t i = this->arguments.size(); i < identifiers.size(); ++i) {
    if (program.functionsCollected.back().count(identifiers[i])) {
      // This is function.
      auto opcodeLocation = program.getBytecode().size();
      program.addBytecode((uinteger_t)Opcode::FUNCTION);
      program.addBytecode(0);
      program.addBytecode(0);
      // Record the fact that this bytecode will need to be populated later,
      // once the function details are known.
      program.functionStackDeclarations[identifiers[i]].push_back(opcodeLocation);
    }
    else if (program.getLibraryAliases().count(identifiers[i])) {
      // This is a library alias.
      auto & aliases = program.getLibraryAliases();
      if (aliases.count(identifiers[i])) {
        program.addBytecode((uinteger_t)Opcode::LIBRARYCOPY);
        program.addBytecode(aliases.at(identifiers[i]));
      }
      else {
        program.addBytecode((uinteger_t)Opcode::NULLVAL);
      }
    }
    else {
      // This is just a standard value.
      program.addBytecode((uinteger_t)Opcode::NULLVAL);
    }
  }

  // Put the string literals on the stack.
  // We must be careful to add them in the expected order, so figure out the
  // order first, and put that into `stringLiterals`.
  if (program.getStrings().size()) {
    program.setAnnotation(program.getBytecode().size(), annotation + "Reserve stack space for function strings");
  }
  auto & strings = program.getStrings();
  vector<pair<string, UnicodeString::Type>> stringLiterals(strings.size());
  for (auto & [item, position] : strings) {
    stringLiterals[position] = item;
  }
  // Now that the strings are in the correct order, push them onto the stack.
  for (auto & [str, type]: stringLiterals) {
    AstNodeString(str, type, Tang::location{}).compileLiteral(program);
  }

  // If any argument will be altered within the function body, then create a
  // copy of the argument so that the value is not changed outside the scope
  // of the function.
  for (auto const & name : this->arguments) {
    if (program.getIdentifiersAssigned().count(name)) {
      // The argument will be modified in this function.  Create a copy of it
      // so that the changes will not leak into the calling scope.
      program.addBytecode((uinteger_t)Opcode::COPY);
      program.addBytecode(program.getIdentifiers().at(name));
    }
  }
  

  // Compile the program.
  // Do not pop the result.  It will be the "default" return value of the
  // function, if a `return;` statement is not otherwise used.
  program.setAnnotation(program.getBytecode().size(), annotation + "Code block start");
  this->codeBlock->compile(program);

  // At this point, we need to account for any stray `continue` or `break`
  // statements.  However, `RETURN` expects there to be a return value on the
  // stack, something that `continue` and `break` do not provide.  Therefore,
  // we must provide a "dummy" value that will only be evaluated in the case
  // that a stray `continue` or `break` is being evaluated.
  //
  // The simple solution is to, at this moment of execution jump over a command
  // to add the "dummy" value, but make the stray `continue` and `break`
  // statements jump *to* the "dummy" value.
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode((uinteger_t)program.getBytecode().size() + 2);
  program.addBytecode((uinteger_t)Opcode::NULLVAL);

  // Now, make all of the stray `continue` and `break` statements jump to the
  // NULLVAL opcode.
  program.popBreakStack(program.getBytecode().size() - 1);
  program.popContinueStack(program.getBytecode().size() - 1);

  // We just popped the `break` and `continue` stacks, but they will be popped
  // again when the function has completed compiling.  So, push the stacks
  // so that the push/pop symmetry is maintained.
  program.pushBreakStack();
  program.pushContinueStack();

  // Ensure that the function is cleaned up by calling `RETURN`
  program.setAnnotation(program.getBytecode().size(), annotation + "Code block end");
  program.addBytecode((uinteger_t)Opcode::RETURN);
  program.addBytecode((uinteger_t)program.getIdentifiers().size() + program.getStrings().size());

  // Set the jump target, now that we are at the end of the function Bytecode.
  program.setJumpTarget(jumpPastFunction, program.getBytecode().size());
  
  // Push a ComputedExpressionCompiledFunction onto the stack.
  //auto functionDeclarationAddress = program.getBytecode().size();
  program.addBytecode((uinteger_t)Opcode::FUNCTION);
  program.addBytecode(this->arguments.size());
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

  // Record the information about this function in the functionsDeclared.
  //program.setFunctionStackDeclaration(functionDeclarationAddress, this->arguments.size(), functionStart);
  program.functionsDeclared[this->name] = {this->arguments.size(), functionStart};
}

void AstNodeFunctionDeclaration::compilePreprocess(Program & program, [[maybe_unused]] PreprocessState state) const {
  program.addIdentifier(this->name);
  program.functionsCollected.back().insert(this->name);
}

