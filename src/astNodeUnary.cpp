/**
 * @file
 * Define the Tang::AstNodeUnary class.
 */

#include <string>
#include <bit>
#include "astNodeIdentifier.hpp"
#include "astNodeString.hpp"
#include "astNodeUnary.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

#define UNARYOP(OP_S, OP_I) \
  integer_t index{-1}; \
  auto & identifier = program.getIdentifiers(); \
  if (typeid(*this->operand) == typeid(AstNodeIdentifier)) { \
    auto & name = static_cast<AstNodeIdentifier &>(*this->operand).name; \
    if (identifier.count(name)) { \
      index = identifier.at(name); \
    } \
  } \
  else if (typeid(*this->operand) == typeid(AstNodeString)) { \
    auto & strings = program.getStrings(); \
    auto & stringConv = static_cast<AstNodeString &>(*this->operand); \
    auto & val = stringConv.getVal(); \
    auto & type = stringConv.getType(); \
    if (strings.count({val, type})) { \
      index = strings.at({val, type}) + program.getIdentifiers().size(); \
    } \
  } \
  if (index >= 0) { \
    program.addBytecode((uinteger_t)Opcode:: OP_I); \
    program.addBytecode((uinteger_t)index); \
  } \
  else { \
    this->operand->compile(program); \
    program.addBytecode((uinteger_t)Opcode:: OP_S); \
  } \
  return;

AstNodeUnary::AstNodeUnary(Operator op, shared_ptr<AstNode> operand, Tang::location location) : AstNode(location), op{op}, operand{operand} {}

string AstNodeUnary::dump(string indent) const {
  string description[] = {
    "Negative",
    "Not",
  };
  return indent + "Unary (" + description[this->op] + "):\n" + this->operand->dump(indent + "  ");
}

void AstNodeUnary::compilePreprocess(Program & program, PreprocessState state) const {
  this->operand->compilePreprocess(program, state);
}

void AstNodeUnary::compile(Tang::Program & program) const {
  switch (this->op) {
    case Negative: {
      UNARYOP(NEGATIVE_S, NEGATIVE_I);
      break;
    }
    case Not: {
      UNARYOP(NOT_S, NOT_I);
      break;
    }
  }
}

