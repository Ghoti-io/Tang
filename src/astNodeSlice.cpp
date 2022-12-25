/**
 * @file
 * Define the Tang::AstNodeSlice class.
 */

#include <string>
#include <bit>
#include "astNodeSlice.hpp"
#include "opcode.hpp"
#include "program.hpp"

using namespace std;
using namespace Tang;

AstNodeSlice::AstNodeSlice(shared_ptr<AstNode> collection, shared_ptr<AstNode> begin, shared_ptr<AstNode> end, shared_ptr<AstNode> skip, Tang::location location) : AstNode(location), collection{collection}, begin{begin}, end{end}, skip{skip} {}

string AstNodeSlice::dump(string indent) const {
  return indent + "Slice:"
    + indent + "  Collection:\n"
    + this->collection->dump(indent + "    ")
    + indent + "  Begin:\n"
    + this->begin->dump(indent + "    ")
    + indent + "  End:\n"
    + this->end->dump(indent + "    ")
    + indent + "  Skip:\n"
    + this->skip->dump(indent + "    ");
}

void AstNodeSlice::compile(Tang::Program & program) const {
  this->collection->compile(program);
  this->begin->compile(program);
  this->end->compile(program);
  this->skip->compile(program);
  
  program.addBytecode((uinteger_t)Opcode::SLICE);
}

void AstNodeSlice::compilePreprocess(Program & program, PreprocessState state) const {
  this->collection->compilePreprocess(program, state);
  this->begin->compilePreprocess(program, state);
  this->end->compilePreprocess(program, state);
  this->skip->compilePreprocess(program, state);
}

