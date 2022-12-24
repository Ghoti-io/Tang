/**
 * @file
 * Define the Tang::TangBase class.
 */

#include "tangBase.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

TangBase::TangBase() : objectMethods{
    {type_index(typeid(ComputedExpressionArray)), ComputedExpressionArray::getMethods()},
    {type_index(typeid(ComputedExpressionString)), ComputedExpressionString::getMethods()},
  }, libraries{} {};

Program TangBase::compileScript(string script) {
  return Program{script, Program::CodeType::Script, this->shared_from_this()};
}

Program TangBase::compileTemplate(string code) {
  return Program{code, Program::CodeType::Template, this->shared_from_this()};
}

shared_ptr<TangBase> TangBase::make_shared() {
  return std::make_shared<TangBase>();
};

map<std::type_index, Tang::NativeBoundFunctionMap> & TangBase::getObjectMethods() {
  return this->objectMethods;
}

LibraryFunctionMap & TangBase::getLibraries() {
  return this->libraries;
}

unordered_map<std::type_index, LibraryFunctionMap> & TangBase::getLibraryAttributes() {
  return this->libraryAttributes;
}

