/**
 * @file
 * Define the Tang::AstNodeIndex class.
 */

#include <string>
#include <bit>
#include "astNodeIdentifier.hpp"
#include "astNodeIndex.hpp"
#include "astNodeString.hpp"
#include "macros.hpp"
#include "opcode.hpp"
#include "program.hpp"

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

void AstNodeIndex::compilePreprocess(Program & program, PreprocessState state) const {
  this->collection->compilePreprocess(program, state);
  this->index->compilePreprocess(program, state);
}

void AstNodeIndex::compile(Tang::Program & program) const {
  BINARYOP(this->collection, this->index, INDEX_SS, INDEX_SI, INDEX_IS, INDEX_II);
}

const std::shared_ptr<const AstNode> AstNodeIndex::getCollection() const {
  return this->collection;
}

const std::shared_ptr<const AstNode> AstNodeIndex::getIndex() const {
  return this->index;
}

