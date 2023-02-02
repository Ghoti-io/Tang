/**
 * @file
 * Define the Tang::TangBase class.
 */

#include <dlfcn.h>
#include <memory>
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

#define LIBRARY(alias, type) {alias, []([[maybe_unused]] Context & context) -> SPCE { \
  return std::make_shared<type>();\
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

Program TangBase::compileScript(const string & script) {
  return Program{script, Program::CodeType::Script, this->shared_from_this()};
}

Program TangBase::compileScript(istream & script) {
  return Program{script, Program::CodeType::Script, this->shared_from_this()};
}

Program TangBase::compileTemplate(const string & code) {
  return Program{code, Program::CodeType::Template, this->shared_from_this()};
}

Program TangBase::compileTemplate(istream & code) {
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

bool TangBase::loadLibrary(const string & path) {
  if (void * library_handle = dlopen(path.c_str(), RTLD_NOW | RTLD_NODELETE)) {
    // Reset any errors.
    TangCustomLibraryLoader func = (TangCustomLibraryLoader)dlsym(library_handle, "TangCustomLibraryLoader");
    const char * dlsym_error = dlerror();
    dlclose(library_handle);
    if (dlsym_error) {
      cerr << "Could not find `TangCustomLibraryLoader` in path " << path << endl;
      return false;
    }
    func(this->shared_from_this());
    return true;
  }
  cerr << "Could not load library at path " << path << endl;
  return false;
}

