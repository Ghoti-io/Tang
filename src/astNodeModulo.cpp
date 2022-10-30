/**
 * @file
 * Define the Tang::AstNodeModulo class.
 */

#include "astNodeModulo.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeModulo::AstNodeModulo(AstNode * lhs, AstNode * rhs, Tang::location location) : AstNode(location), lhs{lhs}, rhs{rhs} {}

string AstNodeModulo::dump(string indent) const {
  return indent + "Modulo:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeModulo::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::MODULO);
}

AstNode * AstNodeModulo::makeCopy() const {
  return new AstNodeModulo(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

