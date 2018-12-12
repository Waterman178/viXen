// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PFB (Memory Interface) engine.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

static constexpr Engine kEngine = { { 0x00100000, 0x1000 }, PMCEnablePFB };

class NV2APFBEngine : public INV2AEngineBase<kEngine_PFB> {
public:
    NV2APFBEngine(NV2A& nv2a);
    ~NV2APFBEngine();

    void Start() override;
    void Stop() override;

    void Read(uint32_t address, uint32_t *value, uint8_t size) override;
    void Write(uint32_t address, uint32_t value, uint8_t size) override;
};

}
}
}
