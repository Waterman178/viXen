// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PFB (Memory Interface) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

namespace vixen {
namespace hw {
namespace nv2a {

// ----- PFB registers --------------------------------------------------------

enum PFBRegister {
    PFBRegConfig0 = 0x200,   // Configuration registers 0
    PFBRegCStatus = 0x20C,   // C... status
    PFBRegWBC = 0x410,       // Write-back cache?
};

// ----- PFB values -----------------------------------------------------------

}
}
}
