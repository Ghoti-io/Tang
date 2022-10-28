/**
 * @file
 */

#include "astNodeSubtract.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeSubtract::dump(string indent) const {
  return indent + "Subtract:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeSubtract::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::SUBTRACT);
}

AstNode * AstNodeSubtract::makeCopy() const {
  return new AstNodeSubtract(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

