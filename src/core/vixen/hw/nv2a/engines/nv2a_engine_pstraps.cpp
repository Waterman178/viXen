// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PSTRAPS (Straps Readout) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pstraps.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APSTRAPSEngine::NV2APSTRAPSEngine() {
}

NV2APSTRAPSEngine::~NV2APSTRAPSEngine() {
}

void NV2APSTRAPSEngine::Start() {
}

void NV2APSTRAPSEngine::Stop() {
}

void NV2APSTRAPSEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APSTRAPSEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APSTRAPSEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APSTRAPSEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
