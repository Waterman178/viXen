// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A PMC (Master Control) definitions.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#pragma once

#include <cstdint>

#include "nv2a_engine.h"

namespace vixen {
namespace hw {
namespace nv2a {

static WriteMasks kWriteMasks = {
    { PMCRegID, 0 },
};

class NV2APMCEngine : public INV2AEngineBase<kEngine_PMC, kWriteMasks> {
public:
    NV2APMCEngine();
    ~NV2APMCEngine();

protected:
    void Start() override;
    void Stop() override;

public:
    void Read(uint32_t address, uint32_t *value, uint8_t size) override;
    void Write(uint32_t address, uint32_t value, uint8_t size) override;

private:
    // Propagates the enable bits to the respective engines
    void PropagateEnable();
};

}
}
}
