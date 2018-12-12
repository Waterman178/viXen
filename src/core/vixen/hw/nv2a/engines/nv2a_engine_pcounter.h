// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PCOUNTER (Performance Monitoring Counters) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

class NV2APCOUNTEREngine : public INV2AEngineBase<kEngine_PCOUNTER> {
public:
    NV2APCOUNTEREngine();
    ~NV2APCOUNTEREngine();

    void Start() override;
    void Stop() override;

    void Read(uint32_t address, uint32_t *value, uint8_t size) override;
    void Write(uint32_t address, uint32_t value, uint8_t size) override;
};

}
}
}
