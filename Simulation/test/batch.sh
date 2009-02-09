#!/bin/bash

ver="v2"
cmssw_ver="CMSSW_2_2_3"
hscp_tag="HEAD"
job=$1

echo "Stopped HSCP sim"
echo "Job              : $job"
echo "Submission       : $ver"
echo "CMSSW version    : $cmssw_ver"
echo "Stopped HSCP tag : $hscp_tag"

# setup scram area
scramv1 p CMSSW $cmssw_ver
cd $cmssw_ver/src
eval `scramv1 ru -sh`

# check out and compile special code
cvs co -d StoppedHSCP/Simulation -r $hscp_tag UserCode/StoppedHSCP/Simulation
source StoppedHSCP/Simulation/patch.sh
scramv1 b

# run job
cmsRun StoppedHSCP/Simulation/test/$job.py >& $job.log

# make output dir
rfmkdir /castor/cern.ch/user/j/jbrooke/hscp/sim_$ver

# copy output to castor
rfcp $job.log /castor/cern.ch/user/j/jbrooke/hscp/sim_$ver/$job.log
rfcp stoppedHSCP.root /castor/cern.ch/user/j/jbrooke/hscp/sim_$ver/$job.root
rfcp stoppedHSCP_histos.root /castor/cern.ch/user/j/jbrooke/hscp/sim_$ver/$job\_histos.root



#END
