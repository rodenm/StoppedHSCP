#!/bin/tcsh
set MassPoint=$1
set CurrentDir=`pwd`
set USCORE="_"

cd ~
source NewScratchLogon.csh

cd ../test/Signal

rm FilterMC$MassPoint.py -f

sed "s/MASSPOINT/$MassPoint/g" FilterTemplate.py > FilterMC$MassPoint.py
cmsRun FilterMC$MassPoint.py
rfcp "/tmp/bjones/GenSimReco$USCORE$MassPoint.root" /castor/cern.ch/cms/store/user/bjones/SignalOutputFiles/
#END
