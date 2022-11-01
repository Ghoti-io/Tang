/**
 * @file
 * Define the Tang::AstNodeBoolean class.
 */

#include <bit>
#include "astNodeBoolean.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeBoolean::AstNodeBoolean(bool val, Tang::location location) : AstNode(location), val{val} {}

string AstNodeBoolean::dump(string indent) const {
  return indent + "Boolean: " + (this->val ? "true" : "false") + "\n";
}

void AstNodeBoolean::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::BOOLEAN);
  program.addBytecode(this->val ? 1 : 0);
}

shared_ptr<AstNode> AstNodeBoolean::makeCopy() const {
  return make_shared<AstNodeBoolean>(this->val, this->location);
}
