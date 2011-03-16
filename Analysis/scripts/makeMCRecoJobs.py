#/usr/bin/env python

import sys

ifilepath='/gpfs_phys/storm/cms/user/fedor/hscp/336/7TeV/gluino1jet/'
ofilepath='/data/sdd1/phjjb/stoppedHSCP/rereco_MC_May6th/rereco_MC_May6th_'

files=['gluino_1jet_336_150_100_2', \
       'gluino_1jet_336_150_100_2',  \
       'gluino_1jet_336_400_300_2',  \
       'gluino_1jet_336_150_50_2',   \
       'gluino_1jet_336_500_100_2',  \
       'gluino_1jet_336_200_100_2',  \
       'gluino_1jet_336_500_200_2',  \
       'gluino_1jet_336_200_150_2',  \
       'gluino_1jet_336_500_400_2',  \
       'gluino_1jet_336_300_100_2',  \
       'gluino_1jet_336_600_300_2',  \
       'gluino_1jet_336_300_200_2',  \
       'gluino_1jet_336_600_500_2',  \
       'gluino_1jet_336_400_100_2',  \
       'gluino_1jet_336_900_800_2',  \
       'gluino_1jet_336_400_200_2']

script = open("rereco_may6th.sh", "w")
script.write("#!/bin/bash\n")

for file in files:
    string = "import FWCore.ParameterSet.Config as cms \n\
from StoppedHSCP.Analysis.rereco_may6th import * \n\
process.MessageLogger.cerr.threshold = '' \n\
process.MessageLogger.cerr.FwkReport.reportEvery = 1000 \n\
process.GlobalTag.globaltag = 'START3X_V27::All' # MC \n\
process.maxEvents.input = cms.untracked.int32(-1) \n\
process.source.fileNames = cms.untracked.vstring('file:"+ifilepath+file+".root') \n\
process.output.fileName = cms.untracked.string('"+ofilepath+file+".root')"

    cfgfile = open("rereco_may6th_"+file+".py", "w")
    cfgfile.write(string)
    cfgfile.close()
    script.write("cmsRun rereco_may6th_"+file+".py >& rereco_may6th_"+file+".log \n")

script.close()



