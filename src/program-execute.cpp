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
  if (this->bytecode.size() < (context.pc + (x))) { \
    context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Opcode instruction truncated."})); \
    context.pc = this->bytecode.size(); \
    break; \
  }

/**
 * Verify the size of the context.stack vector so that it may be safely accessed.
 *
 * @param x The number of entries that should exist in the context.stack.
 */
#define STACKCHECK(x) \
  if (context.stack.size() < (context.fp + (x))) { \
    context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Insufficient context.stack depth."})); \
    context.pc = this->bytecode.size(); \
    break; \
  }

Context Program::execute() {
  Context context{};

  while (context.pc < this->bytecode.size()) {
    switch ((Opcode)this->bytecode[context.pc]) {
      case Opcode::POP: {
        STACKCHECK(1);
        context.stack.pop_back();
        ++context.pc;
        break;
      }
      case Opcode::PEEK: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[context.pc + 1];
        STACKCHECK(position);
        context.stack.push_back(context.stack[context.fp + position]);
        context.pc += 2;
        break;
      }
      case Opcode::POKE: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[context.pc + 1];
        STACKCHECK(position);
        context.stack[context.fp + position] = context.stack.back();
        context.pc += 2;
        break;
      }
      case Opcode::COPY: {
        EXECUTEPROGRAMCHECK(1);
        auto position = this->bytecode[context.pc + 1];
        STACKCHECK(position);
        auto targetPosition = context.fp + position;
        if (context.stack[targetPosition].isCopyNeeded()) {
          context.stack[targetPosition] = context.stack[targetPosition].makeCopy();
        }
        context.pc += 2;
        break;
      }
      case Opcode::JMP: {
        EXECUTEPROGRAMCHECK(1);
        context.pc = this->bytecode[context.pc + 1];
        break;
      }
      case Opcode::JMPF: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = context.stack.back();
        if (condition == false) {
          context.pc = this->bytecode[context.pc + 1];
        }
        else {
          context.pc += 2;
        }
        break;
      }
      case Opcode::JMPF_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = context.stack.back();
        context.stack.pop_back();
        if (condition == false) {
          context.pc = this->bytecode[context.pc + 1];
        }
        else {
          context.pc += 2;
        }
        break;
      }
      case Opcode::JMPT: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = context.stack.back();
        if (condition == true) {
          context.pc = this->bytecode[context.pc + 1];
        }
        else {
          context.pc += 2;
        }
        break;
      }
      case Opcode::JMPT_POP: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto condition = context.stack.back();
        context.stack.pop_back();
        if (condition == true) {
          context.pc = this->bytecode[context.pc + 1];
        }
        else {
          context.pc += 2;
        }
        break;
      }
      case Opcode::NULLVAL: {
        context.stack.push_back(GarbageCollected::make<ComputedExpression>());
        ++context.pc;
        break;
      }
      case Opcode::INTEGER: {
        EXECUTEPROGRAMCHECK(1);
        context.stack.push_back(GarbageCollected::make<ComputedExpressionInteger>((integer_t)this->bytecode[context.pc + 1]));
        context.pc += 2;
        break;
      }
      case Opcode::FLOAT: {
        EXECUTEPROGRAMCHECK(1);
        context.stack.push_back(GarbageCollected::make<ComputedExpressionFloat>(bit_cast<float_t>(this->bytecode[context.pc + 1])));
        context.pc += 2;
        break;
      }
      case Opcode::BOOLEAN: {
        EXECUTEPROGRAMCHECK(1);
        context.stack.push_back(GarbageCollected::make<ComputedExpressionBoolean>(this->bytecode[context.pc + 1] ? true : false));
        context.pc += 2;
        break;
      }
      case Opcode::STRING: {
        EXECUTEPROGRAMCHECK(2);
        bool isTrusted = this->bytecode[context.pc + 1];
        auto size = this->bytecode[context.pc + 2];
        auto bytes = ceil((double)size / sizeof(uinteger_t));
        EXECUTEPROGRAMCHECK(2 + bytes);

        // Extract the letters of the string from the bytecode.
        // TODO make this faster by using a char * buffer.
        string temp{};
        for (size_t i = 0; i < bytes; ++i) {
          for (size_t j = 0; j < sizeof(uinteger_t); ++j) {
            if ((integer_t)((i * sizeof(uinteger_t)) + j) < size) {
              temp += (unsigned char)
                ((this->bytecode[context.pc + 3 + i] >> (8 * (sizeof(uinteger_t) - 1 - j))) & 0xFF);
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

        context.stack.push_back(gcString);
        context.pc += bytes + 3;
        break;
      }
      case Opcode::ARRAY: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[context.pc + 1];
        STACKCHECK(size);
        vector<GarbageCollected> contents;
        contents.reserve(size);
        for (uinteger_t i = 0; i < size; ++i) {
          contents.push_back(context.stack[context.stack.size() - size + i]);
        }
        for (uinteger_t i = 0; i < size; ++i) {
          context.stack.pop_back();
        }
        context.stack.push_back(GarbageCollected::make<ComputedExpressionArray>(contents));
        context.pc += 2;
        break;
      }
      case Opcode::MAP: {
        EXECUTEPROGRAMCHECK(1);
        auto size = this->bytecode[context.pc + 1];
        STACKCHECK(size * 2);
        map<string, GarbageCollected> contents;
        for (uinteger_t i = 0; i < size; ++i) {
          auto value = context.stack.back();
          context.stack.pop_back();
          auto key = context.stack.back();
          context.stack.pop_back();
          if (typeid(*key) == typeid(ComputedExpressionString)) {
            contents.insert({static_cast<ComputedExpressionString &>(*key).dump(), value});
          }
        }
        context.stack.push_back(GarbageCollected::make<ComputedExpressionMap>(contents));
        context.pc += 2;
        break;
      }
      case Opcode::FUNCTION: {
        EXECUTEPROGRAMCHECK(2);
        auto argc = this->bytecode[context.pc + 1];
        auto targetPc = this->bytecode[context.pc + 2];
        context.stack.push_back(GarbageCollected::make<ComputedExpressionCompiledFunction>((uint32_t)argc, targetPc));
        context.pc += 3;
        break;
      }
      case Opcode::ASSIGNINDEX: {
        STACKCHECK(3);
        auto index = context.stack.back();
        context.stack.pop_back();
        auto collection = context.stack.back();
        context.stack.pop_back();
        auto value = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(collection->__assign_index(index, value));
        ++context.pc;
        break;
      }
      case Opcode::ADD: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs + rhs);
        ++context.pc;
        break;
      }
      case Opcode::SUBTRACT: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs - rhs);
        ++context.pc;
        break;
      }
      case Opcode::MULTIPLY: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs * rhs);
        ++context.pc;
        break;
      }
      case Opcode::DIVIDE: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs / rhs);
        ++context.pc;
        break;
      }
      case Opcode::MODULO: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs % rhs);
        ++context.pc;
        break;
      }
      case Opcode::NEGATIVE: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(-operand);
        ++context.pc;
        break;
      }
      case Opcode::NOT: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(!operand);
        ++context.pc;
        break;
      }
      case Opcode::LT: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs < rhs);
        ++context.pc;
        break;
      }
      case Opcode::LTE: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs <= rhs);
        ++context.pc;
        break;
      }
      case Opcode::GT: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs > rhs);
        ++context.pc;
        break;
      }
      case Opcode::GTE: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs >= rhs);
        ++context.pc;
        break;
      }
      case Opcode::EQ: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs == rhs);
        ++context.pc;
        break;
      }
      case Opcode::NEQ: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(lhs != rhs);
        ++context.pc;
        break;
      }
      case Opcode::PERIOD: {
        STACKCHECK(2);
        auto rhs = context.stack.back();
        context.stack.pop_back();
        auto lhs = context.stack.back();
        context.stack.pop_back();
        auto tmp = lhs->__period(rhs, this->tang);
        if (typeid(*tmp) == typeid(ComputedExpressionNativeBoundFunction)) {
          static_cast<ComputedExpressionNativeBoundFunction &>(*tmp).target = lhs;
        }
        context.stack.push_back(tmp);
        ++context.pc;
        break;
      }
      case Opcode::INDEX: {
        STACKCHECK(2);
        auto index = context.stack.back();
        context.stack.pop_back();
        auto container = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(container->__index(index));
        ++context.pc;
        break;
      }
      case Opcode::SLICE: {
        STACKCHECK(4);
        auto skip = context.stack.back();
        context.stack.pop_back();
        auto end = context.stack.back();
        context.stack.pop_back();
        auto begin = context.stack.back();
        context.stack.pop_back();
        auto container = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(container->__slice(begin, end, skip));
        ++context.pc;
        break;
      }
      case Opcode::GETITERATOR: {
        STACKCHECK(1);
        auto collection = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(collection->__getIterator(collection));
        ++context.pc;
        break;
      }
      case Opcode::ITERATORNEXT: {
        STACKCHECK(1);
        auto iterator = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(iterator->__iteratorNext());
        ++context.pc;
        break;
      }
      case Opcode::ISITERATOREND: {
        STACKCHECK(1);
        auto val = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(GarbageCollected::make<ComputedExpressionBoolean>((typeid(*val) == typeid(ComputedExpressionIteratorEnd)) || (typeid(*val) == typeid(ComputedExpressionError))));
        ++context.pc;
        break;
      }
      case Opcode::CASTINTEGER: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(operand->__integer());
        ++context.pc;
        break;
      }
      case Opcode::CASTFLOAT: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(operand->__float());
        ++context.pc;
        break;
      }
      case Opcode::CASTBOOLEAN: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(operand->__boolean());
        ++context.pc;
        break;
      }
      case Opcode::CASTSTRING: {
        STACKCHECK(1);
        auto operand = context.stack.back();
        context.stack.pop_back();
        context.stack.push_back(operand->__string());
        ++context.pc;
        break;
      }
      case Opcode::CALLFUNC: {
        EXECUTEPROGRAMCHECK(1);
        STACKCHECK(1);
        auto function = context.stack.back();
        context.stack.pop_back();
        auto argc = this->bytecode[context.pc + 1];
        STACKCHECK(argc);

        // Compiled functions make use of the arguments on the context.stack.
        // They will clean up the context.stack when they finish, via the RETURN
        // ocontext.pcode.
        if (typeid(*function) == typeid(ComputedExpressionCompiledFunction)) {
          auto & funcConv = static_cast<ComputedExpressionCompiledFunction &>(*function);

          // Verify that the correct number of arguments has been passed.
          if (argc != (int)funcConv.getArgc()) {
            // Incorrect number of arguments passed.
            // Clear the arguments from the context.stack.
            for (uinteger_t i = 0; i < argc; ++i) {
              context.stack.pop_back();
            }

            // Push an error onto the context.stack.
            context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments supplied at function call."}));

            context.pc += 2;
            break;
          }

          // Save the current execution environment so that it can be restored
          // when RETURNing from the function.
          context.pcStack.push_back(context.pc + 2);
          context.fpStack.push_back(context.fp);

          // Set the new context.pc and context.fp.
          context.pc = funcConv.getPc();
          context.fp = context.stack.size() - argc;

          break;
        }

        // Compiled functions make use of the arguments on the context.stack.
        // They will clean up the context.stack when they finish, via the RETURN
        // ocontext.pcode.
        if (typeid(*function) == typeid(ComputedExpressionNativeBoundFunction)) {
          auto & funcConv = static_cast<ComputedExpressionNativeBoundFunction &>(*function);

          // Populate argv to use when calling the function.
          vector<GarbageCollected> argv{};
          argv.reserve(argc);
          auto iter = context.stack.end() - argc;
          while (iter != context.stack.end()) {
            argv.push_back(*iter);
            ++iter;
          }

          // Remove the arguments from the context.stack.
          for (int i = 0; i < argc; ++i) {
            context.stack.pop_back();
          }

          // Verify that the number of arguments supplied matches the number
          // of arguments expected.
          if ((size_t)argc != funcConv.getArgc()) {
            context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));

            context.pc += 2;
            break;
          }

          // Make sure that there is an object that was bound to the function.
          if (funcConv.target) {
            // Verify that the target is the correct type.
            // It is impossible for the target to not be the correct type under
            // normal circumstances.  This is just a safety check.
            if (type_index(typeid(**funcConv.target)) != funcConv.getTargetTypeIndex()) {
              context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Type mismatch of object method to its target object."}));
            }
            else {
              context.stack.push_back(funcConv.getFunction()(*funcConv.target, argv));
            }

            context.pc += 2;
            break;
          }

          // There is no function target.  This is impossible under normal
          // circumstances, but we must account for it, just in case.
          context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Method is not bound to any object."}));
          context.pc += 2;
          break;
        }

        // Compiled functions make use of the arguments on the context.stack.
        // They will clean up the context.stack when they finish, via the RETURN
        // ocontext.pcode.
        if (typeid(*function) == typeid(ComputedExpressionNativeFunction)) {
          auto & funcConv = static_cast<ComputedExpressionNativeFunction &>(*function);

          // Populate argv to use when calling the function.
          vector<GarbageCollected> argv{};
          argv.reserve(argc);
          auto iter = context.stack.end() - argc;
          while (iter != context.stack.end()) {
            argv.push_back(*iter);
            ++iter;
          }

          // Remove the arguments from the context.stack.
          for (int i = 0; i < argc; ++i) {
            context.stack.pop_back();
          }

          // Verify that the number of arguments supplied matches the number
          // of arguments expected.
          if ((size_t)argc != funcConv.getArgc()) {
            context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Incorrect number of arguments provided to object method."}));

            context.pc += 2;
            break;
          }

          // Call the Native function.
          context.stack.push_back(funcConv.getFunction()(argv, context));

          context.pc += 2;
          break;
        }

        // Error: We don't know what to do.
        // Clear the arguments from the context.stack.
        for (uinteger_t i = 0; i < argc; ++i) {
          context.stack.pop_back();
        }

        context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Function call on unrecognized type."}));
        context.pc = this->bytecode.size();
        break;
      }
      case Opcode::RETURN: {
        EXECUTEPROGRAMCHECK(1);
        size_t pop = this->bytecode[context.pc + 1];
        STACKCHECK(pop + 1);

        // Save the top of the context.stack as the return value.
        auto returnVal = context.stack.back();

        // Remove the context.stack down to the context.fp.
        for (size_t i = 0; i <= pop; ++i) {
          context.stack.pop_back();
        }

        // Put the return value back on the context.stack.
        context.stack.push_back(returnVal);

        // Restore the context.pc and context.fp.
        context.pc = context.pcStack.back();
        context.fp = context.fpStack.back();
        context.pcStack.pop_back();
        context.fpStack.pop_back();
        break;
      }
      case Opcode::PRINT: {
        STACKCHECK(1);
        auto expression = context.stack.back();
        context.stack.pop_back();
        // Try to convert the expression to a string.
        auto result = expression->__string();
        if (typeid(*result) == typeid(ComputedExpressionString)) {
          // We know that both our private member and `result` are a
          // ComputedExpressionString, so combine them here.
          static_cast<ComputedExpressionString &>(*context.computedExpressionOut) += static_cast<ComputedExpressionString &>(*result);
          // Push an empty value onto the context.stack.
          context.stack.push_back(GarbageCollected::make<ComputedExpression>());
        }
        else if (typeid(*result) != typeid(ComputedExpressionError)) {
          // __string returned neither a string nor an error, so report that.
          context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Argument not recognized as a string or error type."}));
        }
        else {
          // __string returned an error, pass that back to the context.stack.
          context.stack.push_back(result);
        }
        ++context.pc;
        break;
      }
      default: {
        // We should never reach this.
        context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Unrecognized Opcode."}));
        context.pc = context.stack.size();
        break;
      }
    }
  }

  // Verify that there is at least one value on the context.stack.  If not, set a
  // runtime error.
  if (!context.stack.size()) {
    context.stack.push_back(GarbageCollected::make<ComputedExpressionError>(Error{"Stack is empty."}));
  }

  // Empty the context.stack, but save the top of the context.stack.
  context.result = context.stack.back();
  context.stack.clear();

  // Render the output to `out`.
  context.out = context.computedExpressionOut->dump();

  return context;
}

