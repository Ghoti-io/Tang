/**
 * @file
 * Header file supplied for use by 3rd party code so that they can easily
 * include all necessary headers.
 */

//
// Future Optimizations:
//
// 1. All opcodes after a JMP and before a jump target can be removed.
//    17 JMPF_POP    32
//      ...
//    29 JMP         12
//    31 POP
//    32 PEEK        1
//    ex: 31 can be removed.
//
// 2. Poke.. pop.. peek, when poke and peek are the same stack location.
//    24 POKE        0
//    26 POP
//    27 PEEK        0
//    ex: 26 & 27 can be removed, if not a jump target.
//

#ifndef TANG_HPP
#define TANG_HPP

#include "tangBase.hpp"
#include "astNode.hpp"
#include "error.hpp"
#include "garbageCollected.hpp"
#include "program.hpp"

#endif // TANG_HPP

