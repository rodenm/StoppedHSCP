#/usr/bin/env python

import sys

ifilepath='/data/sdd1/phjjb/stoppedHSCP_MC/'
ofilepath='/data/sdd1/phjjb/stoppedHSCP/stoppedHSCP_tree_MC_361/'

files=['StoppedGluino200-Neutralino100-v2_1.root', \
       'StoppedGluino200-Neutralino150-v2_1.root', \
       'StoppedGluino300-Neutralino100-v2_1.root', \
       'StoppedGluino300-Neutralino200-v2_1.root', \
       'StoppedGluino300-Neutralino250-v2_1.root', \
       'StoppedGluino400-Neutralino100-v2_1.root', \
       'StoppedGluino400-Neutralino300-v2_1.root', \
       'StoppedGluino500-Neutralino300-v2_1.root', \
       'StoppedGluino500-Neutralino400-v2_1.root', \
       'StoppedGluino600-Neutralino300-v2_1.root', \
       'StoppedGluino600-Neutralino500-v2_1.root' ]

script = open("tree_mc_361.sh", "w")
script.write("#!/bin/bash\n")

for file in files:
    string = "import FWCore.ParameterSet.Config as cms \n\
from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import * \n\
process.MessageLogger.cerr.threshold = '' \n\
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 \n\
process.GlobalTag.globaltag = 'START36_V9::All' # MC \n\
process.gctDigis.inputLabel = 'rawDataCollector' \n\
process.gtDigis.DaqGtInputTag = 'rawDataCollector' \n\
process.hcalDigis.InputLabel = 'rawDataCollector' \n\
process.myPath.remove(process.hltHighLevel) \n\
process.maxEvents.input = cms.untracked.int32(-1) \n\
process.source.fileNames = cms.untracked.vstring('file:"+ifilepath+file+".root') \n\
process.TFileService.fileName = cms.string('"+ofilepath+"stoppedHSCPTree_"+file+".root')"

    cfgfile = open("tree_"+file+".py", "w")
    cfgfile.write(string)
    cfgfile.close()
    script.write("cmsRun tree_"+file+".py >& tree_"+file+".log \n")

script.close()



