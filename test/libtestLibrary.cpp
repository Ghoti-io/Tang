#include "tang.hpp"

using namespace std;
using namespace Tang;

/**
 * Custom Library Loader function.
 *
 * This function is called when the libtestLibrary.so library is loaded by the
 * TangBase object.  It must be called by this exact name, and it must be
 * declared `extern "C"` to disable C++ name mangling.
 *
 * @param tang A shared pointer to the TangBase object.
 */
extern "C" void TangCustomLibraryLoader(std::shared_ptr<TangBase> tang) {
  auto & methods = tang->getObjectMethods();
  // Add `custom_function` as a method to any ComputedExpressionString.
  methods[type_index(typeid(ComputedExpressionString))]["custom_function"] = {0,
    []([[maybe_unused]] SPCE & target, [[maybe_unused]] vector<SPCE>& args) -> SPCE {
      // `custom_function() will return a ComputedExpressionNativeFunction.
      return make_shared<ComputedExpressionNativeFunction>(
        []([[maybe_unused]] vector<SPCE>& args, [[maybe_unused]] Context & context) -> SPCE {
          // We are in a ComputedExpressionNativeFunction.  It has access to
          // the execution Context.  This function will use the Context to
          // store a variable that it  will increment each time that the
          // function is called.
          int count = 0;

          // Check to see if the variable already exists.
          if (context.data.count("custom_function")) {
            auto & val = context.data.at("custom_function");
            if (val.type() != typeid(int)) {
              // The variable is not the type that was expected, so something
              // went wrong.  Rather than overwriting the function, we will
              // simply return an error.
              return make_shared<ComputedExpressionError>(Error{"Something went wrong!"});
            }
            // The variable exists as an integer.  Increment it.
            count = any_cast<int>(val) + 1;
            val = count;
          }
          else {
            // The variable did not exist, set it.
            context.data["custom_function"] = (int)0;
          }
          // Return the `count` as an integer.
          return make_shared<ComputedExpressionInteger>(count);
        }, (size_t)0);
    }};
}

