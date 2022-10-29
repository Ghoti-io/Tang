/**
 * @file
 * Define the Tang::Error class used to describe syntax and runtime errors.
 */

#ifndef TANG_ERROR_HPP
#define TANG_ERROR_HPP

#include <string>
#include <ostream>
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
     */
    Error(std::string message) : message{message} {}

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

    /**
     * Add friendly output.
     *
     * @param out The output stream.
     * @param error The Error object.
     * @return The output stream.
     */
    friend std::ostream & operator<<(std::ostream & out, const Error & error);
  };
}

#endif // TANG_ERROR_HPP

