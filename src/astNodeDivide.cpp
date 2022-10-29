/**
 * @file
 */

#include "astNodeDivide.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeDivide::dump(string indent) const {
  return indent + "Divide:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeDivide::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::DIVIDE);
}

AstNode * AstNodeDivide::makeCopy() const {
  return new AstNodeDivide(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

