/**
 * @file
 * Define the Tang::AstNodePeriod class.
 */

#include <string>
#include <bit>
#include "astNodePeriod.hpp"
#include "astNodeString.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodePeriod::AstNodePeriod(shared_ptr<AstNode> lhs, string rhs, Tang::location location) : AstNode(location), lhs{lhs}, rhs{rhs} {}

string AstNodePeriod::dump(string indent) const {
  return indent + "Period:\n"
    + indent + "  LHS:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  RHS:\n"
    + indent + "    " + this->rhs + "\n";
}

void AstNodePeriod::compilePreprocess(Program & program, PreprocessState state) const {
  this->lhs->compilePreprocess(program, state);
  AstNodeString(this->rhs, this->location).compilePreprocess(program, state);
}

void AstNodePeriod::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  AstNodeString(this->rhs, this->location).compile(program);
  program.addBytecode((uinteger_t)Opcode::PERIOD);
}

