/**
 * @file
 * Define the Tang::shared_ptr<AstNode>CastFloat class.
 */

#include <bit>
#include "astNodeCastFloat.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCastFloat::AstNodeCastFloat(shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), expression{expression} {}

string AstNodeCastFloat::dump(string indent) const {
  return indent + "Cast to Float:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastFloat::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTFLOAT);
}

shared_ptr<AstNode> AstNodeCastFloat::makeCopy() const {
  return make_shared<AstNodeCastFloat>(this->expression->makeCopy(), this->location);
}

