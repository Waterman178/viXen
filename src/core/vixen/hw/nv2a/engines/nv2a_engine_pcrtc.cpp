// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PCRTC (CRTC Controls) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pcrtc.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APCRTCEngine::NV2APCRTCEngine()
    : INV2AEngine(kEngine_PCRTC)
{
}

NV2APCRTCEngine::~NV2APCRTCEngine() {
}

void NV2APCRTCEngine::Stop() {
}

void NV2APCRTCEngine::Reset() {
}

void NV2APCRTCEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APCRTCEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APCRTCEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APCRTCEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
