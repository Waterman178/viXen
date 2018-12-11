// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "../defs.h"
#include "pci.h"
#include "../basic/irq.h"

#include "vixen/hw/nv2a/nv2a_defs.h"
#include "vixen/hw/nv2a/engines/nv2a_engine.h"

namespace vixen {

class NV2ADevice : public PCIDevice {
public:
    NV2ADevice(uint8_t *ram, uint32_t ramSize, IRQHandler& irqHandler);
    virtual ~NV2ADevice();

    // PCI Device functions
    void Init();
    void Reset();

    void PCIIORead(int barIndex, uint32_t port, uint32_t *value, uint8_t size) override;
    void PCIIOWrite(int barIndex, uint32_t port, uint32_t value, uint8_t size) override;
    void PCIMMIORead(int barIndex, uint32_t addr, uint32_t *value, uint8_t size) override;
    void PCIMMIOWrite(int barIndex, uint32_t addr, uint32_t value, uint8_t size) override;

private:
    uint8_t *m_ram;
    uint32_t m_ramSize;
    IRQHandler& m_irqHandler;

    // ----- Engines ----------------------------------------------------------

    void RegisterEngine(hw::nv2a::INV2AEngine *engine);
    bool LookupEngine(uint32_t addr, hw::nv2a::INV2AEngine **engine);

    std::map<uint32_t, hw::nv2a::INV2AEngine *> m_engines;

};

}
