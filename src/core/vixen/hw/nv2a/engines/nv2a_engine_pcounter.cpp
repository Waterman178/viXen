// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PCOUNTER (Performance Monitoring Counters) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pcounter.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APCOUNTEREngine::NV2APCOUNTEREngine() {
}

NV2APCOUNTEREngine::~NV2APCOUNTEREngine() {
}

void NV2APCOUNTEREngine::Start() {
}

void NV2APCOUNTEREngine::Stop() {
}

void NV2APCOUNTEREngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APCOUNTEREngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APCOUNTEREngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APCOUNTEREngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
