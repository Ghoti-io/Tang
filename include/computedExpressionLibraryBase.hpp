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
      GarbageCollected makeCopy() const override {
        return GarbageCollected::make<ComputedExpressionLibraryBase>();
      }
      static LibraryFunctionMap getLibraryAttributes();
  };
}

#undef ComputedExpressionLibraryBase

