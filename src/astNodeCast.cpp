/**
 * @file
 * Define the Tang::AstNodeCast class.
 */

#include <bit>
#include "astNodeCast.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCast::AstNodeCast(Type targetType, shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), targetType{targetType}, expression{expression} {}

string AstNodeCast::dump(string indent) const {
  string description[] {
    "Integer",
    "Float",
    "Boolean",
    "String",
  };
  return indent + "Cast to " + description[this->targetType] + ":\n" + this->expression->dump(indent + "  ");
}

void AstNodeCast::compilePreprocess(Program & program, PreprocessState state) const {
  this->expression->compilePreprocess(program, state);
}

void AstNodeCast::compile(Tang::Program & program) const {
  this->expression->compile(program);
  switch (this->targetType) {
    case Integer: {
      program.addBytecode((uinteger_t)Opcode::CASTINTEGER);
      break;
    }
    case Float: {
      program.addBytecode((uinteger_t)Opcode::CASTFLOAT);
      break;
    }
    case Boolean: {
      program.addBytecode((uinteger_t)Opcode::CASTBOOLEAN);
      break;
    }
    case String: {
      program.addBytecode((uinteger_t)Opcode::CASTSTRING);
      break;
    }
  }
}

