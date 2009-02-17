
import FWCore.ParameterSet.Config as cms

from HLTrigger.HLTfilters.hltHighLevel_cfi import hltHighLevel as rHadronHLTPath

rHadronHLTPath.HLTPaths = cms.vstring( "HLTStoppedHSCPPath" )
