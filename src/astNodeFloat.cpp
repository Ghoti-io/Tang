/**
 * @file
 * Define the Tang::AstNodeFloat class.
 */

#include <bit>
#include "astNodeFloat.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeFloat::AstNodeFloat(float_t number, Tang::location location) : AstNode(location), val{number} {}

string AstNodeFloat::dump(string indent) const {
  return indent + "Float: " + to_string(this->val) + "\n";
}

void AstNodeFloat::compile(Tang::Program & program) const {
  program.addBytecode((uinteger_t)Opcode::FLOAT);
  program.addBytecode(bit_cast<uinteger_t>(this->val));
}

