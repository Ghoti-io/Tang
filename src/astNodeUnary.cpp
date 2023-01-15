/**
 * @file
 * Define the Tang::AstNodeUnary class.
 */

#include <string>
#include <bit>
#include "astNodeIdentifier.hpp"
#include "astNodeString.hpp"
#include "astNodeUnary.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "program.hpp"

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

void AstNodeUnary::compilePreprocess(Program & program, PreprocessState state) const {
  this->operand->compilePreprocess(program, state);
}

void AstNodeUnary::compile(Tang::Program & program) const {
  switch (this->op) {
    case Negative: {
      UNARYOP(this->operand, NEGATIVE_S, NEGATIVE_I);
      break;
    }
    case Not: {
      UNARYOP(this->operand, NOT_S, NOT_I);
      break;
    }
  }
}

