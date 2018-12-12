// NV2A emulation for the Original Xbox
// (C) Ivan "StrikerX3" Oliveira
//
// NV2A device class.
//
// Portions based on envytools documentation:
//   https://envytools.readthedocs.io/en/latest/index.html
#include "nv2a.h"

#include "engines/nv2a_engine_pmc.h"
#include "engines/nv2a_engine_pbus.h"
#include "engines/nv2a_engine_pfifo.h"
#include "engines/nv2a_engine_prma.h"
#include "engines/nv2a_engine_pvideo.h"
#include "engines/nv2a_engine_ptimer.h"
#include "engines/nv2a_engine_pcounter.h"
#include "engines/nv2a_engine_pmvio.h"
#include "engines/nv2a_engine_pfb.h"
#include "engines/nv2a_engine_pstraps.h"
#include "engines/nv2a_engine_prom.h"
#include "engines/nv2a_engine_pgraph.h"
#include "engines/nv2a_engine_pcrtc.h"
#include "engines/nv2a_engine_prmcio.h"
#include "engines/nv2a_engine_pramdac.h"
#include "engines/nv2a_engine_prmdio.h"
#include "engines/nv2a_engine_pramin.h"
#include "engines/nv2a_engine_user.h"

namespace vixen {
namespace hw {
namespace nv2a {

NV2A::NV2A(uint8_t *vram, uint32_t vramSize, IRQHandler& irqHandler)
    : m_vram(vram)
    , m_vramSize(vramSize)
    , m_irqHandler(irqHandler)
{
    auto pmc = new NV2APMCEngine(*this);
    auto pbus = new NV2APBUSEngine(*this);
    auto pfifo = new NV2APFIFOEngine(*this);
    auto prma = new NV2APRMAEngine(*this);
    auto pvideo = new NV2APVIDEOEngine(*this);
    auto ptimer = new NV2APTIMEREngine(*this);
    auto pcounter = new NV2APCOUNTEREngine(*this);
    auto pmvio = new NV2APMVIOEngine(*this);
    auto pfb = new NV2APFBEngine(*this);
    auto pstraps = new NV2APSTRAPSEngine(*this);
    auto prom = new NV2APROMEngine(*this);
    auto pgraph = new NV2APGRAPHEngine(*this);
    auto pcrtc = new NV2APCRTCEngine(*this);
    auto prmcio = new NV2APRMCIOEngine(*this);
    auto pramdac = new NV2APRAMDACEngine(*this);
    auto prmdio = new NV2APRMDIOEngine(*this);
    auto pramin = new NV2APRAMINEngine(*this);
    auto user = new NV2AUSEREngine(*this);

    // TODO: pmc->Connect(m_PFIFO, m_PGRAPH, m_PTIMER, m_PFB, m_PCRTC, m_PVIDEO);

    RegisterEngine(pmc);
    RegisterEngine(pbus);
    RegisterEngine(pfifo);
    RegisterEngine(prma);
    RegisterEngine(pvideo);
    RegisterEngine(ptimer);
    RegisterEngine(pcounter);
    RegisterEngine(pmvio);
    RegisterEngine(pfb);
    RegisterEngine(pstraps);
    RegisterEngine(prom);
    RegisterEngine(pgraph);
    RegisterEngine(pcrtc);
    RegisterEngine(prmcio);
    RegisterEngine(pramdac);
    RegisterEngine(prmdio);
    RegisterEngine(pramin);
    RegisterEngine(user);
}

NV2A::~NV2A() {
    for (auto it = m_engines.begin(); it != m_engines.end(); it++) {
        delete it->second;
    }
}

void NV2A::Reset() {
    for (auto it = m_engines.begin(); it != m_engines.end(); it++) {
        it->second->Reset();
    }
}

void NV2A::ReadEngine(uint32_t address, uint32_t *value, uint8_t size) {
    INV2AEngine *engine;
    if (!LookupEngine(address, &engine)) {
        log_warning("NV2A::ReadEngine:  Unmapped engine read!  addr = 0x%x,  size = %u\n", address, size);
        *value = 0;
    }
    else if (engine->IsEnabled()) {
        engine->Read(address - engine->GetParams().mmioRange.base, value, size);
    }
    else {
        *value = 0;
    }
}

void NV2A::ReadVRAM(uint32_t address, uint32_t *value, uint8_t size) {
    // Map to system RAM
    if (address + size <= m_vramSize) {
        switch (size) {
        case 1: *value = m_vram[address]; break;
        case 2: *value = *(uint16_t*)&m_vram[address]; break;
        case 4: *value = *(uint32_t*)&m_vram[address]; break;
        }
    }
    else {
        *value = 0;
    }
}

void NV2A::WriteEngine(uint32_t address, uint32_t value, uint8_t size) {
    INV2AEngine *engine;
    if (!LookupEngine(address, &engine)) {
        log_warning("NV2A::WriteEngine:  Unmapped engine write!  addr = 0x%x,  size = %u,  value = 0x%x\n", address, size, value);
    }
    else if (engine->IsEnabled()) {
        engine->Write(address - engine->GetParams().mmioRange.base, value, size);
    }
}

void NV2A::WriteVRAM(uint32_t address, uint32_t value, uint8_t size) {
    // Map to system RAM
    if (address + size <= m_vramSize) {
        switch (size) {
        case 1: m_vram[address] = value; break;
        case 2: *(uint16_t*)&m_vram[address] = value; break;
        case 4: *(uint32_t*)&m_vram[address] = value; break;
        }
    }
}

void NV2A::RegisterEngine(INV2AEngine *engine) {
    m_engines[engine->GetParams().mmioRange.base] = engine;
}

bool NV2A::LookupEngine(uint32_t addr, INV2AEngine **engine) {
    auto p = m_engines.upper_bound(addr);

    // p->first > addr
    if (p == m_engines.begin()) {
        return false;
    }

    // p->first <= addr
    --p;

    if (p->second->GetParams().mmioRange.InRange(addr)) {
        *engine = p->second;
        return true;
    }

    return false;
}

}
}
}
