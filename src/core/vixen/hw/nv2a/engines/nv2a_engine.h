// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "../nv2a_defs.h"

namespace vixen {
namespace hw {
namespace nv2a {

// Interface for NV2A engines
class INV2AEngine {
public:
    virtual ~INV2AEngine();

protected:
    INV2AEngine(const Engine& engineDefs);

public:
    const Engine& GetEngineDefs() const { return m_engineDefs; }

    virtual void Read(uint32_t address, uint32_t *value) = 0;
    virtual void Write(uint32_t address, uint32_t value) = 0;

private:
    const Engine& m_engineDefs;
};

}
}
}
