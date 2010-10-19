// Objects tracked in Luminosity files
// Format is essentially replicated from one used by CMS LUMI group
// F.Ratnikov, Jul. 23, 2009
#ifndef SHSCP_LUMI_OBJECTS_H
#define SHSCP_LUMI_OBJECTS_H

#include <stdint.h>
#include <vector>

namespace shscp {

  const int MAX_BUNCHES = 4096;
  
  class LumiFillSummary {
  public:
    uint32_t fillNumber;
    float beamEnergy;
    void setBX (int bx, bool active=true);
    bool activeBX (int bx) const;
    std::vector<int> allActiveBX () const;
  private:
    uint32_t beamStructure[MAX_BUNCHES/32];
  };

  struct LumiRunSummary {
    uint32_t run;
    uint32_t fillIndex;
    uint32_t starttime;
    uint32_t starttime_micros;
  };

  struct LumiSectionSummary {
    uint32_t section;
    uint32_t runIndex;
    float lumi;
    float lumiError;
    float lumiQuality;
    bool cmsAlive;
    uint32_t startOrbit;
    uint32_t numOrbits;
    uint16_t beamStatus;
  };

  struct LumiData {
    std::vector<LumiFillSummary> fills;
    std::vector<LumiRunSummary> runs;
    std::vector<LumiSectionSummary> sections;
  };

  void LumiFillSummary::setBX (int bx, bool active) {
    int offset = bx % 32;
    int index = (bx-offset)/32;
    if (index >= MAX_BUNCHES/32) return;
    uint32_t mask = 1<<offset;
    if (active) beamStructure[index] |= mask;
    else beamStructure[index] &= ~mask;
  }

  bool LumiFillSummary::activeBX (int bx) const {
    int offset = bx % 32;
    int index = (bx-offset)/32;
    if (index >= MAX_BUNCHES/32) return false;
    uint32_t mask = 1<<offset;
    return beamStructure[index] & mask;
  }

  std::vector<int> LumiFillSummary::allActiveBX () const {
    std::vector<int> result;
    for (int index = 0; index < MAX_BUNCHES/32; ++index) {
      for (int offset = 0; offset < 32; ++offset) {
	uint32_t mask = 1<<offset;
	if (beamStructure[index] & mask) result.push_back (index*32+offset);
      }
    }
    return result;
  }
}

#endif
