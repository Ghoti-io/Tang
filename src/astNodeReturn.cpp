/**
 * @file
 * Define the Tang::AstNodeReturn class.
 */

#include <string>
#include <bit>
#include "astNodeReturn.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeReturn::AstNodeReturn(shared_ptr<AstNode> expression, Tang::location location) : AstNode(location), expression{expression} {}

string AstNodeReturn::dump(string indent) const {
  return indent + "Return:\n" + this->expression->dump(indent + "  ");
}

void AstNodeReturn::collectIdentifiers(Program & program) const {
  this->expression->collectIdentifiers(program);
}

void AstNodeReturn::collectStrings(Program & program) const {
  this->expression->collectStrings(program);
}

void AstNodeReturn::compile(Tang::Program & program) const {
  this->expression->compile(program);
  program.addBytecode((uinteger_t)Opcode::RETURN);
  program.addBytecode((uinteger_t)program.getIdentifiers().size() + program.getStrings().size());
}

