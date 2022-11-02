/**
 * @file
 * Define the Tang::Program class.
 */

#include <sstream>
#include "program.hpp"
#include "opcode.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

void Program::parse() {
  stringstream ss{this->code};
  TangScanner scanner{ss, std::cout};
  Error * error{nullptr};
  TangParser parser{scanner, this->ast, error};
  parser.parse();
  if (error) {
    this->result = GarbageCollected::make<ComputedExpressionError>(*error);
    delete error;
  }
}

void Program::compile() {
  // Prepare the identifier mapping stack with an empty map.
  this->identifierStack.push_back(map<string,size_t>{});

  // Gather all of the identifiers in the current scope into the current map.
  this->ast->compileIdentifiers(*this);

  // Reserve spaces on the stack for each variable.
  for ([[maybe_unused]] const auto & x : this->identifierStack.back()) {
    this->bytecode.push_back((uint64_t)Opcode::NULLVAL);
  }

  // Compile the program.
  this->ast->compile(*this);
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

void Program::addBytecode(uint64_t op) {
  this->bytecode.push_back(op);
}

