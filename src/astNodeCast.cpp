/**
 * @file
 * Define the Tang::AstNodeCast class.
 */

#include <bit>
#include "astNodeCast.hpp"
#include "astNodeIdentifier.hpp"
#include "astNodeString.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "program.hpp"

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
  switch (this->targetType) {
    case Integer: {
      UNARYOP(this->expression, CASTINTEGER_S, CASTINTEGER_I);
      break;
    }
    case Float: {
      UNARYOP(this->expression, CASTFLOAT_S, CASTFLOAT_I);
      break;
    }
    case Boolean: {
      UNARYOP(this->expression, CASTBOOLEAN_S, CASTBOOLEAN_I);
      break;
    }
    case String: {
      UNARYOP(this->expression, CASTSTRING_S, CASTSTRING_I);
      break;
    }
  }
}

