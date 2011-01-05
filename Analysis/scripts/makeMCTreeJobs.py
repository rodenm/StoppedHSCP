#/usr/bin/env python

import sys

samples=['StoppedGluino200-Neutralino100-38X_v1', \
         'StoppedGluino200-Neutralino150-38X_v1', \
         'StoppedGluino300-Neutralino100-38X_v1', \
         'StoppedGluino300-Neutralino200-38X_v1', \
         'StoppedGluino300-Neutralino250-38X_v1', \
         'StoppedGluino400-Neutralino100-38X_v1', \
         'StoppedGluino400-Neutralino100-38X_v1', \
         'StoppedGluino400-Neutralino300-38X_v1', \
         'StoppedGluino500-Neutralino100-38X_v1', \
         'StoppedGluino500-Neutralino300-38X_v1', \
         'StoppedGluino500-Neutralino400-38X_v1']

ifilepath='/gpfs_phys/storm/cms/user/fedor/'
ofilepath='/users/phjjb/stoppedHSCP/ntuples/MC_38X_v1/'

ifiles=['StoppedGluino200-Neutralino100-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_QV9.root', \
        'StoppedGluino200-Neutralino150-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_3Ve.root', \
        'StoppedGluino300-Neutralino100-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_efq.root', \
        'StoppedGluino300-Neutralino200-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_Fxw.root', \
        'StoppedGluino300-Neutralino250-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_FSG.root', \
        'StoppedGluino400-Neutralino100-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_69V.root', \
        'StoppedGluino400-Neutralino200-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_kV6.root', \
        'StoppedGluino400-Neutralino300-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_V8M.root', \
        'StoppedGluino500-Neutralino100-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_ytM.root', \
        'StoppedGluino500-Neutralino300-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_w0R.root', \
        'StoppedGluino500-Neutralino400-38X_v1/RECO-384-v1-replica1/fb4282659c5d554e4ca05ce12589eef6/stage2_reco_1_1_OYc.root']


script = open("tree_mc.sh", "w")
script.write("#!/bin/bash\n")

for (sample, file) in zip(samples, ifiles):
    string = "import FWCore.ParameterSet.Config as cms \n\
from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import * \n\
process.MessageLogger.cerr.threshold = '' \n\
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 \n\
process.GlobalTag.globaltag = 'START38_V13::All' # MC \n\
process.gctDigis.inputLabel = 'rawDataCollector' \n\
process.gtDigis.DaqGtInputTag = 'rawDataCollector' \n\
process.hcalDigis.InputLabel = 'rawDataCollector' \n\
process.ntuple.remove(process.hltHighLevel) \n\
process.maxEvents.input = cms.untracked.int32(-1) \n\
process.source.fileNames = cms.untracked.vstring('file:"+ifilepath+file+"') \n\
process.TFileService.fileName = cms.string('"+ofilepath+"stoppedHSCPTree_"+sample+".root')"

    cfgfile = open("tree_"+sample+".py", "w")
    cfgfile.write(string)
    cfgfile.close()
    script.write("cmsRun tree_"+sample+".py >& tree_"+sample+".log \n")

script.close()



