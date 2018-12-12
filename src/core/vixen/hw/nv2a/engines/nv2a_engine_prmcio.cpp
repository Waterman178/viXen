// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PRMCIO (VGA CRTC and Attribute Controller Registers) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_prmcio.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APRMCIOEngine::NV2APRMCIOEngine() {
}

NV2APRMCIOEngine::~NV2APRMCIOEngine() {
}

void NV2APRMCIOEngine::Start() {
}

void NV2APRMCIOEngine::Stop() {
}

void NV2APRMCIOEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APRMCIOEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APRMCIOEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APRMCIOEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
