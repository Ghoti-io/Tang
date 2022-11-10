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
  auto & strings = program.getStrings();
  if (strings.count(this->val)) {
    program.addBytecode((uinteger_t)Opcode::PEEK);
    program.addBytecode((uinteger_t)(strings.at(this->val) + program.getIdentifiers().size()));
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

void AstNodeString::compileLiteral(Tang::Program & program) const {
  program.addBytecode((uinteger_t)Opcode::STRING);
  program.addBytecode(bit_cast<uinteger_t>((integer_t)this->val.length()));
  // Pack the characters into the bytecode.
  uinteger_t temp = 0;
  for (size_t i = 0; i < this->val.length(); ++i) {
    temp <<= 8;
    temp |= (uinteger_t)this->val[i];
    if ((i % sizeof(uinteger_t)) == (sizeof(uinteger_t) - 1)) {
      program.addBytecode(temp);
      temp = 0;
    }
  }
  if (int i = this->val.length() % sizeof(uinteger_t)) {
    // Pad the last bytecode and add to program.
    temp <<= 8 * (sizeof(uinteger_t) - i);
    program.addBytecode(temp);
  }
}

void AstNodeString::collectStrings(Program & program) const {
  program.addString(this->val);
}

