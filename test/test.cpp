#include <iostream>
#include "tang.hpp"
#include "singletonObjectPool.hpp"

using namespace std;
using namespace Tang;

int main() {
  Tang::Program program = Tang::TangBase().compileScript(R"(
    3
  )");

  program.execute();
  auto ast = program.getAst();
  if (ast) {
    cout << (*ast)->dump();
  }

  cout << program.out << endl;
  cout << program.dumpBytecode() << endl;

  if (program.getResult()) {
    cout << (*program.getResult())->dump() << endl;
  }
  else {
    cout << "No result!" << endl;
  }

  cout << endl;

  auto & pool = SingletonObjectPool<ComputedExpressionInteger>::getInstance();

  auto i = new (pool.get()) ComputedExpressionInteger(42);
  cout << i->dump() << "\t" << i << endl;

  auto j = new (pool.get()) ComputedExpressionInteger(-8);
  cout << j->dump() << "\t" << j << endl;

  pool.recycle(i);
  auto k = new (pool.get()) ComputedExpressionInteger(1024);
  cout << k->dump() << "\t" << k << endl;

  cout << endl;
  cout << pool.get() << endl;
  cout << pool.get() << endl;
  cout << pool.get() << endl;
  cout << pool.get() << endl;
  cout << sizeof(ComputedExpressionInteger) << endl;

  return 0;
}

