/**
 * @file
 * Define the Tang::AstNodePrint class.
 */

#include <string>
#include "astNodeIdentifier.hpp"
#include "astNodePrint.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodePrint::AstNodePrint(Type type, shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), type{type}, expression{expression} {}

string AstNodePrint::dump(string indent) const {
  string description[] = {
    "Default",
  };
  return indent + "Print (" + description[this->type] + "):\n"
    + this->expression->dump(indent + "  ");
}

void AstNodePrint::compilePreprocess(Program & program, PreprocessState state) const {
  this->expression->compilePreprocess(program, state);
}

void AstNodePrint::compile(Tang::Program & program) const {
  integer_t index{-1};
  auto & identifier = program.getIdentifiers();
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) {
    auto & name = static_cast<AstNodeIdentifier &>(*this->expression).name;
    if (identifier.count(name)) {
      index = identifier.at(name);
    }
  }
  if (index >= 0) {
    program.addBytecode((uinteger_t)Opcode::PRINT_I);
    program.addBytecode((uinteger_t)index);
  }
  else {
    this->expression->compile(program);
    program.addBytecode((uinteger_t)Opcode::PRINT_S);
  }
}

