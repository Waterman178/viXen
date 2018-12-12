// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PBUS (Bus Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pbus.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APBUSEngine::NV2APBUSEngine()
    : INV2AEngine(kEngine_PBUS)
{
}

NV2APBUSEngine::~NV2APBUSEngine() {
}

void NV2APBUSEngine::Stop() {
}

void NV2APBUSEngine::Reset() {
}

void NV2APBUSEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APBUSEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APBUSEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APBUSEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
