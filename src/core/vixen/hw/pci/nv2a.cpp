// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#include "nv2a.h"
#include "vixen/log.h"
#include "vixen/thread.h"

#include "vixen/hw/nv2a/engines/nv2a_engine_pmc.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pbus.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pfifo.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_prma.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pvideo.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_ptimer.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pcounter.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pmvio.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pfb.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pstraps.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_prom.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pgraph.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pcrtc.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_prmcio.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pramdac.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_prmdio.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_pramin.h"
#include "vixen/hw/nv2a/engines/nv2a_engine_user.h"

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
    RegisterEngine(new NV2APBUSEngine());
    RegisterEngine(new NV2APFIFOEngine());
    RegisterEngine(new NV2APRMAEngine());
    RegisterEngine(new NV2APVIDEOEngine());
    RegisterEngine(new NV2APTIMEREngine());
    RegisterEngine(new NV2APCOUNTEREngine());
    RegisterEngine(new NV2APMVIOEngine());
    RegisterEngine(new NV2APFBEngine());
    RegisterEngine(new NV2APSTRAPSEngine());
    RegisterEngine(new NV2APROMEngine());
    RegisterEngine(new NV2APGRAPHEngine());
    RegisterEngine(new NV2APCRTCEngine());
    RegisterEngine(new NV2APRMCIOEngine());
    RegisterEngine(new NV2APRAMDACEngine());
    RegisterEngine(new NV2APRMDIOEngine());
    RegisterEngine(new NV2APRAMINEngine());
    RegisterEngine(new NV2AUSEREngine());
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
    if (addr & 3) {
        log_warning("NV2ADevice::MMIORead:  Misaligned MMIO read!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
    }

    if (barIndex == 0) {
        INV2AEngine *engine;
        if (!LookupEngine(addr, &engine)) {
            log_warning("NV2ADevice::MMIORead:  Unmapped MMIO read!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
            *value = 0;
        }
        else if (engine->IsEnabled()) {
            engine->Read(addr - engine->GetEngineDefs().mmioRange.base, value, size);
        }
        else {
            *value = 0;
        }
    }
    else { // barIndex == 1
        log_warning("NV2ADevice::MMIORead:  Unimplemented MMIO read!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
        *value = 0;
    }
}

void NV2ADevice::PCIMMIOWrite(int barIndex, uint32_t addr, uint32_t value, uint8_t size) {
    if (addr & 3) {
        log_warning("NV2ADevice::MMIOWrite:  Misaligned MMIO write!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
    }

    if (barIndex == 0) {
        INV2AEngine *engine;
        if (!LookupEngine(addr, &engine)) {
            log_warning("NV2ADevice::MMIOWrite:  Unmapped MMIO write!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
        }
        else if (engine->IsEnabled()) {
            engine->Write(addr - engine->GetEngineDefs().mmioRange.base, value, size);
        }
    }
    else { // barIndex == 1
        log_warning("NV2ADevice::MMIOWrite:  Unimplemented MMIO write!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
    }
}


}
