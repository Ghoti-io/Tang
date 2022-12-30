#include <iostream>
#include "tang.hpp"

using namespace Tang;
using namespace std;

int main() {
  auto tang = TangBase::make_shared();
  auto program = tang->compileScript(cin);
  cout << program.execute().out;
  return 0;
}

