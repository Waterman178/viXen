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
    : m_engineDefs(engineDefs) {
}

INV2AEngine::~INV2AEngine() {
}

}
}
}
