// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PFIFO (MMIO and DMA FIFO submission to PGRAPH) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pfifo.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APFIFOEngine::NV2APFIFOEngine() {
}

NV2APFIFOEngine::~NV2APFIFOEngine() {
}

void NV2APFIFOEngine::Start() {
}

void NV2APFIFOEngine::Stop() {
}

void NV2APFIFOEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APFIFOEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APFIFOEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APFIFOEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
