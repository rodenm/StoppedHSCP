// Objects tracked in Luminosity files
// Format is essentially replicated from one used by CMS LUMI group
// F.Ratnikov, Jul. 23, 2009
#ifndef SHSCP_LUMI_OBJECTS_H
#define SHSCP_LUMI_OBJECTS_H

#include <stdint.h>


namespace shscp {

  struct LumiSectionHeader {
    uint32_t timestamp;
    uint32_t timestamp_micros;
    uint32_t  runNumber;   // Run number
    uint32_t  sectionNumber; // Section number
    uint32_t  startOrbit;  // Start orbit of lumi section
    uint32_t  numOrbits;   // Total number of orbits recorded in lumi section
    uint16_t  numBunches;  // Total number of bunches (from start of orbit)
    uint16_t  numHLXs;     // Number of HLXs in lumi section
    bool bCMSLive;    // Is CMS taking data?
    bool bOC0;        // Was section initialised by an OC0?
  };

  struct LumiSummary {
    float DeadtimeNormalization; 
    float LHCNormalization; // recieved from LHC 

    float InstantLumi;
    float InstantLumiErr;
    int16_t InstantLumiQlty;

    float InstantETLumi;
    float InstantETLumiErr;
    int16_t InstantETLumiQlty;
    float ETNormalization;  // Calculated

    float InstantOccLumi[2];
    float InstantOccLumiErr[2];
    int16_t InstantOccLumiQlty[2];
    float OccNormalization[2];

    float lumiNoise[2];
  };

  const int MAX_BUNCHES = 4096;
  struct LumiDetail {
    float LHCLumi[MAX_BUNCHES]; // Sum of LHC.data over all HLX's
    
    float ETLumi[MAX_BUNCHES];
    float ETLumiErr[MAX_BUNCHES];
    int16_t ETLumiQlty[MAX_BUNCHES];
    float ETBXNormalization[MAX_BUNCHES];

    float OccLumi[2][MAX_BUNCHES];
    float OccLumiErr[2][MAX_BUNCHES];
    int16_t OccLumiQlty[2][MAX_BUNCHES];
    float OccBXNormalization[2][MAX_BUNCHES];
  };
}

#endif
