// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PRAMIN (RAMIN Access) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pramin.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APRAMINEngine::NV2APRAMINEngine() {
}

NV2APRAMINEngine::~NV2APRAMINEngine() {
}

void NV2APRAMINEngine::Start() {
}

void NV2APRAMINEngine::Stop() {
}

void NV2APRAMINEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APRAMINEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APRAMINEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APRAMINEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
