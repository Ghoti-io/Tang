/**
 * @file
 * Define the Tang::Program::optimize method.
 */

#include <set>
#include "program.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

static set<Opcode> jumpOpcodes_S{
  Opcode::JMP,
  Opcode::JMPF_S,
  Opcode::JMPF_POP,
  Opcode::JMPT_S,
  Opcode::JMPT_POP,
};

static set<Opcode> jumpOpcodes_I{
  Opcode::JMPF_I,
  Opcode::JMPT_I,
};

static set<Opcode> valueProducingOpcodes{
  Opcode::NULLVAL,
  Opcode::INTEGER,
  Opcode::FLOAT,
  Opcode::BOOLEAN,
  Opcode::STRING,
  Opcode::FUNCTION,
};

/**
 * Remove Opcodes and their associated data from the Bytecode array and the
 * accompanying metadata arrays.
 *
 * @param bytecode The bytecode to be altered.
 * @param position The Opcode position of the Opcode to be removed.  This is
 *   not the Bytecode offset.
 * @param count The total number of Opcodes to be removed.
 * @param opOffsets OpcodeOffsets metadata of the Bytecode array.
 * @param ops OpcodePositions metadata of the Bytecode array.
 * @param annotations The OpcodeAnnotations associated with the Bytecode.
 */
static void removeOpcodes(Bytecode & bytecode, size_t position, size_t count, OpcodeOffsets & opOffsets, OpcodePositions & ops, OpcodeAnnotations & annotations) {
  // Sanity check to make sure that `position` is within the scope of 
  // available Opcode positions.
  if ((ops.size() <= position) || (count < 1)) {
    return;
  }

  // Determine the Bytecode locations affected.
  auto originalBytecodeSize = bytecode.size();
  auto bytecodeStart = ops[position].second;
  auto bytecodeExclusiveEnd = (position + count >= ops.size())
    ? bytecode.size()
    : ops[position + count].second;
  auto bytecodeDeletedCount = bytecodeExclusiveEnd - bytecodeStart;

  // Delete the opcodes from the Bytecode array.
  bytecode.erase(bytecode.begin() + bytecodeStart, bytecode.begin() + bytecodeExclusiveEnd);

  // Fix the Bytecode (and Opcode) metadata.

  // 1. Update Opcodes in OpcodePositions *after* the deleted section.
  for (size_t i{position + count}; i < ops.size(); ++i) {
    ops[i].second -= bytecodeDeletedCount;
  }

  // 2. Remove Opcodes from OpcodePositions.
  ops.erase(ops.begin() + position, ops.begin() + position + count);

  for (auto & [op, offsets] : opOffsets) {
    for (auto it = offsets.rbegin(); it != offsets.rend(); ++it) {
      auto & [boffset, ooffset] = *it;
      if (boffset >= bytecodeExclusiveEnd) {
        // Update Opcodes *after* the deleted section in OpcodeOffsets.
        boffset -= bytecodeDeletedCount;
        ooffset -= count;
      }
      else if (boffset < bytecodeStart) {
        // We are now *before* any deleted sections, so do nothing.
        it = offsets.rend() - 1;
      }
      else {
        // Remove "deleted" Opcode entries from OpcodeOffsets.
        // Get the reverseIndex #
        auto reverseIndex = it - offsets.rbegin();
        offsets.erase((it + 1).base());
        // Recalculate the reverse index.
        // TODO: Verify whether or not this is necessary.  When a vector
        // erases elements, does that invalidate the existing iterators?
        // If so, then our recalculation is necessary.
        it = offsets.rbegin() + (reverseIndex - 1);
      }
    }
    if (jumpOpcodes_S.count(op)) {
      // 3a. Update any Jump targets that may have been affected.
      // We did not do this earlier because the first loop exited early to save
      // processing time.
      // For this loop, however, we must examine every jump target and adjust
      // it as needed, and we cannot assume that the jump instructions are in
      // any particular order.
      for (auto & [boffset, ooffset] : offsets) {
        uinteger_t target = bytecode[boffset + 1];
        if (target >= bytecodeExclusiveEnd) {
          bytecode[boffset + 1] = target - bytecodeDeletedCount;
        }
        else if (target >= bytecodeStart) {
          // Target was jumping to an opcode that is now deleted.
          bytecode[boffset + 1] = bytecodeStart;
        }
      }
    }
    if (jumpOpcodes_I.count(op)) {
      // 3a. Update any Jump targets that may have been affected.
      // We did not do this earlier because the first loop exited early to save
      // processing time.
      // For this loop, however, we must examine every jump target and adjust
      // it as needed, and we cannot assume that the jump instructions are in
      // any particular order.
      for (auto & [boffset, ooffset] : offsets) {
        uinteger_t target = bytecode[boffset + 2];
        if (target >= bytecodeExclusiveEnd) {
          bytecode[boffset + 2] = target - bytecodeDeletedCount;
        }
        else if (target >= bytecodeStart) {
          // Target was jumping to an opcode that is now deleted.
          bytecode[boffset + 2] = bytecodeStart;
        }
      }
    }
    if (op == Opcode::FUNCTION) {
      // 3b. Update any Function targets that may have been affected.
      // We did not do this earlier because the first loop exited early to save
      // processing time.
      // For this loop, however, we must examine every jump target and adjust
      // it as needed, and we cannot assume that the jump instructions are in
      // any particular order.
      for (auto & [boffset, ooffset] : offsets) {
        uinteger_t target = bytecode[boffset + 2];
        if (target >= bytecodeExclusiveEnd) {
          bytecode[boffset + 2] = target - bytecodeDeletedCount;
        }
        else if (target >= bytecodeStart) {
          // Target was jumping to an opcode that is now deleted.
          bytecode[boffset + 2] = bytecodeStart;
        }
      }
    }
  }

  // 4. Update annotations with new Bytecode offsets.
  // Remove any annotations that are associated with the removed bytecodes.
  for (size_t i{bytecodeStart}; i < bytecodeExclusiveEnd; ++i) {
    annotations.erase(i);
  }
  // Move any annotations that are associated with Bytecode positions after the
  // deleted section.
  for (size_t i{bytecodeExclusiveEnd}; i < originalBytecodeSize; ++i) {
    if (annotations.count(i)) {
      annotations[i - bytecodeDeletedCount] = move(annotations[i]);
      annotations.erase(i);
    }
  }
}

