// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PGRAPH (2D/3D Graphics Engine) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pgraph.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APGRAPHEngine::NV2APGRAPHEngine()
    : INV2AEngine(kEngine_PGRAPH)
{
}

NV2APGRAPHEngine::~NV2APGRAPHEngine() {
}

void NV2APGRAPHEngine::Stop() {
}

void NV2APGRAPHEngine::Reset() {
}

void NV2APGRAPHEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APGRAPHEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APGRAPHEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APGRAPHEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
