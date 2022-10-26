/**
 * @file
 */

#include <iostream>
#include <bit>
#include "ast.hpp"
#include "macros.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

AstNode::~AstNode() {}

string AstNode::dump(string indent) const {
  return indent + "\n";
}

void AstNode::compile(Tang::Program & TANG_UNUSED(program)) const {
}

AstNode * AstNode::makeCopy() const {
  return new AstNode(this->location);
}

string AstNodeInteger::dump(string indent) const {
  return indent + "Integer: " + to_string(this->val) + "\n";
}

void AstNodeInteger::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::INTEGER);
  program.addBytecode(bit_cast<uint64_t>(this->val));
}

AstNode * AstNodeInteger::makeCopy() const {
  return new AstNodeInteger(this->val, this->location);
}

string AstNodeFloat::dump(string indent) const {
  return indent + "Float: " + to_string(this->val) + "\n";
}

void AstNodeFloat::compile(Tang::Program & program) const {
  program.addBytecode((uint64_t)Opcode::FLOAT);
  program.addBytecode(bit_cast<uint64_t>(this->val));
}

AstNode * AstNodeFloat::makeCopy() const {
  return new AstNodeFloat(this->val, this->location);
}

string AstNodeAdd::dump(string indent) const {
  return indent + "Add:\n"
    + indent + "  lhs:\n"
    + this->lhs->dump(indent + "    ")
    + indent + "  rhs:\n"
    + this->rhs->dump(indent + "    ");
}

void AstNodeAdd::compile(Tang::Program & program) const {
  this->lhs->compile(program);
  this->rhs->compile(program);
  program.addBytecode((uint64_t)Opcode::ADD);
}

AstNode * AstNodeAdd::makeCopy() const {
  return new AstNodeAdd(this->lhs->makeCopy(), this->rhs->makeCopy(), this->location);
}

