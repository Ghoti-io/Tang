/**
 * @file
 */

#include <bit>
#include "astNodeNegative.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeNegative::dump(string indent) const {
  return indent + "Negative:\n" + this->operand->dump(indent + "  ");
}

void AstNodeNegative::compile(Tang::Program & program) const {
  this->operand->compile(program);
  program.addBytecode((uint64_t)Opcode::NEGATIVE);
}

AstNode * AstNodeNegative::makeCopy() const {
  return new AstNodeNegative(this->operand->makeCopy(), this->location);
}

