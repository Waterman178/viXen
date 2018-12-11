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
    const PMCEngine engine;       // The engine bit mask used to enable/disable it, if applicable
};

// Engines used by NV2A
const Engine kEngine_PMC      = { { 0x00000000,   0x1000 }, PMCEngineNone   };   // Master control
const Engine kEngine_PBUS     = { { 0x00001000,   0x1000 }, PMCEngineNone   };   // Bus control
const Engine kEngine_PFIFO    = { { 0x00002000,   0x2000 }, PMCEnginePFIFO  };   // MMIO and DMA FIFO submission to PGRAPH  (there's no VPE in NV2A)
const Engine kEngine_PRMA     = { { 0x00007000,   0x1000 }, PMCEngineNone   };   // Real mode BAR access
const Engine kEngine_PVIDEO   = { { 0x00008000,   0x1000 }, PMCEnginePVIDEO };   // Video overlay
const Engine kEngine_PTIMER   = { { 0x00009000,   0x1000 }, PMCEnginePTIMER };   // Time measurement and time-based alarms
const Engine kEngine_PCOUNTER = { { 0x0000A000,   0x1000 }, PMCEngineNone   };   // Performance monitoring counters
const Engine kEngine_PMVIO    = { { 0x000C0000,   0x1000 }, PMCEngineNone   };   // VGA sequencer and graph controller registers
const Engine kEngine_PFB      = { { 0x00100000,   0x1000 }, PMCEnginePFB    };   // Memory interface
const Engine kEngine_PSTRAPS  = { { 0x00101000,   0x1000 }, PMCEngineNone   };   // Straps readout
const Engine kEngine_PROM     = { { 0x00300000,  0x20000 }, PMCEngineNone   };   // ROM access window
const Engine kEngine_PGRAPH   = { { 0x00400000,   0x2000 }, PMCEnginePGRAPH };   // 2D/3D graphics engine
const Engine kEngine_PCTRC    = { { 0x00600000,   0x1000 }, PMCEnginePCRTC  };   // CRTC controls
const Engine kEngine_PRMCIO   = { { 0x00601000,   0x1000 }, PMCEngineNone   };   // VGA CRTC and attribute controller registers
const Engine kEngine_PRAMDAC  = { { 0x00680000,   0x1000 }, PMCEngineNone   };   // RAMDAC, video overlay, cursor, and PLL control
const Engine kEngine_PRMDIO   = { { 0x00681000,   0x1000 }, PMCEngineNone   };   // VGA DAC registers
const Engine kEngine_PRAMIN   = { { 0x00700000, 0x100000 }, PMCEngineNone   };   // RAMIN access
const Engine kEngine_PUSER    = { { 0x00800000, 0x200000 }, PMCEngineNone   };   // PFIFO MMIO/DMA submission area

}
}
}
