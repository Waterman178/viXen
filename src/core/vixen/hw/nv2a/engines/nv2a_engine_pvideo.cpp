// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PVIDEO (Video Overlay) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pvideo.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APVIDEOEngine::NV2APVIDEOEngine()
    : INV2AEngine(kEngine_PVIDEO)
{
}

NV2APVIDEOEngine::~NV2APVIDEOEngine() {
}

void NV2APVIDEOEngine::Stop() {
}

void NV2APVIDEOEngine::Reset() {
}

void NV2APVIDEOEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APVIDEOEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APVIDEOEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APVIDEOEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
