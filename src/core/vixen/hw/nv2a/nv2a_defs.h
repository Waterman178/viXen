// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// Base NV2A definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "nv2a_pmc_defs.h"

namespace vixen {
namespace hw {
namespace nv2a {

// Specifies a range of MMIO addresses
struct MMIORange {
    const uint32_t base;    // The base address
    const uint32_t count;   // The range length

    inline bool InRange(const uint32_t address) const { return address >= base && address < base + count; }
};

// Specifies parameters for an engine
struct Engine {
    const MMIORange mmioRange;    // The range of MMIO addresses that access the engine
    const PMCEnable enableBit;    // The engine bit mask used to enable/disable it, if applicable
};

// Engines used by NV2A
constexpr Engine kEngine_PMC      = { { 0x00000000,   0x1000 }, PMCEnableNone   };   // Master control
constexpr Engine kEngine_PBUS     = { { 0x00001000,   0x1000 }, PMCEnableNone   };   // Bus control
constexpr Engine kEngine_PFIFO    = { { 0x00002000,   0x2000 }, PMCEnablePFIFO  };   // MMIO and DMA FIFO submission to PGRAPH  (there's no VPE in NV2A)
constexpr Engine kEngine_PRMA     = { { 0x00007000,   0x1000 }, PMCEnableNone   };   // Real mode BAR access
constexpr Engine kEngine_PVIDEO   = { { 0x00008000,   0x1000 }, PMCEnablePVIDEO };   // Video overlay
constexpr Engine kEngine_PTIMER   = { { 0x00009000,   0x1000 }, PMCEnablePTIMER };   // Time measurement and time-based alarms
constexpr Engine kEngine_PCOUNTER = { { 0x0000A000,   0x1000 }, PMCEnableNone   };   // Performance monitoring counters
constexpr Engine kEngine_PMVIO    = { { 0x000C0000,   0x1000 }, PMCEnableNone   };   // VGA sequencer and graph controller registers
constexpr Engine kEngine_PFB      = { { 0x00100000,   0x1000 }, PMCEnablePFB    };   // Memory interface
constexpr Engine kEngine_PSTRAPS  = { { 0x00101000,   0x1000 }, PMCEnableNone   };   // Straps readout
constexpr Engine kEngine_PROM     = { { 0x00300000,  0x20000 }, PMCEnableNone   };   // ROM access window
constexpr Engine kEngine_PGRAPH   = { { 0x00400000,   0x2000 }, PMCEnablePGRAPH };   // 2D/3D graphics engine
constexpr Engine kEngine_PCRTC    = { { 0x00600000,   0x1000 }, PMCEnablePCRTC  };   // CRTC controls
constexpr Engine kEngine_PRMCIO   = { { 0x00601000,   0x1000 }, PMCEnableNone   };   // VGA CRTC and attribute controller registers
constexpr Engine kEngine_PRAMDAC  = { { 0x00680000,   0x1000 }, PMCEnableNone   };   // RAMDAC, video overlay, cursor, and PLL control
constexpr Engine kEngine_PRMDIO   = { { 0x00681000,   0x1000 }, PMCEnableNone   };   // VGA DAC registers
constexpr Engine kEngine_PRAMIN   = { { 0x00700000, 0x100000 }, PMCEnableNone   };   // RAMIN access
constexpr Engine kEngine_USER     = { { 0x00800000, 0x200000 }, PMCEnableNone   };   // PFIFO MMIO/DMA submission area

}
}
}
