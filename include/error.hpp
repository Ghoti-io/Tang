
#include <string>
#include "location.hh"

namespace Tang {
  /**
   * The Error class is used to report any error of the system, whether a
   * syntax (parsing) error or a runtime (execution) error.
   */
  class Error {
  public:
    /**
     * Creates an empty error message.
     */
    Error();

    /**
     * Creates an error message using the supplied error string and location.
     *
     * @param message The error message as a string.
     * @param location The location of the error.
     */
    Error(std::string message, Tang::location location) : message{message}, location{location} {}

    /**
     * The error message as a string.
     */
    std::string message;

    /**
     * The location of the error
     */
    Tang::location location;
  };
}

