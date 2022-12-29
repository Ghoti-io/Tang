/**
 * @file
 * Define the Tang::TangBase class.
 */

#include "tangBase.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionLibraryMath.hpp"
#include "computedExpressionLibraryTang.hpp"
#include "context.hpp"

using namespace std;
using namespace Tang;

#define OBJECTMETHOD(type) {type_index(typeid(type)), type::getMethods()}

#define LIBRARY(alias, type) {alias, []([[maybe_unused]] Context & context) { \
  return GarbageCollected::make<type>();\
}}

#define LIBRARYATTRIBUTES(type) {type_index(typeid(type)), type::getLibraryAttributes()}

TangBase::TangBase() : objectMethods{
    OBJECTMETHOD(ComputedExpressionArray),
    OBJECTMETHOD(ComputedExpressionString),
  },
  libraries{
    LIBRARY("math", ComputedExpressionLibraryMath),
    LIBRARY("tang", ComputedExpressionLibraryTang),
	},
  libraryAttributes{
    LIBRARYATTRIBUTES(ComputedExpressionLibraryMath),
    LIBRARYATTRIBUTES(ComputedExpressionLibraryTang),
	} {};

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

