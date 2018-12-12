// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A device class.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "vixen/hw/basic/irq.h"

#include "engines/nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

/*!
 * The NV2A device class.
 */
class NV2A {
public:
    NV2A(uint8_t *vram, uint32_t vramSize, IRQHandler& irqHandler);
    ~NV2A();

    void Reset();

    void ReadEngine(uint32_t address, uint32_t *value, uint8_t size);
    void ReadVRAM(uint32_t address, uint32_t *value, uint8_t size);

    void WriteEngine(uint32_t address, uint32_t value, uint8_t size);
    void WriteVRAM(uint32_t address, uint32_t value, uint8_t size);

    inline uint32_t GetVRAMSize() const { return m_vramSize; }

private:
    uint8_t *m_vram;
    uint32_t m_vramSize;
    IRQHandler& m_irqHandler;

    // ----- Engines ----------------------------------------------------------

    void RegisterEngine(INV2AEngine *engine);
    bool LookupEngine(uint32_t addr, INV2AEngine **engine);

    std::map<uint32_t, INV2AEngine *> m_engines;
};

}
}
}
