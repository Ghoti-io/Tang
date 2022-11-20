/**
 * @file
 * Declare the Opcodes used in the Bytecode representation of a program.
 */

namespace Tang {
  enum class Opcode {
    POP,      ///< Pop a val
    PEEK,     ///< Stack # (from fp): push val from stack #
    POKE,     ///< Stack # (from fp): Copy a val, store @ stack #
    COPY,     ///< Stack # (from fp): Deep copy val @ stack #, store @ stack #
    JMP,      ///< PC #: set pc to PC #
    JMPF,     ///< PC #: read val, if false, set pc to PC #
    JMPF_POP, ///< PC #: pop val, if false, set pc to PC #
    JMPT,     ///< PC #: read val, if true, set pc to PC #
    JMPT_POP, ///< PC #: pop val, if true, set pc to PC #
    NULLVAL,  ///< Push a null onto the stack
    INTEGER,  ///< Push an integer onto the stack
    FLOAT,    ///< Push a floating point number onto the stack
    BOOLEAN,  ///< Push a boolean onto the stack
    STRING,   ///< Get len, char string: push string
    ARRAY,    ///< Get len, pop `len` items, putting them into an array
              ///<   with the last array item popped first
    FUNCTION, ///< Get argc, PC#: push function(argc, PC #)
    ASSIGNINDEX, ///< Pop index, pop collection, pop value,
                 ///<   push (collection[index] = value)
    ADD,      ///< Pop rhs, pop lhs, push lhs + rhs
    SUBTRACT, ///< Pop rhs, pop lhs, push lhs - rhs
    MULTIPLY, ///< Pop rhs, pop lhs, push lhs * rhs
    DIVIDE,   ///< Pop rhs, pop lhs, push lhs / rhs
    MODULO,   ///< Pop rhs, pop lhs, push lhs % rhs
    NEGATIVE, ///< Pop val, push negative val
    NOT,      ///< Pop val, push logical not of val
    LT,       ///< Pop rhs, pop lhs, push lhs < rhs
    LTE,      ///< Pop rhs, pop lhs, push lhs <= rhs
    GT,       ///< Pop rhs, pop lhs, push lhs > rhs
    GTE,      ///< Pop rhs, pop lhs, push lhs >= rhs
    EQ,       ///< Pop rhs, pop lhs, push lhs == rhs
    NEQ,      ///< Pop rhs, pop lhs, push lhs != rhs
    INDEX,    ///< Pop index, pop collection, push collection[index]
    CASTINTEGER, ///< Pop a val, typecast to int, push
    CASTFLOAT,   ///< Pop a val, typecast to float, push
    CASTBOOLEAN, ///< Pop a val, typecast to boolean, push
    CALLFUNC, ///< Get argc, Pop a function, execute function if argc matches.
    RETURN,   ///< Get stack #, pop return val, pop (stack #) times,
              ///< push val, restore fp, restore pc
    PRINT,    ///< Pop val, print(val), push error or NULL
  };
}

