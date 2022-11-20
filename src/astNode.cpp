/**
 * @file
 * Define the Tang::AstNode class.
 */

#include <iostream>
#include "macros.hpp"
#include "astNode.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNode::AstNode(Tang::location location) : location {location} {}

AstNode::~AstNode() {}

string AstNode::dump(string indent) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually AstNode, and not a derived type that forgot to override the
  // virtual method.
  return typeid(*this) == typeid(AstNode)
   ? indent + "NULL\n"
   : indent + "UNKNOWN\n";
}

void AstNode::compile(Tang::Program & program) const {
  // Because this is a virtual function, we must ensure that the type is
  // actually AstNode, and not a derived type that forgot to override the
  // virtual method.
  if (typeid(*this) == typeid(AstNode)) {
    program.addBytecode((uinteger_t)Opcode::NULLVAL);
  }
}

void AstNode::compilePreprocess([[maybe_unused]] Program & program, [[maybe_unused]] PreprocessState state) const {}

