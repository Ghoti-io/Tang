#include "macros.hpp"
#include "computedExpressionLibrary.hpp"
#include "garbageCollected.hpp"

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

