#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Ntuples.stoppedHSCPTree_MC_2011_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

# change Global Tag
process.GlobalTag.globaltag = 'GR_P_V17::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/data/Run2011A/MinimumBias/RECO/HSCPSD-PromptSkim-v6/0000/FEF8C3F8-58D9-E011-8925-003048678B94.root'
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v6/000/173/692/FE3E0C58-D5CE-E011-97E4-BCAEC518FF91.root'
#'/store/data/Run2011B/MinimumBias/RECO/HSCPSD-PromptSkim-v1/0000/FAA237CA-5BDC-E011-A567-0018F3D09658.root'
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/7CB12B4D-A955-E011-8882-001D09F24691.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/785B1701-AA55-E011-8F68-000423D9997E.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/74BB3103-AA55-E011-8FA4-001617DBD5AC.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/72C75A07-AA55-E011-AC4E-0030487CD7E0.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/7283464C-A955-E011-AEC9-001D09F24600.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/72071D4C-A955-E011-B46F-001D09F24FBA.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/7040A845-A755-E011-952F-001617C3B76E.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/5AFF098C-A655-E011-8AD2-001617C3B79A.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/50E22908-AA55-E011-BE02-0030487CD716.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/409B637E-A655-E011-A7BA-0016177CA778.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/3A6B0952-A955-E011-90B3-001D09F2514F.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/30F9211E-A555-E011-B4C7-003048D2BCA2.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/22B87901-AA55-E011-BB67-0030487A3232.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/20655205-AA55-E011-A4A8-001617C3B6C6.root'
    #    'file:HSCP.root'
    #    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/CE3FDCA1-4D53-E011-973E-0030487A3DE0.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/C6044534-4F53-E011-BFAA-0030487CD77E.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/BC48F92C-4F53-E011-AB59-0030487CD710.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/BAB9622C-4F53-E011-8BA2-0030487C7E18.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/90E5602C-4F53-E011-8345-00304879EE3E.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/74ED9CF7-4C53-E011-88D8-0030487C5CE2.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/1CA301F9-4C53-E011-8C45-001617E30D52.root',
#        '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/160/853/165FC62B-4F53-E011-A1E6-003048D2C108.root'

        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/E87F802E-4F53-E011-BE87-001617C3B6DE.root',
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/74AC62A9-4D53-E011-8CE4-0030487C635A.root',
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/309B4830-4F53-E011-B5F7-001D09F2441B.root',
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/20250333-4F53-E011-860B-0019B9F70607.root',
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/0609E301-5453-E011-B5E7-0030487CD906.root'
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/497/D404CDF5-5E50-E011-AA95-003048F024FA.root'
    ] );




