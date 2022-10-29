/**
 * @file
 */

#include <bit>
#include "astNodeCastFloat.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeCastFloat::dump(string indent) const {
  return indent + "Cast to Float:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastFloat::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTFLOAT);
}

AstNode * AstNodeCastFloat::makeCopy() const {
  return new AstNodeCastFloat(this->expression->makeCopy(), this->location);
}

