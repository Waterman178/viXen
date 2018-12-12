// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A USER (PFIFO MMIO/DMA Submission Area) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_user.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2AUSEREngine::NV2AUSEREngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2AUSEREngine::~NV2AUSEREngine() {
}

void NV2AUSEREngine::Start() {
}

void NV2AUSEREngine::Stop() {
}

void NV2AUSEREngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2AUSEREngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2AUSEREngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2AUSEREngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
