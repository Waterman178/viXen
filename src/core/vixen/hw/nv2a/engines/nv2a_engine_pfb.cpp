// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PFB (Memory Interface) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pfb.h"
#include "../nv2a.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APFBEngine::NV2APFBEngine(NV2A& nv2a)
    : INV2AEngineBase(nv2a) {
}

NV2APFBEngine::~NV2APFBEngine() {
}

void NV2APFBEngine::Start() {
    RegWriteUnmasked(PFBRegConfig0, 3, sizeof(uint32_t));
    RegWriteUnmasked(PFBRegCStatus, m_nv2a.GetVRAMSize(), sizeof(uint32_t));
    RegWriteUnmasked(PFBRegWBC, 0, sizeof(uint32_t));
}

void NV2APFBEngine::Stop() {
}

void NV2APFBEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    RegRead(address, value, size);
}

void NV2APFBEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    RegWrite(address, value, size);
}

}
}
}
