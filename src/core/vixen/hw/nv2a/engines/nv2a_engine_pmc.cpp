// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine_pmc.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2APMCEngine::NV2APMCEngine()
    : INV2AEngine(kEngine_PMC)
{
}

NV2APMCEngine::~NV2APMCEngine() {
}

void NV2APMCEngine::Stop() {
}

void NV2APMCEngine::Reset() {
    // Initialize registers
    m_cardID = CardID(0x2a, 0, 0xa2);
    SetEnable(0);
}

void NV2APMCEngine::Read(uint32_t address, uint32_t *value, uint8_t size) {
    switch (address) {
    case PMCRegID:
        *value = m_cardID;
        break;
    case PMCRegEnable:
        *value = m_enable;
        break;

    default:
        log_spew("NV2APMCEngine::Read:  Unhandled read!   address = 0x%x,  size = %u\n", address, size);
        *value = 0;
        break;
    }
}

void NV2APMCEngine::Write(uint32_t address, uint32_t value, uint8_t size) {
    switch (address) {
    case PMCRegEnable:
        if (size == 1) {
            value = (m_enable & 0xFFFFFF00) | (value & 0xFF);
        }
        else if (size == 2) {
            value = (m_enable & 0xFFFF0000) | (value & 0xFFFF);
        }
        SetEnable(value);
        break;

    // Read-only registers
    case PMCRegID:
        break;

    default:
        log_spew("NV2APMCEngine::Write:  Unhandled write!   address = 0x%x,  value = 0x%x,  size = %u\n", address, value, size);
        break;
    }
}

void NV2APMCEngine::SetEnable(uint32_t value) {
    m_enable = value;
    // TODO: propagate to respective engines
}

}
}
}
