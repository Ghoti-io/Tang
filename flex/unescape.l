/*
 * Generate a C++ Scanner class.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Cxx.html#Cxx
 */
%option c++

/*
 * Tell flex the name of our scanner class.  It must inherit from yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option yyclass="UnescapeFlexLexer"

/*
 * Use "TangTang" as a name prefix rather than "yy".  In C++, this only applies to
 * yywrap (addressed in the next option) and yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option prefix="TangUnescape"

/*
 * Get rid of yywrap.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Options-Affecting-Scanner-Behavior.html
 */
%option noyywrap

/*
 * Cause the scanner to error (rather than supply an empty default rule)
 * when no match is made.  This is handy for finding hols in our rules.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Debugging-Options.html
 */
%option nodefault

/*
 * Don't include code for the interactive scanner.  We won't use it.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Options-Affecting-Scanner-Behavior.html
 */
%option never-interactive

/*
 * Use a stack to maintain the lexer state.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Scanner-Options.html#Scanner-Options
 */
%option stack

%{

#include "unescape.hpp"

using namespace std;

// yyterminate() is not a function, but a macro.
// The macro does not return the correct type.  It returns an int,
// but we want it to return a string.
// Redefine the yyterminate() macro so that it returns the correct type,
// consistent with our use.
// See yyterminate() in http://web.mit.edu/gnu/doc/html/flex_2.html
#define yyterminate() return ""

%}

%%
  // Include any initialization code here.  These lines *must* be indented,
  // otherwise, flex will try to interpret them as rules rather than code.
  // (Note: there is no code yet, this is just a placeholder)

\" {
  return R"(\")";
}

\n {
  return "\\n";
}

\a {
  return "\\a";
}

\b {
  return "\\b";
}

\f {
  return "\\f";
}

\r {
  return "\\r";
}

\t {
  return "\\t";
}

\v {
  return "\\v";
}

\\ {
  return "\\\\";
}

[a-zA-Z0-9!@#$%\^&\*\\(\)`~\[\]\{\}\|;:',\.<>\? ]+ {
  return yytext;
}

. {
  char buff[] = "\\x00";
  uint8_t ch;

  // Upper 4 bits
  ch = (uint8_t)yytext[0] >> 4;
  buff[2] = ch > 9
    ? 'A' + ch - 10
    : '0' + ch;

  // Lower 4 bits
  ch = (uint8_t)yytext[0] & 15;
  buff[3] = ch > 9
    ? 'A' + ch - 10
    : '0' + ch;

  return buff;
}

<<EOF>> { yyterminate(); }

%%

