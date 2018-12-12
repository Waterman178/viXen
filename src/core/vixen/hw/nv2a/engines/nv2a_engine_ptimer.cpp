// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PTIMER (Time Measurement and Time-Based Alarms) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_ptimer.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APTIMEREngine::NV2APTIMEREngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2APTIMEREngine::~NV2APTIMEREngine() {
}

void NV2APTIMEREngine::Start() {
}

void NV2APTIMEREngine::Stop() {
}

void NV2APTIMEREngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    log_spew("NV2APTIMEREngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
    *value = 0;
}

void NV2APTIMEREngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    log_spew("NV2APTIMEREngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
}

}
}
}
