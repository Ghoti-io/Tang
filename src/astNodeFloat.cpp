/**
 * @file
 * Define the Tang::AstNodeFloat class.
 */

#include <bit>
#include "astNodeFloat.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeFloat::AstNodeFloat(double number, Tang::location location) : AstNode(location), val{number} {}

string AstNodeFloat::dump(string indent) const {
  return indent + "Float: " + to_string(this->val) + "\n";
}

void AstNodeFloat::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::FLOAT);
  program.addBytecode(bit_cast<uint64_t>(this->val));
}

