#include <iostream>
#include "ast.hpp"

using namespace std;
using namespace Tang;

string AstNode::dump(string indent) const {
  return indent + "\n";
}

string AstNodeInteger::dump(string indent) const {
  return indent + "Integer: " + to_string(this->val) + "\n";
}

