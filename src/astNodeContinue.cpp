/**
 * @file
 * Define the Tang::AstNodeContinue class.
 */

#include <bit>
#include "astNodeContinue.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeContinue::AstNodeContinue(Tang::location location) : AstNode(location) {}

string AstNodeContinue::dump(string indent) const {
  return indent + "Continue\n";
}

void AstNodeContinue::compile(Tang::Program & program) const {
  // Record the fact that there is a `continue` statement here.
  program.addContinue(program.getBytecode().size());

  // The `continue` statement is represented by a JMP opcode.
  program.addBytecode((uinteger_t)Opcode::JMP);
  program.addBytecode(0);
}

