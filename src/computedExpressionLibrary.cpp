/**
 * @file
 * Define the Tang::ComputedExpressionLibrary class.
 */

#include <typeinfo>
#include "tangBase.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionLibrary.hpp"
#include "computedExpressionNativeLibraryFunction.hpp"
#include "computedExpressionString.hpp"

using namespace std;
using namespace Tang;

ComputedExpressionLibrary::ComputedExpressionLibrary() {}

std::string ComputedExpressionLibrary::dump() const {
  return string("Library");
}

SPCE ComputedExpressionLibrary::makeCopy() const {
  return make_shared<ComputedExpressionLibrary>();
}

SPCE ComputedExpressionLibrary::__period([[maybe_unused]] const SPCE & member, [[maybe_unused]] shared_ptr<TangBase> & tang) const {
  if (typeid(*member) == typeid(ComputedExpressionString)) {
    auto & libraryAttributes = tang->getLibraryAttributes();
    auto thisType = type_index(typeid(*this));
    if (libraryAttributes.count(thisType)) {
      auto & attributes = libraryAttributes.at(thisType);
      string name = static_cast<ComputedExpressionString &>(*member).dump();
      if (attributes.count(name)) {
        auto & fn = attributes.at(name);
        return make_shared<ComputedExpressionNativeLibraryFunction>(fn);
      }
    }
  }

  return make_shared<ComputedExpressionError>(Error{"Member not found."});
}

