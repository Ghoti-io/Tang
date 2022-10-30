/**
 * @file
 * Define the Tang::AstNode class.
 */

#include <iostream>
#include "astNode.hpp"

using namespace std;
using namespace Tang;

AstNode::AstNode(Tang::location location) : location {location} {}

AstNode::~AstNode() {}

string AstNode::dump(string indent) const {
  return indent + "\n";
}

void AstNode::compile([[maybe_unused]] Tang::Program & program) const {
}

shared_ptr<AstNode> AstNode::makeCopy() const {
  return shared_ptr<AstNode>(new AstNode(this->location));
}

