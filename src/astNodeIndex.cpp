/**
 * @file
 * Define the Tang::AstNodeIndex class.
 */

#include <string>
#include <bit>
#include "astNodeIndex.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNodeIndex::AstNodeIndex(shared_ptr<AstNode> collection, shared_ptr<AstNode> index, Tang::location location) : AstNode(location), collection{collection}, index{index} {}

string AstNodeIndex::dump(string indent) const {
  return indent + "Index:\n"
    + indent + "  Collection:\n"
    + this->collection->dump(indent + "    ")
    + indent + "  Index:\n"
    + this->index->dump(indent + "    ");
}

void AstNodeIndex::compilePreprocess(Program & program) const {
  this->collection->compilePreprocess(program);
  this->index->compilePreprocess(program);
}

void AstNodeIndex::compile(Tang::Program & program) const {
  this->collection->compile(program);
  this->index->compile(program);
  program.addBytecode((uinteger_t)Opcode::INDEX);
}

