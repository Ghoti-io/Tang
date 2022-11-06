/**
 * @file
 * Define the Tang::AstNodeString class.
 */

#include <bit>
#include <cmath>
#include <string.h>
#include "astNodeString.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeString::AstNodeString(const string & text, Tang::location location) : AstNode(location), val{text} {}

string AstNodeString::dump(string indent) const {
  return indent + "String: \"" + this->val + "\"\n";
}

void AstNodeString::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::STRING);
  program.addBytecode(bit_cast<uint64_t>(this->val.length()));
  // Pack the characters into the bytecode.
  uint64_t temp = 0;
  for (size_t i = 0; i < this->val.length(); ++i) {
    temp <<= sizeof(uint64_t);
    temp = temp | (uint64_t)this->val[i];
    if (i % sizeof(uint64_t) == sizeof(uint64_t) - 1) {
      program.addBytecode(temp);
      temp = 0;
    }
  }
  if (int i = this->val.length() % sizeof(uint64_t)) {
    // Pad the last bytecode and add to program.
    temp <<= 8 * (8 - i);
    program.addBytecode(temp);
  }
}

