// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PROM (ROM Access Window) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_prom.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APROMEngine::NV2APROMEngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2APROMEngine::~NV2APROMEngine() {
}

void NV2APROMEngine::Start() {
}

void NV2APROMEngine::Stop() {
}

void NV2APROMEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APROMEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APROMEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APROMEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
