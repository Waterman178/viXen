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
	RegisterBAR(0, 16 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xFD000000 - 0xFDFFFFFF
	RegisterBAR(1, 128 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xF0000000 - 0xF7FFFFFF

    Write8(m_configSpace, PCI_INTERRUPT_PIN, 1);

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
