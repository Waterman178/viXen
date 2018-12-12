// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PRMA (Real Mode BAR Access) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_prma.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APRMAEngine::NV2APRMAEngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2APRMAEngine::~NV2APRMAEngine() {
}

void NV2APRMAEngine::Start() {
}

void NV2APRMAEngine::Stop() {
}

void NV2APRMAEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APRMAEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APRMAEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APRMAEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
