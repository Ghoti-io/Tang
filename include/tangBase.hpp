/**
 * @file
 * Declare the Tang::TangBase class used to interact with Tang.
 */

namespace Tang {
  class TangBase;
}

#ifndef TANG_TANGBASE_HPP
#define TANG_TANGBASE_HPP

#include <memory>
#include <string>
#include "program.hpp"

/**
 * \mainpage Tang: A Template Language
 *
 * \section A Quick Description
 *
 * **Tang** is a C++ Template Language.  It takes the form of a library
 * which may be included in other projects.  It is under active development,
 * and you can follow its progress here:
 * - [YouTube playlist](https://www.youtube.com/playlist?list=PLZqirAnnqaCZ8lT8w7p2PUB7tqrId7d89)
 * - [GitHub repository](https://github.com/coreyp1/Tang)
 *
 * \section Features
 *
 * The following features are planned:
 * - Native support for Unicode/Utf-8 strings.
 * - Change from template to script mode using escape tags like PHP.
 * - Loosely typed, with Python-like indexing and slicing of containers.
 * - Syntax similar to C/C++/PHP.
 * - Code compiles to a custom Bytecode and is executed by the Tang VM.
 * - Fast and thread-safe.
 *
 * \section License
 *
 * \verbinclude LICENSE
 */


namespace Tang {
  /**
   * The base class for the Tang programming language.
   *
   * This class is the fundamental starting point to compile and execute a
   * Tang program.  It may be considered in three parts:
   *
   * 1. It acts as an extendable interface through which additional "library"
   *    functions can be added to the language.
   *
   *    It is intentionally designed that each instance of \ref TangBase will
   *    have its own library functions.
   *
   * 2. It provides methods to compile scripts and templates, resulting in a
   *    \ref Program object.
   *
   * 3. The \ref Program object may then be executed, providing
   *    instance-specific context information (*i.e.*, state).
   */
  class TangBase: public std::enable_shared_from_this<TangBase> {
  public:
    /**
     * Create an instance of Tang and return a reference to it as a shared
     * pointer.
     *
     * @return A shared pointer to the base Tang object.
     */
    static std::shared_ptr<TangBase> make_shared();

    /**
     * Compile the provided source code as a script and return a Program.
     *
     * @param script The Tang script to be compiled.
     * @return The Program object representing the compiled script.
     */
    Program compileScript(std::string script);

    /**
     * The constructor.
     *
     * This function should never be called directly.  Rather, always use the
     * Tang::TangBase() static method, which supplies the shared pointer
     * necessary for creation of Program objects.
     */
    TangBase();
  };
}

#endif // TANG_TANGBASE_HPP

