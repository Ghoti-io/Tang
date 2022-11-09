/**
 * @file
 * Define the Tang::AstNodeUnary class.
 */

#include <string>
#include <bit>
#include "astNodeUnary.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeUnary::AstNodeUnary(Operator op, shared_ptr<AstNode> operand, Tang::location location) : AstNode(location), op{op}, operand{operand} {}

string AstNodeUnary::dump(string indent) const {
  string description[] = {
    "Negative",
    "Not",
  };
  return indent + "Unary (" + description[this->op] + "):\n" + this->operand->dump(indent + "  ");
}

void AstNodeUnary::collectIdentifiers(Program & program) const {
  this->operand->collectIdentifiers(program);
}

void AstNodeUnary::collectStrings(Program & program) const {
  this->operand->collectStrings(program);
}

void AstNodeUnary::compile(Tang::Program & program) const {
  this->operand->compile(program);
  switch (this->op) {
    case Negative: {
      program.addBytecode((uinteger_t)Opcode::NEGATIVE);
      break;
    }
    case Not: {
      program.addBytecode((uinteger_t)Opcode::NOT);
      break;
    }
  }
}

