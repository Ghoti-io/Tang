/**
 * @file
 * Contains generic macros.
 */

#ifndef TANG_MACROS_HPP
#define TANG_MACROS_HPP

/**
 * Instruct the compiler that a function argument will not be used so that it
 * does not generate an error.
 *
 * When defining a funcion, use the TANG_UNUSED() macro around any argument
 * which is *not* used in the function, in order to squash any compiler
 * warnings.
 * e.g., void foo(int TANG_UNUSED(a)) {}
 *
 * @param x The argument to be ignored.
 */
#if defined(__GNUC__)
  #define TANG_UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
  #define TANG_UNUSED(x) /*@unused@*/ x
#else
  #define TANG_UNUSED(x) x
#endif

#endif // TANG_MACROS_HPP

