// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#include "nv2a.h"
#include "vixen/log.h"
#include "vixen/thread.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pmc.h"

#include <cassert>
#include <cstring>

namespace vixen {

using namespace hw::nv2a;

NV2ADevice::NV2ADevice(uint8_t *ram, uint32_t ramSize, IRQHandler& irqHandler)
	: PCIDevice(PCI_HEADER_TYPE_NORMAL, PCI_VENDOR_ID_NVIDIA, 0x02A0, 0xA1,
		0x03, 0x00, 0x00) // VGA-compatible controller
    , m_ram(ram)
    , m_ramSize(ramSize)
    , m_irqHandler(irqHandler)
{
    RegisterEngine(new NV2APMCEngine());
}

NV2ADevice::~NV2ADevice() {
    for (auto it = m_engines.begin(); it != m_engines.end(); it++) {
        delete it->second;
    }
}

void NV2ADevice::RegisterEngine(INV2AEngine *engine) {
    m_engines[engine->GetEngineDefs().mmioRange.base] = engine;
}

// PCI Device functions

void NV2ADevice::Init() {
	RegisterBAR(0, 16 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xFD000000 - 0xFDFFFFFF
	RegisterBAR(1, 128 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xF0000000 - 0xF7FFFFFF

    Write8(m_configSpace, PCI_INTERRUPT_PIN, 1);

    Reset();
}

void NV2ADevice::Reset() {
}

bool NV2ADevice::LookupEngine(uint32_t addr, INV2AEngine **engine) {
    auto p = m_engines.upper_bound(addr);

    // p->first > addr
    if (p == m_engines.begin()) {
        return false;
    }

    // p->first <= addr
    --p;

    if (p->second->GetEngineDefs().mmioRange.InRange(addr)) {
        *engine = p->second;
        return true;
    }

    return false;
}

void NV2ADevice::PCIIORead(int barIndex, uint32_t port, uint32_t *value, uint8_t size) {
	log_warning("NV2ADevice::IORead:  Unexpected I/O read!   bar = %d,  port = 0x%x,  size = %u\n", barIndex, port, size);
    *value = 0;
}

void NV2ADevice::PCIIOWrite(int barIndex, uint32_t port, uint32_t value, uint8_t size) {
	log_warning("NV2ADevice::IOWrite: Unexpected I/O write!  bar = %d,  port = 0x%x,  size = %u,  value = 0x%x\n", barIndex, port, size, value);
}

void NV2ADevice::PCIMMIORead(int barIndex, uint32_t addr, uint32_t *value, uint8_t size) {
    if (size != 4) {
        log_warning("NV2ADevice::MMIORead:  Unexpected read of size %u!  bar = %d,  addr = 0x%x\n", size, barIndex, addr);
    }

    if (barIndex == 0) {
        INV2AEngine *engine;
        if (!LookupEngine(addr, &engine)) {
            log_warning("NV2ADevice::MMIORead:  Unmapped access!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
            *value = 0;
        }
        else {
            engine->Read(addr - engine->GetEngineDefs().mmioRange.base, value);
        }
    }
    else { // barIndex == 1
        log_warning("NV2ADevice::MMIORead:  Unimplemented!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
        *value = 0;
    }
}

void NV2ADevice::PCIMMIOWrite(int barIndex, uint32_t addr, uint32_t value, uint8_t size) {
    if (size != 4) {
        log_warning("NV2ADevice::MMIOWrite:  Unexpected read of size %u!  bar = %d,  addr = 0x%x,  value = 0x%x\n", size, barIndex, addr, value);
    }

    if (barIndex == 0) {
        INV2AEngine *engine;
        if (!LookupEngine(addr, &engine)) {
            log_warning("NV2ADevice::MMIOWrite:  Unmapped access!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
        }
        else {
            engine->Write(addr - engine->GetEngineDefs().mmioRange.base, value);
        }
    }
    else { // barIndex == 1
        log_warning("NV2ADevice::MMIOWrite:  Unimplemented!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
    }
}


}
