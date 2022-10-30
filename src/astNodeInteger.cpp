/**
 * @file
 * Define the Tang::AstNodeInteger class.
 */

#include <bit>
#include "astNodeInteger.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeInteger::AstNodeInteger(int64_t number, Tang::location location) : AstNode(location), val{number} {}

string AstNodeInteger::dump(string indent) const {
  return indent + "Integer: " + to_string(this->val) + "\n";
}

void AstNodeInteger::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::INTEGER);
  program.addBytecode(bit_cast<uint64_t>(this->val));
}

shared_ptr<AstNode> AstNodeInteger::makeCopy() const {
  return make_shared<AstNodeInteger>(this->val, this->location);
}

