// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pmc.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APMCEngine::NV2APMCEngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a)
{
}

NV2APMCEngine::~NV2APMCEngine() {
}

void NV2APMCEngine::Start() {
    // Initialize registers
    RegWriteUnmasked(PMCRegID, CardID(0x2a, 0, 0xa2), sizeof(uint32_t));
}

void NV2APMCEngine::Stop() {
}

void NV2APMCEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    RegRead(address, value, size);
}

void NV2APMCEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    RegWrite(address, value, size);

    switch (address) {
    case PMCRegEnable:
        PropagateEnable();
        break;

    // Read-only registers
    case PMCRegID:
        break;

    default:
        log_spew("NV2APMCEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
        break;
    }
}

void NV2APMCEngine::PropagateEnable() {
    uint32_t enable;
    RegRead(PMCRegEnable, &enable, sizeof(uint32_t));
    // TODO: propagate to respective engines
}

}
}
}
