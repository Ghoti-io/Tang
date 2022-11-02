/**
 * @file
 * Define the Tang::AstNodeNull class.
 */

#include <bit>
#include "astNodeNull.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeNull::AstNodeNull(Tang::location location) : AstNode(location) {}

string AstNodeNull::dump(string indent) const {
  return indent + "NULL\n";
}

void AstNodeNull::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::NULLVAL);
}

