/**
 * @file
 * Define the Tang::Program::dumpBytecode method.
 */

#include <set>
#include "program.hpp"
#include "opcode.hpp"

using namespace std;
using namespace Tang;

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
static void removeOpcodes([[maybe_unused]]Bytecode & bytecode, [[maybe_unused]]size_t position, [[maybe_unused]]size_t count, [[maybe_unused]]OpcodeOffsets & opOffsets, [[maybe_unused]]OpcodePositions & ops, [[maybe_unused]]OpcodeAnnotations & annotations) {
  // Sanity check to make sure that `position` is within the scope of 
  // available Opcode positions.
  if ((ops.size() <= position) || (count < 1)) {
    return;
  }

  // Determine the Bytecode locations affected.
  auto originalBytecodeSize = bytecode.size();
  auto bytecodeStart = ops[position].second;
  auto bytecodeExclusiveEnd = (position + count >= ops.size())
    ? ops.size()
    : ops[position + count].second;
  auto bytecodeDeletedCount = bytecodeExclusiveEnd - bytecodeStart;

  set<Opcode> jumpOpcodes{
    Opcode::JMP,
    Opcode::JMPF,
    Opcode::JMPF_POP,
    Opcode::JMPT,
    Opcode::JMPT_POP,
  };

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
        auto next = it + 1;
        offsets.erase(next.base());
        it = next - 1;
      }
    }
    if (jumpOpcodes.count(op)) {
      // 3. Update any Jump targets that may have been affected.
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
  /*
  for (auto & [op, offsets] : opOffsets) {
    cout << op << endl;
    for (auto & [boffset, ooffset] : offsets) {
      cout << "  " << boffset << " : " << ooffset << endl;
    }
  }
  */
}

void Program::optimize() {
  auto [opOffsets, ops] = this->analyze();
  //auto before = this->dumpBytecode();
  /*
  cout << "OPCODE OFFSETS (BYTECODE, OP #)" << endl;
  for (auto & [opcode, offsets] : opOffsets) {
    cout << "OPCODE: " << opcode << endl;
    for (auto & [bytecodeOffset, opcodeOffset] : offsets) {
      cout << "  " << bytecodeOffset << " : " << opcodeOffset << endl;
    }
  }

  cout << "OPCODES (order#, opcode, bytecode offset)" << endl;
  size_t opcodeOffset = 0;
  for (auto & [opcode, bytecodeOffset] : ops) {
    cout << opcodeOffset++ << " : " << opcode << " : " << bytecodeOffset << endl;
  }
  */

  set<Opcode> valueProducingOpcodes{
    Opcode::NULLVAL,
    Opcode::INTEGER,
    Opcode::FLOAT,
    Opcode::BOOLEAN,
    Opcode::STRING,
    Opcode::FUNCTION,
  };
	for (size_t i{1}; i < ops.size(); ++i) {
    if ((ops[i].first == Opcode::POP) && (valueProducingOpcodes.count(ops[i-1].first))) {
      // We have found a set of opcodes that can be removed!
      removeOpcodes(this->bytecode, i - 1, 2, opOffsets, ops, this->annotations);
      i -= 2;
    }
	}
  //auto after = this->dumpBytecode();
  /*
  if (before != after) {
    cout << "#########################################" << endl;
    cout << before;
    cout << "--------------------------" << endl << after;
  }
  */
}

