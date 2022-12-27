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
%option yyclass="PercentEncodeFlexLexer"

/*
 * Use "TangTang" as a name prefix rather than "yy".  In C++, this only applies to
 * yywrap (addressed in the next option) and yyFlexLexer.
 * https://www.cs.virginia.edu/~cr4bd/flex-manual/Code_002dLevel-And-API-Options.html
 */
%option prefix="TangPercentEncode"

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

#include "percentEncode.hpp"

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

[A-Za-z0-9\-_\.~]+ {
  // Unreserved Characters pass through unaltered.
  return yytext;
}

" " {
  // Space (" ") becomes a plus ("+").
  return "+";
}

.|\n {
  // Every other character needs to be percent encoded.
  char buff[4]{0};
  snprintf(buff, sizeof(buff), "%%%02X", *(uint8_t *)yytext);
  return buff;
}

<<EOF>> { yyterminate(); }

%%

