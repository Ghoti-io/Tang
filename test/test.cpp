#include <iostream>
#include "tang.hpp"

using namespace std;

int main() {
  Tang::Program program = Tang::TangBase().compileScript(R"(
    3
  )");

  //program.execute();
  auto ast = program.getAst();
  if (ast) {
    cout << (*ast)->dump();
  }

  cout << program.out << endl;
  cout << program.dumpBytecode() << endl;

  return 0;
}

