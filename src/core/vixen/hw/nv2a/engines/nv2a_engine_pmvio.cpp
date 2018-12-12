// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMVIO (VGA Sequencer and Graph Controller Registers) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pmvio.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APMVIOEngine::NV2APMVIOEngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2APMVIOEngine::~NV2APMVIOEngine() {
}

void NV2APMVIOEngine::Start() {
}

void NV2APMVIOEngine::Stop() {
}

void NV2APMVIOEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APMVIOEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APMVIOEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APMVIOEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
