#include "macros.hpp"
#include "computedExpressionLibrary.hpp"
#include "garbageCollected.hpp"

#ifndef ComputedExpressionLibraryBase
  #error "ComputedExpressionLibraryBase has not been defined."
#endif

namespace Tang {
  class ComputedExpressionLibraryBase: public ComputedExpressionLibrary {
    public:
      ComputedExpressionLibraryBase() {}
      SPCE makeCopy() const override {
        return std::make_shared<ComputedExpressionLibraryBase>();
      }
      static LibraryFunctionMap getLibraryAttributes();
  };
}

#undef ComputedExpressionLibraryBase

