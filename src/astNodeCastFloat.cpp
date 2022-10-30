/**
 * @file
 * Define the Tang::AstNodeCastFloat class.
 */

#include <bit>
#include "astNodeCastFloat.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCastFloat::AstNodeCastFloat(AstNode * expression, Tang::location location) : AstNode(location), expression{expression} {}

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

