/**
 * @file
 */

#include "astNodeAdd.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeAdd::dump(string indent) const {
  return indent + "Add:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeAdd::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::ADD);
}

AstNode * AstNodeAdd::makeCopy() const {
  return new AstNodeAdd(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

