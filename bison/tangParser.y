// Declarations can be found here:
// https://www.gnu.org/software/bison/manual/html_node/Decl-Summary.html
// Defines can be found here:
// https://www.gnu.org/software/bison/manual/html_node/_0025define-Summary.html

// Minimum version requirement.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025require
%require "3.8.2"

// Use a C++ skeleton.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025skeleton
%skeleton "lalr1.cc"

// Create a .h file with the proper definitions for the lexer.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025defines-2
%defines

// Choose the namespace to hold the generated code to avoid conflicts.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002enamespace
%define api.namespace { Tang }

// Choose the name of the parser that will be generated.  (e.g., "Parser")
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002eparser_002eclass-1
%define api.parser.class { TangParser }

// Use variant-based values instead of the old union syntax.  Only available
// in C++, but it allows us to use objects without pointer workarounds.
// https://www.gnu.org/software/bison/manual/html_node/C_002b_002b-Variants.html
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002evalue_002etype-1
%define api.value.type variant

// In combination with "%defines", the type "symbol_type" will be defined
// and used when appropriate as the return type of yylex().  In short, it
// consolidates the information returned by the lexer, which makes our job
// easier.  This option should be used when using "api.value.type variant".
// https://www.gnu.org/software/bison/manual/html_node/Complete-Symbols.html#Complete-Symbols
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-api_002etoken_002econstructor
%define api.token.constructor

// Use runtime assertions to verify that variant objects are constructed and
// destroyed properly.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002eassert
%define parse.assert

// Define the YYDEBUG macro so that debugging facilities are compiled.
// https://www.gnu.org/software/bison/manual/bison.html#Tracing
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002etrace
%define parse.trace

// Provide a more helpful error message.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025define-parse_002eerror-verbose
%define parse.error verbose

// Add a locations class to track the parsing location, so that we can generate
// more helpful error messages.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025locations
%locations

// Additional arguments that yylex() should accept.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025lex_002dparam-3
%lex-param { Tang::TangScanner & scanner }

// Additional arguments that yyparse() should accept.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025parse_002dparam-3
%parse-param { Tang::TangScanner & scanner }
%parse-param { Tang::AstNode * & ast }
%parse-param { Tang::Error * & parseError }

// Add a prefix to token names
// %define api.token.prefix {TOKEN_}
// Because the prefix will be added to a suffix, do not include any whitespace
// between the prefix and the closing '}'
%define api.token.prefix {TANG_PARSER_}

// Declare tokens (as opposed to the old, %union approach.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025token
%token EOF 0 "end of code"
%token < int64_t > INTEGER "integer"
%token < long double > FLOAT "float"
%token PLUS "+"
%token MINUS "-"

// Any %type declarations of non-terminals.
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025type
%type < Tang::AstNode * > program
%type < Tang::AstNode * > expression

// Precedence rules.
// For guidance, see:
// https://efxa.org/2014/05/17/techniques-for-resolving-common-grammar-conflicts-in-parsers/
// Notice that the order is reversed from:
// https://en.cppreference.com/w/cpp/language/operator_precedence
// Here, rules are in order of lowest to highest precedence.
%left "+" "-"
%right UMINUS

// Code sections.
// https://www.gnu.org/software/bison/manual/bison.html#g_t_0025code-Summary
// `requires` will be included in the .hpp file.
%code requires {
#include <stdint.h>
#include "astNode.hpp"
#include "error.hpp"
namespace Tang {
  class TangScanner;
}
}

// `top` will be included at the top of the .cpp file, but not in .hpp.
%code top {
#include "tangScanner.hpp"
#include "tangParser.hpp"
#include "location.hh"
#include "astNodeAdd.hpp"
#include "astNodeSubtract.hpp"
#include "astNodeFloat.hpp"
#include "astNodeInteger.hpp"
#include "astNodeNegative.hpp"

// We must provide the yylex() function.
// yylex() arguments are defined in the bison .y file.
// It is conceivable that a programmer may want to have multiple compilers in
// the same project.  Each compiler will need its own yylex() function.
// Because yylex() is only defined and used in this file, we can set its
// linkage as "internal", by declaring the function "static", which allows
// each compiler's yylex() to not interfere with that of another linked file.
// https://en.cppreference.com/w/cpp/language/storage_duration

static Tang::TangParser::symbol_type yylex(Tang::TangScanner & scanner) {
  return scanner.get_next_token();
}
}


// The grammar start symbol (non-terminal).
// https://www.gnu.org/software/bison/manual/bison.html#index-_0025start
%start program


%%
// Grammar Section.
// https://efxa.org/2014/05/17/techniques-for-resolving-common-grammar-conflicts-in-parsers/
// https://stackoverflow.com/a/12732388/3821565

// `program` represents every possible syntactically-valid program.
program
  : expression
    {
      ast = $1;
    }
  | EOF
    {}
  ;

// `expression` represents a computable value.
expression
  : INTEGER
    {
      $$ = new Tang::AstNodeInteger($1, @1);
    }
  | FLOAT
    {
      $$ = new Tang::AstNodeFloat($1, @1);
    }
  | expression "+" expression
    {
      $$ = new Tang::AstNodeAdd($1, $3, @2);
    }
  | expression "-" expression
    {
      $$ = new Tang::AstNodeSubtract($1, $3, @2);
    }
  | "-" expression %prec UMINUS
    {
      $$ = new Tang::AstNodeNegative($2, @1);
    }
  ;

%%

// An error-handler must be defined.  See the end of the following section:
// https://www.gnu.org/software/bison/manual/bison.html#A-Simple-C_002b_002b-Example
void Tang::TangParser::error(const location & location, const std::string & message) {
  parseError = new Error{message, location};
}

