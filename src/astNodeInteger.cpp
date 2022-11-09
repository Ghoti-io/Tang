/**
 * @file
 * Define the Tang::AstNodeInteger class.
 */

#include <bit>
#include "astNodeInteger.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeInteger::AstNodeInteger(integer_t number, Tang::location location) : AstNode(location), val{number} {}

string AstNodeInteger::dump(string indent) const {
  return indent + "Integer: " + to_string(this->val) + "\n";
}

void AstNodeInteger::compile(Tang::Program & program) const {
  program.addBytecode((uinteger_t)Opcode::INTEGER);
  program.addBytecode(bit_cast<uinteger_t>(this->val));
}

