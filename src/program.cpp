#include <sstream>
#include "program.hpp"
#include "tangScanner.hpp"
#include "tangParser.hpp"

using namespace std;
using namespace Tang;

Tang::Program::Program(string code, Program::CodeType codeType) : code{code}, codeType{codeType}, ast{nullptr}, error{nullptr} {
  this->compile();
}

void Tang::Program::execute() {}

void Tang::Program::compile() {
  stringstream ss{this->code};
  TangScanner scanner{ss, std::cout};
  TangParser parser{scanner, this->ast, this->error};
  parser.parse();
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

