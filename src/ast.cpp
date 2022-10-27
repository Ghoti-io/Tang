/**
 * @file
 */

#include <iostream>
#include "ast.hpp"

using namespace std;
using namespace Tang;

AstNode::~AstNode() {}

string AstNode::dump(string indent) const {
  return indent + "\n";
}

void AstNode::compile([[maybe_unused]] Tang::Program & program) const {
}

AstNode * AstNode::makeCopy() const {
  return new AstNode(this->location);
}

