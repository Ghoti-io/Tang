/**
 * @file
 * Define the Tang::Program class.
 */

#include <sstream>
#include "program.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr}, error{nullptr} {
  this->parse();
  if (this->ast) {
    this->compile();
  }
}

Program::~Program() {
  if (this->error) {
    delete this->error;
  }
  if (this->ast) {
    delete this->ast;
  }
}

Program::Program(const Program & program) {
  this->code = program.code;
  this->codeType = program.codeType;
  this->ast = program.ast->makeCopy();
  this->error = new Error(*program.error);
  this->result = program.result;
}

Program::Program(Program && program) {
  swap(this->code, program.code);
  swap(this->codeType, program.codeType);
  swap(this->ast, program.ast);
  swap(this->error, program.error);
  swap(this->result, program.result);
}

Program & Program::operator=(const Program & program) {
  this->code = program.code;
  this->codeType = program.codeType;

  // `ast` is a pointer, so cleanup before replacing.
  if (this->ast) {
    delete this->ast;
    this->ast = nullptr;
  }
  if (program.ast) {
    this->ast = program.ast->makeCopy();
  }

  // `error` is a pointer, so cleanup before replacing.
  if (this->error) {
    delete this->error;
    this->error = nullptr;
  }
  if (program.error) {
    this->error = new Error(*program.error);
  }

  this->result = program.result;
  return *this;
}

Program & Program::operator=(Program && program) {
  swap(this->code, program.code);
  swap(this->codeType, program.codeType);
  swap(this->ast, program.ast);
  swap(this->error, program.error);
  swap(this->result, program.result);
  return *this;
}

void Program::parse() {
  stringstream ss{this->code};
  TangScanner scanner{ss, std::cout};
  TangParser parser{scanner, this->ast, this->error};
  parser.parse();
}

void Program::compile() {
  this->ast->compile(*this);
}

string Program::getCode() const {
  return this->code;
}

optional<const AstNode *> Program::getAst() const {
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

