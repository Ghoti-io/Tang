/**
 * @file
 */

#include <bit>
#include "astNodeCastInteger.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeCastInteger::dump(string indent) const {
  return indent + "Cast to Integer:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastInteger::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTINTEGER);
}

AstNode * AstNodeCastInteger::makeCopy() const {
  return new AstNodeCastInteger(this->expression->makeCopy(), this->location);
}

