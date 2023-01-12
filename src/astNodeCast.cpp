/**
 * @file
 * Define the Tang::AstNodeCast class.
 */

#include <bit>
#include "astNodeCast.hpp"
#include "astNodeIdentifier.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

#define CASTOP(OP_S, OP_I) \
  integer_t index{-1}; \
  auto & identifier = program.getIdentifiers(); \
  if (typeid(*this->expression) == typeid(AstNodeIdentifier)) { \
    auto & name = static_cast<AstNodeIdentifier &>(*this->expression).name; \
    if (identifier.count(name)) { \
      index = identifier.at(name); \
    } \
  } \
  if (index >= 0) { \
    program.addBytecode((uinteger_t)Opcode:: OP_I); \
    program.addBytecode((uinteger_t)index); \
  } \
  else { \
    this->expression->compile(program); \
    program.addBytecode((uinteger_t)Opcode:: OP_S); \
  } \
  return;

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
      CASTOP(CASTINTEGER_S, CASTINTEGER_I);
      break;
    }
    case Float: {
      CASTOP(CASTFLOAT_S, CASTFLOAT_I);
      break;
    }
    case Boolean: {
      CASTOP(CASTBOOLEAN_S, CASTBOOLEAN_I);
      break;
    }
    case String: {
      CASTOP(CASTSTRING_S, CASTSTRING_I);
      break;
    }
  }
}