void Program::optimize() {
  auto [opOffsets, ops] = this->analyze();

  bool changed = true;
  while (changed) {
    changed = false;
    // Optimization #1:
    // All opcodes after a JMP and before a jump target or function target
    // can be removed.
    //    17 JMPF_POP    32
    //      ...
    //    29 JMP         12
    //    31 POP
    //    32 PEEK        1
    //    ex: 31 can be removed.
    for (size_t i{0}; i < ops.size(); ++i) {
      if (ops[i].first == Opcode::JMP) {
        auto jmpBytecodeOffset = ops[i].second;
        size_t minBytecodeTarget = this->bytecode.size();
        // Check for Jump instruction targets.
        for (auto & op : jumpOpcodes_S) {
          if (opOffsets.count(op)) {
            for (auto & [bytecodeOffset, opcodeOffset] : opOffsets.at(op)) {
              auto jumpInstructionTarget = this->bytecode[bytecodeOffset + 1];
              if ((jumpInstructionTarget > jmpBytecodeOffset) && (jumpInstructionTarget < minBytecodeTarget)) {
                minBytecodeTarget = jumpInstructionTarget;
              }
            }
          }
        }
        for (auto & op : jumpOpcodes_I) {
          if (opOffsets.count(op)) {
            for (auto & [bytecodeOffset, opcodeOffset] : opOffsets.at(op)) {
              auto jumpInstructionTarget = this->bytecode[bytecodeOffset + 2];
              if ((jumpInstructionTarget > jmpBytecodeOffset) && (jumpInstructionTarget < minBytecodeTarget)) {
                minBytecodeTarget = jumpInstructionTarget;
              }
            }
          }
        }
        // Check for Function targets.
        if (opOffsets.count(Opcode::FUNCTION)) {
          for (auto & [bytecodeOffset, opcodeOffset] : opOffsets.at(Opcode::FUNCTION)) {
            auto jumpInstructionTarget = this->bytecode[bytecodeOffset + 2];
            if ((jumpInstructionTarget > jmpBytecodeOffset) && (jumpInstructionTarget < minBytecodeTarget)) {
              minBytecodeTarget = jumpInstructionTarget;
            }
          }
        }
        // Remove any bytecodes that can never be executed.
        auto firstBytecodeToDelete = jmpBytecodeOffset + 2;
        if (minBytecodeTarget > firstBytecodeToDelete) {
          // Figure out the opcode # of the "minBytecodeTarget".
          auto minOffset = i + 1;
          do {
            ++minOffset;
          } while ((minOffset < ops.size()) && (ops[minOffset].second < minBytecodeTarget));

          removeOpcodes(this->bytecode, i + 1, minOffset - (i + 1), opOffsets, ops, this->annotations);
          changed = true;
        }
      }
    }

    // Optimization #2:
    // Poke.. pop.. peek, when poke and peek are the same stack location.
    //    24 POKE        0
    //    26 POP
    //    27 PEEK        0
    //    ex: 26 & 27 can be removed, if not a jump target.
    //        27 is often a jump target when 26 is from a for() initialization.
    for (size_t i{2}; i < ops.size(); ++i) {
      // ops[i].first is an opcode
      // ops[i].second is a bytecodeTarget 
      if ((ops[i].first == Opcode::PEEK)
          && (ops[i - 1].first == Opcode::POP)
          && (ops[i - 2].first == Opcode::POKE)
          && (this->bytecode[ops[i].second + 1] == this->bytecode[ops[i - 2].second + 1])) {
        // The optimization cannot be performed if ops[i].second is a jump target
        bool isAJumpTarget{false};
        for (auto & op : jumpOpcodes_S) {
          if (opOffsets.count(op)) {
            for (auto & [bytecodeOffset, opcodeOffset] : opOffsets.at(op)) {
              if (this->bytecode[bytecodeOffset + 1] == ops[i].second) {
                isAJumpTarget = true;
                break;
              }
            }
          }
        }
        for (auto & op : jumpOpcodes_I) {
          if (opOffsets.count(op)) {
            for (auto & [bytecodeOffset, opcodeOffset] : opOffsets.at(op)) {
              if (this->bytecode[bytecodeOffset + 2] == ops[i].second) {
                isAJumpTarget = true;
                break;
              }
            }
          }
        }
        if (!isAJumpTarget) {
          // We have found a set of opcodes that can be removed!
          removeOpcodes(this->bytecode, i - 1, 2, opOffsets, ops, this->annotations);
          changed = true;
          i -= 2;
        }
      }
    }

    // Optimization #3:
    // Push.. pop, can be removed.
    //    17 JMPF_POP    24
    //    19 NULLVAL
    //    20 POP
    //    21 JMP         7
    //    ex: 19 & 20 can be removed, if 20 is not a jump target.
    for (size_t i{1}; i < ops.size(); ++i) {
      if ((ops[i].first == Opcode::POP) && (valueProducingOpcodes.count(ops[i-1].first))) {
        // We have found a set of opcodes that can be removed!
        removeOpcodes(this->bytecode, i - 1, 2, opOffsets, ops, this->annotations);
        changed = true;
        i -= 2;
      }
    }
  }
}

