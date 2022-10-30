/**
 * @file
 * Define the Tang::TangBase class.
 */

#include "tangBase.hpp"

using namespace std;
using namespace Tang;

TangBase::TangBase() {};

Program TangBase::compileScript(string script) {
  return Program{script, Program::CodeType::Script};
}

