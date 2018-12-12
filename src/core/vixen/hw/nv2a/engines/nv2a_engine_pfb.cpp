// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PFB (Memory Interface) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pfb.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APFBEngine::NV2APFBEngine() {
}

NV2APFBEngine::~NV2APFBEngine() {
}

void NV2APFBEngine::Start() {
}

void NV2APFBEngine::Stop() {
}

void NV2APFBEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APFBEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APFBEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APFBEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
