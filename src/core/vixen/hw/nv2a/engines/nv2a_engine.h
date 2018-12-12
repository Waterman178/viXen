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
    INV2AEngine(const Engine& engineDefs);
    virtual ~INV2AEngine();

    virtual void Stop() = 0;
    virtual void Reset();

    virtual void Read(uint32_t address, uint32_t *value, uint8_t size) = 0;
    virtual void Write(uint32_t address, uint32_t value, uint8_t size) = 0;

    // Determines if the engine is enabled.
    // Some engines may be disabled through a PMC register, in which case they
    // will reset and become inaccessible through MMIO.
    virtual bool IsEnabled() { return m_enabled; }

    // Enables this engine.
    void Enable();

    // Disables this engine. Not all engines may be disabled.
    void Disable();

    const Engine& GetEngineDefs() const { return m_engineDefs; }

private:
    const Engine& m_engineDefs;

    // Whether the engine is enabled or disabled.
    bool m_enabled;
};

}
}
}
