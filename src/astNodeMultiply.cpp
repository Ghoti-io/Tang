/**
 * @file
 */

#include "astNodeMultiply.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeMultiply::dump(string indent) const {
  return indent + "Multiply:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeMultiply::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::MULTIPLY);
}

AstNode * AstNodeMultiply::makeCopy() const {
  return new AstNodeMultiply(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

