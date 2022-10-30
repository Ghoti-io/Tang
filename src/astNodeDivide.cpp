/**
 * @file
 * Define the Tang::AstNodeDivide class.
 */

#include "astNodeDivide.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeDivide::AstNodeDivide(AstNode * lhs, AstNode * rhs, Tang::location location) : AstNode(location), lhs{lhs}, rhs{rhs} {}

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

