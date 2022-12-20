/**
 * @file
 * Define the Tang::Program::execute method.
 */

#include <bit>
#include <cmath>
#include "program.hpp"
#include "context.hpp"
#include "opcode.hpp"
#include "computedExpressionError.hpp"
#include "computedExpressionInteger.hpp"
#include "computedExpressionFloat.hpp"
#include "computedExpressionBoolean.hpp"
#include "computedExpressionString.hpp"
#include "computedExpressionArray.hpp"
#include "computedExpressionMap.hpp"
#include "computedExpressionCompiledFunction.hpp"
#include "computedExpressionNativeBoundFunction.hpp"
#include "computedExpressionNativeFunction.hpp"
#include "computedExpressionIteratorEnd.hpp"

using namespace std;
using namespace Tang;

/**
 * Verify the size of the Bytecode vector so that it may be safely accessed.
 *
 * @param x The number of additional vector entries that should exist.
 */
#define EXECUTEPROGRAMCHECK(x) \
  if (this->bytecode.size() < (pc + (x))) { \
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Opcode instruction truncated."})); \
    pc = this->bytecode.size(); \
    break; \
  }

/**
 * Verify the size of the stack vector so that it may be safely accessed.
 *
 * @param x The number of entries that should exist in the stack.
 */
#define STACKCHECK(x) \
  if (stack.size() < (fp + (x))) { \
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Insufficient stack depth."})); \
    pc = this->bytecode.size(); \
    break; \
  }

Context Program::execute() {
  Context context{};

  // The program counter of the current instruction.
  size_t pc{0};

  // The frame pointer (an index into the stack frame).
  size_t fp{0};

  // The execution stack.
  vector<GarbageCollected> stack;

  // The stack of program counters used to recover the previous pc when
  // returning from a function.
  vector<size_t> pcStack{};

  // The stack of frame pointers, used to recover the previous fp when
  // returning from a function.
  vector<size_t> fpStack{};

  while (pc < this->bytecode.size()) {
    switch ((Opcode)this->bytecode[pc]) {
      case Opcode::POP: {
        STACKCHECK(1);
        stack.pop_back();
        ++pc;
        break;
      }
      case Opcode::PEEK: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack.push_back(stack[fp + position]);
        pc += 2;
        break;
      }
      case Opcode::POKE: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        stack[fp + position] = stack.back();
        pc += 2;
        break;
      }
      case Opcode::COPY: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[pc + 1];
        STACKCHECK(position);
        auto targetPosition = fp + position;
        if (stack[targetPosition].isCopyNeeded()) {
          stack[targetPosition] = stack[targetPosition].makeCopy();
        }
        pc += 2;
        break;
      }
      case Opcode::JMP: {
        EXECUTEPROGRAMCHECK(1);
        pc = this->bytecode[pc + 1];
        break;
      }
      case Opcode::JMPF: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        if (condition == false) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::JMPF_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        stack.pop_back();
        if (condition == false) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::JMPT: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        if (condition == true) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::JMPT_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = stack.back();
        stack.pop_back();
        if (condition == true) {
          pc = this->bytecode[pc + 1];
        }
        else {
          pc += 2;
        }
        break;
      }
      case Opcode::NULLVAL: {
        stack.push_back(GarbageCollected::make<ComputedExpression>());
        ++pc;
        break;
      }
      case Opcode::INTEGER: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionInteger>((integer_t)this->bytecode[pc + 1]));
        pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionFloat>(bit_cast<float_t>(this->bytecode[pc + 1])));
        pc += 2;
        break;
      }
      case Opcode::BOOLEAN: {
        EXECUTEPROGRAMCHECK(1);
        stack.push_back(GarbageCollected::make<ComputedExpressionBoolean>(this->bytecode[pc + 1] ? true : false));
        pc += 2;
        break;
      }
      case Opcode::STRING: {
        EXECUTEPROGRAMCHECK(2);
        bool isTrusted = this->bytecode[pc + 1];
        auto size = this->bytecode[pc + 2];
        auto bytes = ceil((double)size / sizeof(uinteger_t));
        EXECUTEPROGRAMCHECK(2 + bytes);

        // Extract the letters of the string from the bytecode.
        // TODO make this faster by using a char * buffer.
        string temp{};
        for (size_t i = 0; i < bytes; ++i) {
          for (size_t j = 0; j < sizeof(uinteger_t); ++j) {
            if ((integer_t)((i * sizeof(uinteger_t)) + j) < size) {
              temp += (unsigned char)
                ((this->bytecode[pc + 3 + i] >> (8 * (sizeof(uinteger_t) - 1 - j))) & 0xFF);
            }
          }
        }

        // Finally construct the string object.
        auto gcString = GarbageCollected::make<ComputedExpressionString>(temp);

        // Set the string as Untrusted if necessary.
        if (!isTrusted) {
          auto & s = static_cast<ComputedExpressionString &>(*gcString);
          s.setUntrusted();
        }

        stack.push_back(gcString);
        pc += bytes + 3;
        break;
      }
      case Opcode::ARRAY: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[pc + 1];
        STACKCHECK(size);
        vector<GarbageCollected> contents;
        contents.reserve(size);
        for (uinteger_t i = 0; i < size; ++i) {
          contents.push_back(stack[stack.size() - size + i]);
        }
        for (uinteger_t i = 0; i < size; ++i) {
          stack.pop_back();
        }
        stack.push_back(GarbageCollected::make<ComputedExpressionArray>(contents));
        pc += 2;
        break;
      }
      case Opcode::MAP: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[pc + 1];
        STACKCHECK(size * 2);
        map<string, GarbageCollected> contents;
        for (uinteger_t i = 0; i < size; ++i) {
          auto value = stack.back();
          stack.pop_back();
          auto key = stack.back();
          stack.pop_back();
          if (typeid(*key) == typeid(ComputedExpressionString)) {
            contents.insert({static_cast<ComputedExpressionString &>(*key).dump(), value});
          }
        }
        stack.push_back(GarbageCollected::make<ComputedExpressionMap>(contents));
        pc += 2;
        break;
      }
      case Opcode::FUNCTION: {
        EXECUTEPROGRAMCHECK(2);
        auto argc = this->bytecode[pc + 1];
        auto targetPc = this->bytecode[pc + 2];
        stack.push_back(GarbageCollected::make<ComputedExpressionCompiledFunction>((uint32_t)argc, targetPc));
        pc += 3;
        break;
      }
      case Opcode::ASSIGNINDEX: {
        STACKCHECK(3);
        auto index = stack.back();
        stack.pop_back();
        auto collection = stack.back();
        stack.pop_back();
        auto value = stack.back();
        stack.pop_back();
        stack.push_back(collection->__assign_index(index, value));
        ++pc;
        break;
      }
      case Opcode::ADD: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs + rhs);
        ++pc;
        break;
      }
      case Opcode::SUBTRACT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs - rhs);
        ++pc;
        break;
      }
      case Opcode::MULTIPLY: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs * rhs);
        ++pc;
        break;
      }
      case Opcode::DIVIDE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs / rhs);
        ++pc;
        break;
      }
      case Opcode::MODULO: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs % rhs);
        ++pc;
        break;
      }
      case Opcode::NEGATIVE: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(-operand);
        ++pc;
        break;
      }
      case Opcode::NOT: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(!operand);
        ++pc;
        break;
      }
      case Opcode::LT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs < rhs);
        ++pc;
        break;
      }
      case Opcode::LTE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs <= rhs);
        ++pc;
        break;
      }
      case Opcode::GT: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs > rhs);
        ++pc;
        break;
      }
      case Opcode::GTE: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs >= rhs);
        ++pc;
        break;
      }
      case Opcode::EQ: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs == rhs);
        ++pc;
        break;
      }
      case Opcode::NEQ: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        stack.push_back(lhs != rhs);
        ++pc;
        break;
      }
      case Opcode::PERIOD: {
        STACKCHECK(2);
        auto rhs = stack.back();
        stack.pop_back();
        auto lhs = stack.back();
        stack.pop_back();
        auto tmp = lhs->__period(rhs, this->tang);
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }
        stack.push_back(tmp);
        ++pc;
        break;
      }
      case Opcode::INDEX: {
        STACKCHECK(2);
        auto index = stack.back();
        stack.pop_back();
        auto container = stack.back();
        stack.pop_back();
        stack.push_back(container->__index(index));
        ++pc;
        break;
      }
      case Opcode::SLICE: {
        STACKCHECK(4);
        auto skip = stack.back();
        stack.pop_back();
        auto end = stack.back();
        stack.pop_back();
        auto begin = stack.back();
        stack.pop_back();
        auto container = stack.back();
        stack.pop_back();
        stack.push_back(container->__slice(begin, end, skip));
        ++pc;
        break;
      }
      case Opcode::GETITERATOR: {
        STACKCHECK(1);
        auto collection = stack.back();
        stack.pop_back();
        stack.push_back(collection->__getIterator(collection));
        ++pc;
        break;
      }
      case Opcode::ITERATORNEXT: {
        STACKCHECK(1);
        auto iterator = stack.back();
        stack.pop_back();
        stack.push_back(iterator->__iteratorNext());
        ++pc;
        break;
      }
      case Opcode::ISITERATOREND: {
        STACKCHECK(1);
        auto val = stack.back();
        stack.pop_back();
        stack.push_back(GarbageCollected::make<ComputedExpressionBoolean>((typeid(*val) == typeid(ComputedExpressionIteratorEnd)) || (typeid(*val) == typeid(ComputedExpressionError))));
        ++pc;
        break;
      }
      case Opcode::CASTINTEGER: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__integer());
        ++pc;
        break;
      }
      case Opcode::CASTFLOAT: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__float());
        ++pc;
        break;
      }
      case Opcode::CASTBOOLEAN: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__boolean());
        ++pc;
        break;
      }
      case Opcode::CASTSTRING: {
        STACKCHECK(1);
        auto operand = stack.back();
        stack.pop_back();
        stack.push_back(operand->__string());
        ++pc;
        break;
      }
      case Opcode::CALLFUNC: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto function = stack.back();
        stack.pop_back();
        auto argc = this->bytecode[pc + 1];
        STACKCHECK(argc);

        // Compiled functions make use of the arguments on the stack.
        // They will clean up the stack when they finish, via the RETURN
        // opcode.
        if (typeid(*function) == typeid(ComputedExpressionCompiledFunction)) {
          auto & funcConv = static_cast<ComputedExpressionCompiledFunction &>(*function);

          // Verify that the correct number of arguments has been passed.
          if (argc != (int)funcConv.getArgc()) {
            // Incorrect number of arguments passed.
            // Clear the arguments from the stack.
            for (uinteger_t i = 0; i < argc; ++i) {
              stack.pop_back();
            }

            // Push an error onto the stack.
            stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments supplied at function call."}));

            pc += 2;
            break;
          }

          // Save the current execution environment so that it can be restored
          // when RETURNing from the function.
          pcStack.push_back(pc + 2);
          fpStack.push_back(fp);

          // Set the new pc and fp.
          pc = funcConv.getPc();
          fp = stack.size() - argc;

          break;
        }

        // Compiled functions make use of the arguments on the stack.
        // They will clean up the stack when they finish, via the RETURN
        // opcode.
        if (typeid(*function) == typeid(ComputedExpressionNativeBoundFunction)) {
          auto & funcConv = static_cast<ComputedExpressionNativeBoundFunction &>(*function);

          // Populate argv to use when calling the function.
          vector<GarbageCollected> argv{};
          argv.reserve(argc);
          auto iter = stack.end() - argc;
          while (iter != stack.end()) {
            argv.push_back(*iter);
            ++iter;
          }

          // Remove the arguments from the stack.
          for (int i = 0; i < argc; ++i) {
            stack.pop_back();
          }

          // Verify that the number of arguments supplied matches the number
          // of arguments expected.
          if ((size_t)argc != funcConv.getArgc()) {
            stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));

            pc += 2;
            break;
          }

          // Make sure that there is an object that was bound to the function.
          if (funcConv.target) {
            // Verify that the target is the correct type.
            // It is impossible for the target to not be the correct type under
            // normal circumstances.  This is just a safety check.
            if (type_index(typeid(**funcConv.target)) != funcConv.getTargetTypeIndex()) {
              stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Type mismatch of object method to its target object."}));
            }
            else {
              stack.push_back(funcConv.getFunction()(*funcConv.target, argv));
            }

            pc += 2;
            break;
          }

          // There is no function target.  This is impossible under normal
          // circumstances, but we must account for it, just in case.
          stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Method is not bound to any object."}));
          pc += 2;
          break;
        }

        // Compiled functions make use of the arguments on the stack.
        // They will clean up the stack when they finish, via the RETURN
        // opcode.
        if (typeid(*function) == typeid(ComputedExpressionNativeFunction)) {
          auto & funcConv = static_cast<ComputedExpressionNativeFunction &>(*function);

          // Populate argv to use when calling the function.
          vector<GarbageCollected> argv{};
          argv.reserve(argc);
          auto iter = stack.end() - argc;
          while (iter != stack.end()) {
            argv.push_back(*iter);
            ++iter;
          }

          // Remove the arguments from the stack.
          for (int i = 0; i < argc; ++i) {
            stack.pop_back();
          }

          // Verify that the number of arguments supplied matches the number
          // of arguments expected.
          if ((size_t)argc != funcConv.getArgc()) {
            stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));

            pc += 2;
            break;
          }

          // Call the Native function.
          stack.push_back(funcConv.getFunction()(argv, context));

          pc += 2;
          break;
        }

        // Error: We don't know what to do.
        // Clear the arguments from the stack.
        for (uinteger_t i = 0; i < argc; ++i) {
          stack.pop_back();
        }

        stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Function call on unrecognized type."}));
        pc = this->bytecode.size();
        break;
      }
      case Opcode::RETURN: {
        EXECUTEPROGRAMCHECK(1);
        size_t pop = this->bytecode[pc + 1];
        STACKCHECK(pop + 1);

        // Save the top of the stack as the return value.
        auto returnVal = stack.back();

        // Remove the stack down to the fp.
        for (size_t i = 0; i <= pop; ++i) {
          stack.pop_back();
        }

        // Put the return value back on the stack.
        stack.push_back(returnVal);

        // Restore the pc and fp.
        pc = pcStack.back();
        fp = fpStack.back();
        pcStack.pop_back();
        fpStack.pop_back();
        break;
      }
      case Opcode::PRINT: {
        STACKCHECK(1);
        auto expression = stack.back();
        stack.pop_back();
        // Try to convert the expression to a string.
        auto result = expression->__string();
        if (typeid(*result) == typeid(ComputedExpressionString)) {
          // We know that both our private member and `result` are a
          // ComputedExpressionString, so combine them here.
          static_cast<ComputedExpressionString &>(*context.computedExpressionOut) += static_cast<ComputedExpressionString &>(*result);
          // Push an empty value onto the stack.
          stack.push_back(GarbageCollected::make<ComputedExpression>());
        }
        else if (typeid(*result) != typeid(ComputedExpressionError)) {
          // __string returned neither a string nor an error, so report that.
          stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Argument not recognized as a string or error type."}));
        }
        else {
          // __string returned an error, pass that back to the stack.
          stack.push_back(result);
        }
        ++pc;
        break;
      }
      default: {
        // We should never reach this.
        stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Unrecognized Opcode."}));
        pc = stack.size();
        break;
      }
    }
  }

  // Verify that there is at least one value on the stack.  If not, set a
  // runtime error.
  if (!stack.size()) {
    stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Stack is empty."}));
  }

  // Empty the stack, but save the top of the stack.
  context.result = stack.back();
  stack.clear();

  // Render the output to `out`.
  context.out = context.computedExpressionOut->dump();

  return context;
}

