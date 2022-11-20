/**
 * @file
 * Define the Tang::AstNodePrint class.
 */

#include <string>
#include "astNodePrint.hpp"
#include "opcode.hpp"

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
  this->expression->compile(program);
  switch (this->type) {
    case Default: {
      program.addBytecode((uinteger_t)Opcode::PRINT);
      break;
    }
  }
}

