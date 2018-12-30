// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#include "nv2a.h"
#include "vixen/log.h"
#include "vixen/thread.h"

namespace vixen {

using namespace hw::nv2a;

NV2ADevice::NV2ADevice(uint8_t *ram, uint32_t ramSize, IRQHandler& irqHandler)
	: PCIDevice(PCI_HEADER_TYPE_NORMAL, PCI_VENDOR_ID_NVIDIA, 0x02A0, 0xA1,
		0x03, 0x00, 0x00) // VGA-compatible controller
{
    m_nv2a = new NV2A(ram, ramSize, irqHandler);
}

NV2ADevice::~NV2ADevice() {
    delete m_nv2a;
}

// PCI Device functions

void NV2ADevice::Init() {
	RegisterBAR(0, 0x1000000, PCI_BAR_TYPE_MEMORY); // 0xFD000000 - 0xFDFFFFFF
	RegisterBAR(1, 0x8000000, PCI_BAR_TYPE_MEMORY | PCI_BAR_MEMORY_PREFETCHABLE); // 0xF0000000 - 0xF7FFFFFF
	RegisterBAR(2, 0x80000, PCI_BAR_TYPE_MEMORY | PCI_BAR_MEMORY_PREFETCHABLE); // 0x0 - 0x7FFFF

    Write8(m_configSpace, PCI_LATENCY_TIMER, 0xf8);

    // Initialize configuration space
    Write16(m_configSpace, PCI_STATUS, PCI_STATUS_FAST_BACK | PCI_STATUS_66MHZ | PCI_STATUS_CAP_LIST | PCI_STATUS_DEVSEL_MEDIUM);
    Write8(m_configSpace, PCI_CAPABILITY_LIST, 0x60);
    Write8(m_configSpace, PCI_MIN_GNT, 0x05);
    Write8(m_configSpace, PCI_MAX_LAT, 0x01);

    // Capability list
    Write8(m_configSpace, 0x60, PCI_CAP_ID_PM);
    Write8(m_configSpace, 0x61, 0x44);

    Write8(m_configSpace, 0x44, PCI_CAP_ID_AGP);
    Write8(m_configSpace, 0x45, 0x00);

    // Unknown registers
    Write16(m_configSpace, 0x46, 0x20);
    Write32(m_configSpace, 0x48, 0x1f000017);
    Write16(m_configSpace, 0x4c, 0x1f00);
    Write32(m_configSpace, 0x54, 0x1);
    Write32(m_configSpace, 0x58, 0x23d6ce);
    Write32(m_configSpace, 0x5c, 0xf);
    Write32(m_configSpace, 0x60, 0x24401);
    Write32(m_configSpace, 0x80, 0x2b16d065);

    Reset();
}

void NV2ADevice::Reset() {
    m_nv2a->Reset();
}

void NV2ADevice::PCIIORead(int barIndex, uint32_t port, uint32_t *value, uint8_t size) {
	log_warning("NV2ADevice::IORead:  Unexpected I/O read!   bar = %d,  port = 0x%x,  size = %u\n", barIndex, port, size);
    *value = 0;
}

void NV2ADevice::PCIIOWrite(int barIndex, uint32_t port, uint32_t value, uint8_t size) {
	log_warning("NV2ADevice::IOWrite: Unexpected I/O write!  bar = %d,  port = 0x%x,  size = %u,  value = 0x%x\n", barIndex, port, size, value);
}

void NV2ADevice::PCIMMIORead(int barIndex, uint32_t addr, uint32_t *value, uint8_t size) {
    if (addr & (size - 1)) {
        log_warning("NV2ADevice::MMIORead:  Misaligned MMIO read!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
    }

    if (barIndex == 0) {
        m_nv2a->ReadEngine(addr, value, size);
    }
    else { // barIndex == 1
        m_nv2a->ReadVRAM(addr, value, size);
    }
}

void NV2ADevice::PCIMMIOWrite(int barIndex, uint32_t addr, uint32_t value, uint8_t size) {
    if (addr & (size - 1)) {
        log_warning("NV2ADevice::MMIOWrite:  Misaligned MMIO write!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
    }

    if (barIndex == 0) {
        m_nv2a->WriteEngine(addr, value, size);
    }
    else { // barIndex == 1
        m_nv2a->WriteVRAM(addr, value, size);
    }
}


}
