// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PCRTC (CRTC Controls) engine.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

class NV2APCRTCEngine : public INV2AEngineBase<kEngine_PCRTC> {
public:
    NV2APCRTCEngine(NV2A& nv2a);
    ~NV2APCRTCEngine();

    void Start() override;
    void Stop() override;

    void Read(uint32_t address, uint32_t *value, uint8_t size) override;
    void Write(uint32_t address, uint32_t value, uint8_t size) override;
};

}
}
}
