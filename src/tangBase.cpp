/**
 * @file
 * Define the Tang::TangBase class.
 */

#include "tangBase.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionError.hpp"

using namespace std;
using namespace Tang;

TangBase::TangBase() {
  this->objectMethods = {
    {type_index(typeid(ComputedExpressionString)), {
      {"length", [](GarbageCollected & target, [[maybe_unused]] vector<GarbageCollected>& args) {
        if (typeid(*target) == typeid(ComputedExpressionString)) {
          return GarbageCollected::make<ComputedExpressionInteger>((integer_t)static_cast<ComputedExpressionString &>(*target).getValue().length());
        }
        return GarbageCollected::make<ComputedExpressionError>(Error{""});
      }},
     }},
  };
};

Program TangBase::compileScript(string script) {
  return Program{script, Program::CodeType::Script, this->shared_from_this()};
}

shared_ptr<TangBase> TangBase::make_shared() {
  return std::make_shared<TangBase>();
};

map<std::type_index, Tang::NativeBoundFunctionMap> & TangBase::getObjectMethods() {
  return this->objectMethods;
}

