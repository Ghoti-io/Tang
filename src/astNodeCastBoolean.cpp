/**
 * @file
 * Define the Tang::AstNodeCastBoolean class.
 */

#include <bit>
#include "astNodeCastBoolean.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCastBoolean::AstNodeCastBoolean(AstNode * expression, Tang::location location) : AstNode(location), expression{expression} {}

string AstNodeCastBoolean::dump(string indent) const {
  return indent + "Cast to Boolean:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastBoolean::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTBOOLEAN);
}

AstNode * AstNodeCastBoolean::makeCopy() const {
  return new AstNodeCastBoolean(this->expression->makeCopy(), this->location);
}

