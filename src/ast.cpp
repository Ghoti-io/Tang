#include <iostream>
#include "ast.hpp"

using namespace std;
using namespace Tang;

string AstNode::inspect() {
  return "";
}

string AstNodeInteger::inspect() {
  return to_string(this->val);
}

