/**
 * @file
 * Define the Tang::AstNodeString class.
 */

#include <bit>
#include <cmath>
#include <string.h>
#include "astNodeString.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeString::AstNodeString(const string & text, Tang::location location) : AstNode(location), val{text}, type{UnicodeString::Type::Trusted} {}

AstNodeString::AstNodeString(const string & text, UnicodeString::Type type, Tang::location location) : AstNode(location), val{text}, type{type} {}

string AstNodeString::dump(string indent) const {
  return indent + "String: \"" + this->val + "\"\n";
}

void AstNodeString::compile(Tang::Program & program) const {
  auto & strings = program.getStrings();
  if (strings.count({this->val, this->type})) {
    program.addBytecode((uinteger_t)Opcode::PEEK);
    program.addBytecode((uinteger_t)(strings.at({this->val, this->type}) + program.getIdentifiers().size()));
  }
  else {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

void AstNodeString::compileLiteral(Tang::Program & program) const {
  program.addBytecode((uinteger_t)Opcode::STRING);
  program.addBytecode((uinteger_t)this->type);
  program.addBytecode(bit_cast<uinteger_t>((integer_t)this->val.length()));
  // Pack the characters into the bytecode.
  uinteger_t temp = 0;
  for (size_t i = 0; i < this->val.length(); ++i) {
    temp <<= 8;
    // In order to handle UTF-8 encodings as well as ASCII values larger than
    // 127, we ***must*** cast the string character as a uint8_t first, then
    // to the uinteger_t.
    temp |= (uinteger_t)(uint8_t)this->val[i];
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

void AstNodeString::compilePreprocess(Program & program, [[maybe_unused]] PreprocessState state) const {
  program.addString(this->val, this->type);
}

