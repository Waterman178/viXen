#include "nv2a.h"
#include "vixen/log.h"
#include "vixen/thread.h"

#include <cassert>
#include <cstring>

namespace vixen {

NV2ADevice::NV2ADevice(uint8_t *ram, uint32_t ramSize, IRQHandler& irqHandler)
	: PCIDevice(PCI_HEADER_TYPE_NORMAL, PCI_VENDOR_ID_NVIDIA, 0x02A0, 0xA1,
		0x03, 0x00, 0x00) // VGA-compatible controller
    , m_ram(ram)
    , m_ramSize(ramSize)
    , m_irqHandler(irqHandler)
{
}

NV2ADevice::~NV2ADevice() {
}

// PCI Device functions

void NV2ADevice::Init() {
	RegisterBAR(0, 16 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xFD000000 - 0xFDFFFFFF
	RegisterBAR(1, 128 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xF0000000 - 0xF7FFFFFF
	// TODO: check if this is correct
	RegisterBAR(2, 64 * 1024 * 1024, PCI_BAR_TYPE_MEMORY); // 0xF8000000 - 0xFBFFFFFF

    Write8(m_configSpace, PCI_INTERRUPT_PIN, 1);

    Reset();
}

void NV2ADevice::Reset() {
}

void NV2ADevice::PCIIORead(int barIndex, uint32_t port, uint32_t *value, uint8_t size) {
	log_warning("NV2ADevice::IORead:  Unexpected I/O read!   bar = %d,  port = 0x%x,  size = %u\n", barIndex, port, size);
    *value = 0;
}

void NV2ADevice::PCIIOWrite(int barIndex, uint32_t port, uint32_t value, uint8_t size) {
	log_warning("NV2ADevice::IOWrite: Unexpected I/O write!  bar = %d,  port = 0x%x,  size = %u,  value = 0x%x\n", barIndex, port, size, value);
}

void NV2ADevice::PCIMMIORead(int barIndex, uint32_t addr, uint32_t *value, uint8_t size) {
	log_warning("NV2ADevice::MMIORead:  Unimplemented!  bar = %d,  addr = 0x%x,  size = %u\n", barIndex, addr, size);
    *value = 0;
}

void NV2ADevice::PCIMMIOWrite(int barIndex, uint32_t addr, uint32_t value, uint8_t size) {
	log_warning("NV2ADevice::MMIOWrite: Unimplemented!  bar = %d,  addr = 0x%x,  size = %u,  value = 0x%x\n", barIndex, addr, size, value);
}

}
