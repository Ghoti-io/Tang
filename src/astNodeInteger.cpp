/**
 * @file
 */

#include <bit>
#include "astNodeInteger.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

string AstNodeInteger::dump(string indent) const {
  return indent + "Integer: " + to_string(this->val) + "\n";
}

void AstNodeInteger::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::INTEGER);
  program.addBytecode(bit_cast<uint64_t>(this->val));
}

AstNode * AstNodeInteger::makeCopy() const {
  return new AstNodeInteger(this->val, this->location);
}

