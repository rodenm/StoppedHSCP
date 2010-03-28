#!/bin/bash

pwd=$PWD

# prompt analysis directory
export CAFDIR=/afs/cern.ch/cms/CAF/CMSCOMM/COMM_TRIGGER/jbrooke/gluinos
export CMSVER=CMSSW_3_5_5

# GRID UI
source /afs/cern.ch/cms/LCG/LCG-2/UI/cms_ui_env.sh

# setup CMSSW environment
cd $CAFDIR/$CMSVER/src
eval `scram ru -sh`
cd $pwd

# CRAB
source /afs/cern.ch/cms/ccs/wm/scripts/Crab/crab.sh

# python
export PYTHONPATH=${PYTHONPATH}:$CAFDIR/$CMSVER/src/StoppedHSCP/Analysis/python:$CAFDIR/$CMSVER/src/StoppedHSCP/Analysis/macros