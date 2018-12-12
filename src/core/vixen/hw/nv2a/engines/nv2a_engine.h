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

/*!
 * A sparse array of write masks.
 * Entries not present in the array are considered to be unmasked, i.e. allow writing all bits of the register.
 */
typedef const std::unordered_map<const uint32_t, const uint32_t, std::hash<uint32_t>> WriteMasks;

static const WriteMasks kEmptyWriteMasks = {};

/*!
 * Interface for NV2A engines
 */
class INV2AEngine {
public:
    INV2AEngine() {}
    virtual ~INV2AEngine() {}

    /*!
     * Retrieves the engine's parameters.
     */
    virtual const Engine& GetParams() const = 0;

    /*!
     * Resets this engine to its default state.
     */
    virtual void Reset() = 0;

    /*!
     * Enables this engine.
     */
    virtual void Enable() = 0;

    /*!
     * Disables this engine.
     * Not all engines may be disabled.
     */
    virtual void Disable() = 0;

    /*!
     * Determines if the engine is enabled.
     * Some engines may be disabled through a PMC register, in which case they
     * will reset and become inaccessible through MMIO.
     */
    virtual bool IsEnabled() const = 0;

    virtual void Read(uint32_t address, uint32_t *value, uint8_t size) = 0;
    virtual void Write(uint32_t address, uint32_t value, uint8_t size) = 0;

protected:
    /*!
     * Starts this engine.
     * Sets all registers and state to default values.
     */
    virtual void Start() = 0;

    /*!
     * Stops execution of this engine.
     * Triggered by the PMC when writing 0 to the engine's enable bit.
     */
    virtual void Stop() = 0;
};

/*!
 * Template interface for NV2A engines
 */
template<const Engine& engine, const WriteMasks& writeMasks = kEmptyWriteMasks>
class INV2AEngineBase : public INV2AEngine {
public:
    INV2AEngineBase() {
        // Enable all engines that do not have a flag in the PMC Enable register
        if constexpr (engine.enableBit == PMCEnableNone) {
            m_enabled = true;
        }
    }
    virtual ~INV2AEngineBase() {}

protected:
    virtual void Start() override = 0;
    virtual void Stop() override = 0;

public:
    inline const Engine& GetParams() const { return engine; }

    void Reset() override {
        memset(m_regs, 0, sizeof(m_regs));
        Start();
    }
    
    void Enable() override {
        if constexpr (engine.enableBit != PMCEnableNone) {
            if (!m_enabled) {
                Reset();
            }
            m_enabled = true;
        }
    }

    void Disable() override {
        if constexpr (engine.enableBit != PMCEnableNone) {
            if (m_enabled) {
                Stop();
            }
            m_enabled = false;
        }
    }

    inline bool IsEnabled() const override { return m_enabled; }

protected:
    /*!
     * Read from a register.
     */
    void RegRead(uint32_t reg, uint32_t *value, uint8_t size) {
        assert(reg + size <= engine.mmioRange.count);   // register access within range
        assert(size == 1 || size == 2 || size == 4);    // 1, 2 or 4 byte reads
        assert((reg & 3) == 0);                         // 4-byte aligned reads

        switch (size) {
        case 1: *value = m_regs[reg]; break;
        case 2: *value = *(uint16_t*)&m_regs[reg]; break;
        case 4: *value = *(uint32_t*)&m_regs[reg]; break;
        }
    }

    /*!
     * Write to a register.
     */
    void RegWrite(uint32_t reg, uint32_t value, uint8_t size) {
        assert(reg + size <= engine.mmioRange.count);   // register access within range
        assert(size == 1 || size == 2 || size == 4);    // 1, 2 or 4 byte reads
        assert((reg & 3) == 0);                         // 4-byte aligned reads

        if (writeMasks.count(reg) != 0) {
            uint32_t mask = writeMasks.at(reg);
            switch (size) {
            case 1: m_regs[reg] = (value & mask) | (m_regs[reg] & ~mask); break;
            case 2: *(uint16_t*)&m_regs[reg] = (value & mask) | ((*(uint16_t*)&m_regs[reg]) & ~mask); break;
            case 4: *(uint32_t*)&m_regs[reg] = (value & mask) | ((*(uint32_t*)&m_regs[reg]) & ~mask); break;
            }
        }
        else {
            switch (size) {
            case 1: m_regs[reg] = value; break;
            case 2: *(uint16_t*)&m_regs[reg] = value; break;
            case 4: *(uint32_t*)&m_regs[reg] = value; break;
            }
        }
    }

    /*!
     * Write to a register without using masks.
     * Should be used internally, but not on the MMIO interface.
     */
    void RegWriteUnmasked(uint32_t reg, uint32_t value, uint8_t size) {
        assert(reg + size <= engine.mmioRange.count);   // register access within range
        assert(size == 1 || size == 2 || size == 4);    // 1, 2 or 4 byte reads
        assert((reg & 3) == 0);                         // 4-byte aligned reads

        switch (size) {
        case 1: m_regs[reg] = value; break;
        case 2: *(uint16_t*)&m_regs[reg] = value; break;
        case 4: *(uint32_t*)&m_regs[reg] = value; break;
        }
    }

private:
    // The registers used by this engine
    uint8_t m_regs[engine.mmioRange.count];

    // Whether the engine is enabled or disabled.
    bool m_enabled;
};

}
}
}
