#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

#process.MessageLogger.cerr.threshold = ''
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.stoppedHSCPTree.hltPath = cms.untracked.string("HLT_*")

process.stoppedHSCPTree.isMC = cms.untracked.bool(True)

# change Global Tag
process.GlobalTag.globaltag = 'GR10_P_V12::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/776/647CDCF1-4A38-E011-B00D-0015C5FDE067.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/776/4ADD94F6-2838-E011-8AD4-003048F1C832.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/775/EE79022F-2438-E011-B8CC-0030487CD7EA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/775/ECDF2998-2038-E011-BF32-001617E30E2C.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/775/50B86497-2738-E011-90A0-001D09F2AF1E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/774/8A360B0C-1D38-E011-A9D1-003048F118D4.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/774/4AA88586-1E38-E011-AD4C-001D09F2432B.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/FC618EB2-E737-E011-90E2-001D09F2423B.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/EE134B86-EA37-E011-B342-0030487CD17C.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/E88D1A5B-E637-E011-93C5-0030487BC68E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/DCBFED74-F637-E011-8FDC-0030487CF41E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/D00B9918-0338-E011-891E-001D09F24FEC.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/CEB88D51-0738-E011-96DC-001D09F297EF.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/CC45C4AA-F137-E011-8D4C-003048F118AC.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/CA247237-E437-E011-B5C0-003048F1110E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/B85B6B12-F537-E011-A73D-0030487CD840.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/B29B3505-E037-E011-8666-0030487CD77E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/B249239E-1438-E011-A6A3-0030487A3C92.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/B0B08FA7-F337-E011-A2C2-0030487CD184.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/AAC47AED-EB37-E011-A413-001D09F25460.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/8CFECFD0-0A38-E011-B255-0030487C6062.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/6C7484BF-EE37-E011-BF3D-0030487CD14E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/60DE7034-0C38-E011-A548-003048D37538.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/56A3C3E1-DD37-E011-A00A-001D09F251CC.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/520FDD5A-1538-E011-BC6D-0030487CAF5E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/36A1B597-F837-E011-B18F-001617E30D40.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/3296C66B-E137-E011-A9AA-0030487CD178.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/30F1BC04-0838-E011-92FD-0030487CD17C.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/3059A184-0438-E011-9AAF-0030487BC68E.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/28794462-0238-E011-9B78-0030487C2B86.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/28055020-1138-E011-8C85-001D09F24498.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/26A01976-EF37-E011-A1B4-0030487C5CFA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/2207ED9E-E537-E011-B990-001D09F24399.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/1EA21C9B-FF37-E011-956B-001617E30CC8.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/1E9E54DD-FC37-E011-B3AC-001D09F2512C.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/166D1152-0E38-E011-AF8D-001D09F252DA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/16429EEB-FE37-E011-AE3F-0030487C5CFA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/0470856D-1038-E011-B973-001D09F23174.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/773/00191062-FB37-E011-999F-0030487C6A66.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/770/9C9CC9D2-D437-E011-AB62-00304879BAB2.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/769/A4AE2144-D837-E011-A2C7-001D09F291D7.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/769/98D4E2E2-D637-E011-B66F-003048F118DE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/769/84F11C05-E037-E011-AB4E-0030487CD812.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/769/6CCE90E2-DD37-E011-8A40-0030487CD6DA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/FA3D66EC-B537-E011-8164-001D09F24691.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/EE9708BE-C637-E011-8FEA-003048F024DE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/DACB1C24-C837-E011-B3C7-001D09F23A20.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/C628D368-C037-E011-B5CB-001D09F29533.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/B834D2DA-BA37-E011-97FF-0030487A1990.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/B4A192CB-CD37-E011-8546-003048F118DE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/A6057E50-B737-E011-B04F-003048D374F2.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/A287C428-CF37-E011-A8FE-001D09F254CE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/9EA17BDD-CF37-E011-87F6-003048F118DE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/9A0566E0-C837-E011-B210-001D09F29533.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/96484CAA-D937-E011-B926-0030487A1990.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/92B07496-B637-E011-9944-0030487CD178.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/90291918-BA37-E011-942E-001D09F25217.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/900DFB5D-CC37-E011-9561-0015C5FDE067.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/7ED5ADBB-BF37-E011-81D2-003048F1BF66.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/6209CCEF-C337-E011-9B63-003048678098.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/5CABF943-D837-E011-BFE2-001D09F252DA.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/4404E5EA-C337-E011-93E6-001D09F251FE.root',
        '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/741/282C5B34-BC37-E011-AF61-001D09F24D67.root',
        ## '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/735/A4A3D8E9-AE37-E011-808C-0030487CD812.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/735/947807F9-B037-E011-AABC-003048F11C5C.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/735/78DF1AEB-B537-E011-ABFB-001D09F29114.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/735/3A399810-AC37-E011-A655-001D09F253D4.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/735/06FA3133-AE37-E011-B383-001617E30CE8.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/734/E67E51B2-AA37-E011-98B5-001D09F2B30B.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/734/68AF0AFE-A237-E011-8BD0-001D09F24682.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/734/0CB36A5E-A437-E011-9642-0030487C6090.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/729/DA7709D1-A037-E011-A28E-001D09F2423B.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/726/B8CFAF54-9637-E011-B7EA-001617E30F48.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/726/90A08397-9A37-E011-8E71-0019B9F72BFF.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/726/4A204BEC-9437-E011-9113-001D09F251D1.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/726/326C2A20-9937-E011-8DA3-003048F118C6.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/726/24D1E351-9D37-E011-8B5B-001D09F24600.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/724/FE8A4173-8A37-E011-8427-003048678098.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/723/8CA76AD5-8B37-E011-A736-000423D9890C.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/723/767BFF96-9537-E011-844E-001D09F24399.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/723/4063B095-8E37-E011-AB8A-0019B9F709A4.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/723/3C9E00B2-9037-E011-87CD-0030487A1884.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/723/24B88B07-9037-E011-B54C-001D09F2905B.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/720/EE7293DE-8637-E011-9099-001D09F2532F.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/720/8A3882E7-8237-E011-A49B-001D09F2525D.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/720/82C526CE-8B37-E011-BF42-0030487CD7E0.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/720/7A215837-8437-E011-8D92-003048F11C28.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/718/68913F89-8337-E011-B8E1-0030487CD13A.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/718/08099AF9-8237-E011-8A7F-001D09F24DDF.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/718/049D44C9-7D37-E011-B7B7-001D09F297EF.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/711/E8485B4E-7537-E011-B414-003048F1C424.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/711/B64E50D7-7837-E011-8D0A-001D09F24399.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/711/586999C4-8037-E011-8005-001D09F29524.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/711/2AA78D4E-7537-E011-9271-003048F118AC.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/711/04C426D4-7837-E011-9AA8-001D09F28F11.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/707/BAD67AFD-6E37-E011-89C9-003048F11C5C.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/707/6C198317-7137-E011-AAF2-003048D2C0F0.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/707/5011484F-7537-E011-AE77-001D09F26509.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/F06E6EEC-8B37-E011-B0B3-0030487C6062.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/E87AEFF1-6037-E011-AD21-001D09F2B2CF.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/E6B9350A-5C37-E011-A059-001D09F2512C.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/BE4E43EC-8B37-E011-B445-001D09F28F1B.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/B8BEFAA9-6137-E011-A497-001D09F2AD4D.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/AE39E013-6A37-E011-A0F3-001D09F23C73.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/9A7CC282-5D37-E011-B03F-0019B9F705A3.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/9670B04F-6737-E011-AE68-0030487CD180.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/78C56C27-6537-E011-9D2C-0030487CD6E8.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/705/5A7EAB78-5D37-E011-B86A-003048D2C1C4.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/E02CEEE8-5737-E011-B612-001D09F2525D.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/AC04BA95-4537-E011-ACC9-0030486733B4.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/94E45A1A-4937-E011-822C-003048D2C0F0.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/6A8310FE-3F37-E011-AEE1-003048F11C5C.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/64A5D428-4437-E011-8F19-003048F024DC.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/5EC141C8-4937-E011-9B6A-003048678098.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/549398FA-4D37-E011-93D8-001D09F29169.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/4CD49F89-5137-E011-9A8E-0030487CD6DA.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/4846B17C-4337-E011-B063-003048D2BB58.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/46AD9C87-5137-E011-8F65-0030487CD13A.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/3A91E2E7-4B37-E011-9E87-003048F1182E.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/38B5AC3F-3F37-E011-89A9-003048F117B4.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/24DD6C9D-5337-E011-A6C4-001D09F253FC.root',
##         '/store/data/Commissioning11/Cosmics/RECO/PromptReco-v1/000/157/700/2216F0B0-4E37-E011-8C01-003048F118C4.root'
        
    ] );




