/**
 * @file
 * Define the Tang::Program class.
 */

#include <sstream>
#include "program.hpp"
#include "opcode.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "astNodeString.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

Program::Program(const string & code, Program::CodeType codeType, std::shared_ptr<Tang::TangBase> tang) : tang{tang}, code{code}, istreamCode{nullopt}, codeType{codeType}, ast{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

Program::Program(istream & code, Program::CodeType codeType, std::shared_ptr<Tang::TangBase> tang) : tang{tang}, code{""}, istreamCode{&code}, codeType{codeType}, ast{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

void Program::parse() {
  unique_ptr<TangScanner> scanner{};
  stringstream ss{};

  if (this->istreamCode) {
    scanner = make_unique<TangScanner>(**this->istreamCode, cout);
  }
  else {
    ss << this->code;
    scanner = make_unique<TangScanner>(ss, cout);
  }

  Error * error{nullptr};
  TangParser parser{*scanner, this->ast, error};

  // Set the scanner mode, depending on the codeType.
  if (this->codeType == Program::CodeType::Template) {
    scanner->setModeTemplate();
  }

  // Begin parsing.
  parser.parse();
  if (error) {
    this->result = GarbageCollected::make<ComputedExpressionError>(*error);
    delete error;
  }
}

void Program::pushEnvironment(const shared_ptr<AstNode> & ast) {
  // Prepare the identifier mapping stack with an empty map.
  this->identifierStack.push_back({});

  // Prepare the string mapping stack with an empty map.
  this->stringStack.push_back({});

  // Forward all of the previous function declarations, and gather any new ones
  // in the new scope.
  if (this->functionsCollected.size()) {
    this->functionsCollected.push_back(this->functionsCollected.back());
  }
  else {
    this->functionsCollected.push_back({});
  }

  // Forward all of the previous library aliases, and gather any new ones
  // in the new scope.
  if (this->libraryAliasStack.size()) {
    this->libraryAliasStack.push_back(this->libraryAliasStack.back());
  }
  else {
    this->libraryAliasStack.push_back({});
  }

  // Prepare the break stack.
  this->pushBreakStack();

  // Prepare the continue stack.
  this->pushContinueStack();

  // Prepare the identifierAssigned stack.
  this->identifiersAssignedStack.push_back({});

  // Preprocess the AST
  ast->compilePreprocess(*this, AstNode::Default);
}

void Program::popEnvironment() {
  // Remove stack entries.
  this->identifierStack.pop_back();
  this->stringStack.pop_back();

  // Try to "fill in" function stack declarations.
  for (auto & declaration : this->functionStackDeclarations) {
    // `declaration` is key/value pair of function name => vector of bytecodes.
    auto & functionName = declaration.first;

    if (this->functionsDeclared.count(functionName)) {
      // The function was declared within this scope, so we can set the
      // bytecodes to the correct values.
      for (auto bytecode : declaration.second) {

        this->setFunctionStackDeclaration(bytecode, this->functionsDeclared[functionName].first, this->functionsDeclared[functionName].second);
      }
      // Remove the bytecodes, because they have been filled in.
      this->functionStackDeclarations[functionName].clear();
    }
  }

  // Restore the `functionsCollected` stack to the previous scope state.
  this->functionsCollected.pop_back();

  // Restore the `libraryAliasStack` to the previous scope state.
  this->libraryAliasStack.pop_back();

  // Try to "fill in" break opcodes.
  this->popBreakStack(this->bytecode.size());

  // Try to "fill in" continue opcodes.
  this->popContinueStack(this->bytecode.size());

  // Pop the identifierAssigned stack.
  this->identifiersAssignedStack.pop_back();
}

void Program::compile() {
  // Prepare the environment.
  this->pushEnvironment(this->ast);

  // Reserve spaces on the stack for each variable.
  for ([[maybe_unused]] const auto & x : this->getIdentifiers()) {
    this->bytecode.push_back((uinteger_t)Opcode::NULLVAL);
  }

  // Reserve spaces on the stack for each string.
  // We must be careful to add them in the expected order, so figure out the
  // order first, and put that into `stringLiterals`.
  vector<pair<string, UnicodeString::Type>> stringLiterals(this->stringStack.back().size());
  for (auto & [item, position] : this->stringStack.back()) {
    stringLiterals[position] = item;
  }
  // Now that the strings are in the correct order, push them onto the stack.
  for (auto & [str, type] : stringLiterals) {
    AstNodeString(str, type, Tang::location{}).compileLiteral(*this);
  }

  // Compile the program.
  this->ast->compile(*this);

  // Release the environment.
  this->popEnvironment();
}

void Program::addIdentifier(const string & name, optional<size_t> position) {
  auto & identifiers = this->identifierStack.back();
  if (identifiers.count(name) == 0) {
    identifiers[name] = identifiers.size();
  }

  // If a specific position was requested, then swap entries as necessary.
  if (position && (identifiers[name] != *position)) {
    map<size_t, string> flipped{};
    for (auto i : identifiers) {
      flipped[i.second] = i.first;
    }
    identifiers[flipped[*position]] = identifiers[name];
    identifiers[name] = *position;
  }
};

const map<string, size_t>& Program::getIdentifiers() const {
  return this->identifierStack.back();
}

void Program::addLibraryAlias(const string & name) {
  auto & currentAliases = this->libraryAliasStack.back();
  currentAliases.insert({name, currentAliases.size()});
};

const map<string, uinteger_t> & Program::getLibraryAliases() const {
  return this->libraryAliasStack.back();
}

void Program::addIdentifierAssigned(const string & name) {
  this->identifiersAssignedStack.back().insert(name);
}

const set<string>& Program::getIdentifiersAssigned() const {
  return this->identifiersAssignedStack.back();
}

void Program::addString(const string & val, UnicodeString::Type type) {
  auto & strings = this->stringStack.back();
  if (strings.count({val, type}) == 0) {
    strings[{val, type}] = strings.size();
  }
}

const map<pair<string, UnicodeString::Type>, size_t>& Program::getStrings() const {
  return this->stringStack.back();
}

string Program::getCode() const {
  return this->code;
}

optional<const shared_ptr<AstNode>> Program::getAst() const {
  if (this->ast) {
    return this->ast;
  }
  return nullopt;
}

optional<const GarbageCollected> Program::getResult() const {
  return this->result;
}

size_t Program::addBytecode(uinteger_t op) {
  this->bytecode.push_back(op);
  return this->bytecode.size();
}

const Bytecode & Program::getBytecode() {
  return this->bytecode;
}

bool Program::setJumpTarget(size_t opcodeAddress, uinteger_t jumpTarget) {
  // Verify that the address is in scope.
  if (opcodeAddress >= this->bytecode.size() - 1) {
    return false;
  }
  // Verify that the opcodeAddress is, in fact, a jump instruction.
  // TODO

  // Set the instruction.
  this->bytecode[opcodeAddress + 1] = jumpTarget;
  return true;
}

bool Program::setFunctionStackDeclaration(size_t opcodeAddress, uinteger_t argc, uinteger_t targetPC) {
  // Verify that the address is in scope.
  if (opcodeAddress >= this->bytecode.size() - 2) {
    return false;
  }

  // Verify that the opcodeAddress is, in fact, a function declaration.
  if (this->bytecode[opcodeAddress] != (uinteger_t)Opcode::FUNCTION) {
    return false;
  }

  // Set the instruction.
  this->bytecode[opcodeAddress + 1] = argc;
  this->bytecode[opcodeAddress + 2] = targetPC;
  return true;
}

void Program::pushBreakStack() {
  this->breakStack.push_back({});
}

void Program::addBreak(size_t location) {
  this->breakStack.back().insert(location);
}

void Program::popBreakStack(size_t target) {
  for (auto i : this->breakStack.back()) {
    this->setJumpTarget(i, target);
  }
  this->breakStack.pop_back();
}

void Program::pushContinueStack() {
  this->continueStack.push_back({});
}

void Program::addContinue(size_t location) {
  this->continueStack.back().insert(location);
}

void Program::popContinueStack(size_t target) {
  for (auto i : this->continueStack.back()) {
    this->setJumpTarget(i, target);
  }
  this->continueStack.pop_back();
}

void Program::setAnnotation(size_t offset, const std::string & annotation) {
  this->annotations[offset] = annotation;
}

const map<size_t, string> & Program::getAnnotations() const {
  return this->annotations;
}

