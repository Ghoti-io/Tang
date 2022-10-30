/**
 * @file
 * Define the Tang::AstNodeCastBoolean class.
 */

#include <bit>
#include "astNodeCastBoolean.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeCastBoolean::AstNodeCastBoolean(shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), expression{expression} {}

string AstNodeCastBoolean::dump(string indent) const {
  return indent + "Cast to Boolean:\n" + this->expression->dump(indent + "  ");
}

void AstNodeCastBoolean::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uint64_t)Opcode::CASTBOOLEAN);
}

shared_ptr<AstNode> AstNodeCastBoolean::makeCopy() const {
  return make_shared<AstNodeCastBoolean>(this->expression->makeCopy(), this->location);
}

