// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

namespace vixen {
namespace hw {
namespace nv2a {

// ----- PMC registers --------------------------------------------------------

enum PMCRegister {
    PMCRegID = 0x0,                 // Card identification
    PMCRegEndian = 0x4,             // Endian switch
    PMCRegIntrStatus = 0x100,       // Interrupt status
    PMCRegIntrEnable = 0x140,       // Interrupt enable
    PMCRegIntrLineStatus = 0x160,   // Interrupt line status
    PMCRegEnable = 0x200,           // Engine master enable
    PMCRegVRAMHideLow = 0x300,      // VRAM hidden area low address
    PMCRegVRAMHideHigh = 0x304,     // VRAM hidden area high address
};

// ----- PMC values -----------------------------------------------------------

// --- ID

// Constructs the card identification value returned by the ID register.
inline uint32_t CardID(uint8_t gpuID, uint8_t devID, uint8_t stepping) {
    return (gpuID << 20) | ((devID & 0xF) << 16) | stepping;
}

// --- Endian

// Values returned by the PMC Endian register
enum PMCEndian : uint32_t {
    PMCLittleEndian = 0x0,       // Little endian
    PMCBigEndian = 0x01000001,   // Big endian
};

// The bit that must be flipped in the PMC Endian register to switch between little and big endian modes
const uint32_t kPMCEndianSwitchBit = 24;

// --- Enable

// Bits indicating the engines controlled by the PMC Enable register.
// Setting 1 to the corresponding bit enables the engine, 0 disables it.
// MMIO ranges are removed and engines are reset when disabled.
enum PMCEnable : uint32_t {
    PMCEnableNone = 0,              // No engine (used for engines that cannot be disabled)
    PMCEnablePFIFO = (1u << 8),     // PFIFO
    PMCEnablePGRAPH = (1u << 12),   // PGRAPH
    PMCEnablePTIMER = (1u << 16),   // PTIMER
    PMCEnablePFB = (1u << 20),      // PFB
    PMCEnablePCRTC = (1u << 24),    // PCRTC
    PMCEnablePVIDEO = (1u << 28),   // PVIDEO
};

// --- Interrupts

// Bits corresponding to the interrupts in the PMC interrupt registers.
enum PMCInterrupts : uint32_t {
    PMCIntrPFIFO = (1u << 8),       // PFIFO
    PMCIntrPGRAPH = (1u << 12),     // PGRAPH
    PMCIntrPVIDEO = (1u << 16),     // PVIDEO
    PMCIntrPTIMER = (1u << 20),     // PTIMER
    PMCIntrPCRTC = (1u << 24),      // PCRTC
    PMCIntrPBUS = (1u << 28),       // PBUS
    PMCIntrSoftware = (1u << 31),   // Software
};

}
}
}
