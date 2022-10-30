/**
 * @file
 * Define the Tang::AstNodeNegative class.
 */

#include <bit>
#include "astNodeNegative.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeNegative::AstNodeNegative(AstNode * operand, Tang::location location) : AstNode(location), operand{operand} {}

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

