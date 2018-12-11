// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine.h"
#include "nv2a_engine_pmc.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APMCEngine::NV2APMCEngine()
    : INV2AEngine(kEngine_PMC)
{
}

NV2APMCEngine::~NV2APMCEngine() {
}

void NV2APMCEngine::Read(uint32_t address, uint32_t *value) {
    switch (address) {
    case PMCRegID:
        *value = CardID(0x2a, 0, 0xa2);
        break;
    default:
        log_warning("NV2APMCEngine::Read:  Unhandled read!   address = 0x%x\n", address);
        break;
    }
}

void NV2APMCEngine::Write(uint32_t address, uint32_t value) {
    log_warning("NV2APMCEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x\n", address, value);
}

}
}
}
