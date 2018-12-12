// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include "nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

INV2AEngine::INV2AEngine(const Engine& engineDefs)
    : m_engineDefs(engineDefs)
{
    // Enable all engines that do not have a flag in the PMC Enable register
    if (engineDefs.engine == PMCEngineNone) {
        m_enabled = true;
        Reset();
    }
}

INV2AEngine::~INV2AEngine() {
}

void INV2AEngine::Reset() {
}

void INV2AEngine::Enable() {
    if (m_engineDefs.engine != PMCEngineNone) {
        if (!m_enabled) {
            Reset();
        }
        m_enabled = true;
    }
}

void INV2AEngine::Disable() {
    if (m_engineDefs.engine != PMCEngineNone) {
        if (m_enabled) {
            Stop();
        }
        m_enabled = false;
    }
}

}
}
}
