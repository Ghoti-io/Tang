/**
 * @file
 * Define the Tang::AstNodeCastInteger class.
 */

#include <bit>
#include "astNodeCastInteger.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCastInteger::AstNodeCastInteger(shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), expression{expression} {}

string AstNodeCastInteger::dump(string indent) const {
  return indent + "Cast to Integer:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastInteger::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTINTEGER);
}

shared_ptr<AstNode> AstNodeCastInteger::makeCopy() const {
  return make_shared<AstNodeCastInteger>(this->expression->makeCopy(), this->location);
}

