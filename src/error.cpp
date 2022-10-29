/**
 * @file
 */

#include "error.hpp"

Tang::Error::Error() : message{} {};
namespace Tang {
  std::ostream & operator<<(std::ostream & out, const Error & error) {
    return out << "Error: " << error.message;
  }
}

