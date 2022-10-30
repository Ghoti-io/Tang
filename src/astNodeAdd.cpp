/**
 * @file
 * Define the Tang::AstNodeAdd class.
 */

#include "astNodeAdd.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeAdd::AstNodeAdd(AstNode * lhs, AstNode * rhs, Tang::location location) : AstNode(location), lhs{lhs}, rhs{rhs} {}

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

