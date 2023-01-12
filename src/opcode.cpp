/**
 * @file
 * Define the Tang::Program::dumpBytecode method.
 */

#include <sstream>
#include <iomanip>
#include <bit>
#include <cmath>
#include "program.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

static const char* description[] = {
  "POP",
  "PEEK",
  "POKE",
  "COPY",
  "JMP",
  "JMPF_S",
  "JMPF_I",
  "JMPF_POP",
  "JMPT_S",
  "JMPT_I",
  "JMPT_POP",
  "NULLVAL",
  "INTEGER",
  "FLOAT",
  "BOOLEAN",
  "STRING",
  "ARRAY",
  "MAP",
  "LIBRARY",
  "LIBRARYSAVE",
  "LIBRARYCOPY",
  "FUNCTION",
  "ASSIGNINDEX",
  "ADD_SS",
  "ADD_SI",
  "ADD_IS",
  "ADD_II",
  "SUBTRACT_SS",
  "SUBTRACT_SI",
  "SUBTRACT_IS",
  "SUBTRACT_II",
  "MULTIPLY_SS",
  "MULTIPLY_SI",
  "MULTIPLY_IS",
  "MULTIPLY_II",
  "DIVIDE_SS",
  "DIVIDE_SI",
  "DIVIDE_IS",
  "DIVIDE_II",
  "MODULO_SS",
  "MODULO_SI",
  "MODULO_IS",
  "MODULO_II",
  "NEGATIVE_S",
  "NEGATIVE_I",
  "NOT_S",
  "NOT_I",
  "LT_SS",
  "LT_SI",
  "LT_IS",
  "LT_II",
  "LTE_SS",
  "LTE_SI",
  "LTE_IS",
  "LTE_II",
  "GT_SS",
  "GT_SI",
  "GT_IS",
  "GT_II",
  "GTE_SS",
  "GTE_SI",
  "GTE_IS",
  "GTE_II",
  "EQ_SS",
  "EQ_SI",
  "EQ_IS",
  "EQ_II",
  "NEQ_SS",
  "NEQ_SI",
  "NEQ_IS",
  "NEQ_II",
  "PERIOD",
  "INDEX",
  "SLICE",
  "GETITERATOR",
  "ITERATORNEXT",
  "ISITERATOREND",
  "CASTINTEGER_S",
  "CASTINTEGER_I",
  "CASTFLOAT_S",
  "CASTFLOAT_I",
  "CASTBOOLEAN_S",
  "CASTBOOLEAN_I",
  "CASTSTRING_S",
  "CASTSTRING_I",
  "CALLFUNC",
  "CALLFUNC_I",
  "RETURN",
  "PRINT",
};

ostream & Tang::operator<<(ostream & lhs, const Opcode & rhs) {
  if ((uinteger_t)rhs >= (uinteger_t)sizeof(description)) {
    return lhs << "UNKNOWN";
  }
  return lhs << description[(int)rhs];
}

