import FWCore.ParameterSet.Config as cms
from SUSYBSMAnalysis.RHadron.rHadronHLTPath_cfi import rHadronHLTPath
from SUSYBSMAnalysis.RHadron.rHadronFilter_cfi  import rHadronFilter

rHadronPath = cms.Path( rHadronHLTPath + rHadronFilter )
