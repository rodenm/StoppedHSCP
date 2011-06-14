#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_RECO_2011_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

# change Global Tag
process.GlobalTag.globaltag = 'GR_P_V17::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    #'file:/tmp/jbrooke/SD_HSCP_2011.root'
    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v2/000/163/302/C205190F-646F-E011-840D-0019DB2F3F9A.root'
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v2/000/162/826/0211C136-8B69-E011-82D8-001D09F251BD.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/224/343051B9-B756-E011-A0D5-001D09F2512C.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/EC327C19-AE56-E011-8F3C-003048F118DE.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/D419650E-BB56-E011-802A-003048F11DE2.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/C2CA0659-BC56-E011-AEF0-001617DBD316.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/B8176219-AE56-E011-871E-003048F118C4.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/4E9E4519-AE56-E011-BA26-003048F118D2.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/222/3A9E33D0-AE56-E011-9DF1-001617C3B778.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/EEEE5DF8-6656-E011-BF30-003048F11C5C.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/C8BF839F-6C56-E011-9402-001D09F24664.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/B65BB2D8-6B56-E011-9BD8-0016177CA778.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/92EFDE9A-6C56-E011-AF96-001D09F29524.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/88E71E5D-6856-E011-A3CC-001617E30D4A.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/848682A0-6756-E011-9AA7-001617E30D00.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/6C0AFA9E-6C56-E011-AB7E-001D09F28F0C.root',
    #'/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/216/44498CA0-6C56-E011-9C60-001D09F28755.root'
   # 
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/F075D60E-AA55-E011-B704-0030487CD6DA.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/EE2FEB4C-A955-E011-8A94-001D09F2983F.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/DEBD5509-AA55-E011-B110-001617E30D0A.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/DE9BB78B-A655-E011-AAFA-001617E30D40.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/D88924B5-AA55-E011-8EA6-001D09F2983F.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/D6D28CE5-A755-E011-A43B-001D09F25401.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/D64C90D3-AA55-E011-ACE1-003048F118D4.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/C495A302-AA55-E011-8482-001617C3B76E.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/B65CA449-A955-E011-9DB0-001D09F29321.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/A6E97D01-AA55-E011-A0CD-0030487A18F2.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/A0E50FB5-AA55-E011-B963-001D09F24600.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/942C8E8C-A655-E011-8C3D-001D09F24047.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/8666BE3E-A755-E011-826E-001617C3B710.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/84A8214E-A955-E011-A34A-001D09F2910A.root',
#    '/store/data/Run2011A/MinimumBias/RECO/PromptReco-v1/000/161/016/826A9E01-AA55-E011-BD5C-0030487CD718.root',
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




