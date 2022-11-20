/**
 * @file
 * Define the Tang::AstNodeFunctionCall class.
 */

#include <string>
#include "astNodeFunctionCall.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeFunctionCall::AstNodeFunctionCall(shared_ptr<AstNode> function, vector<shared_ptr<AstNode>> argv, Tang::location location) : AstNode(location), function{function}, argv{argv} {}

string AstNodeFunctionCall::dump(string indent) const {
  string out = indent + "FunctionCall:\n"
    + indent + "  function:\n"
    + this->function->dump(indent + "    ")
    + indent + "  argv:\n";
  for (auto & arg : this->argv) {
    out += arg->dump(indent + "    ");
  }
  return out;
}

void AstNodeFunctionCall::compilePreprocess(Program & program, PreprocessState state) const {
  this->function->compilePreprocess(program, state);
  for (auto & arg : this->argv) {
    arg->compilePreprocess(program, state);
  }
}

void AstNodeFunctionCall::compile(Tang::Program & program) const {
  // Push the arguments onto the stack.
  for (auto & arg : this->argv) {
    arg->compile(program);
  }

  // Push the function onto the stack.
  this->function->compile(program);

  // Call the function.
  program.addBytecode((uinteger_t)Opcode::CALLFUNC);
  program.addBytecode((uinteger_t)this->argv.size());
}

