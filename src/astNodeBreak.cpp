/**
 * @file
 * Define the Tang::AstNodeBreak class.
 */

#include <bit>
#include "astNodeBreak.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeBreak::AstNodeBreak(Tang::location location) : AstNode(location) {}

string AstNodeBreak::dump(string indent) const {
  return indent + "Break\n";
}

void AstNodeBreak::compile(Tang::Program & program) const {
  // Record the fact that there is a `break` statement here.
  program.addBreak(program.getBytecode().size());

  // The `break` statement is represented by a JMP opcode.
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode(0);
}

