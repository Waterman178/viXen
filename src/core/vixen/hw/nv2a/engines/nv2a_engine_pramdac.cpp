// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PRAMDAC (RAMDAC, video overlay, cursor, and PLL control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pramdac.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APRAMDACEngine::NV2APRAMDACEngine() {
}

NV2APRAMDACEngine::~NV2APRAMDACEngine() {
}

void NV2APRAMDACEngine::Start() {
}

void NV2APRAMDACEngine::Stop() {
}

void NV2APRAMDACEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APRAMDACEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APRAMDACEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APRAMDACEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
