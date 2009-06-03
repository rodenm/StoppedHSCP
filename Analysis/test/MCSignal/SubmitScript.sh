#!/bin/sh
#!/bin/bash

ver="v5"
cmssw_ver="CMSSW_2_2_6"
hscp_tag="HEAD"
job=$1

echo "Stopped HSCP Analysis"
echo "Submission       : $ver"
echo "CMSSW version    : $cmssw_ver"
echo "Stopped HSCP tag : $hscp_tag"
echo "Job              : $job.py"
echo

# setup scram area
scramv1 p CMSSW $cmssw_ver
cd $cmssw_ver/src
eval `scramv1 ru -sh`

# check out and compile special code
cvs co -d StoppedHSCP/Analysis -r $hscp_tag UserCode/StoppedHSCP/Analysis
scramv1 b

# make job config
rm FilterMC$MassPoint.py -f
sed "s/MASSPOINT/$MassPoint/g" StoppedHSCP/Analysis/test/MCSignal/FilterTemplate.py > FilterMC$job.py

# run job
cmsRun FilterMC$job.py

# make output dir
rfmkdir /castor/cern.ch/user/j/jbrooke/hscp/ana_$ver

# copy output to castor
rfcp $job.log /castor/cern.ch/user/j/jbrooke/hscp/ana_$ver/$job.log
rfcp GenSimReco\_$job.root /castor/cern.ch/user/j/jbrooke/hscp/ana_$ver/$job.root

#END
