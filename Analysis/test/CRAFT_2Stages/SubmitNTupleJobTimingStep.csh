#!/bin/tcsh

set RunNum = $1
set NowPath = `pwd`
cd ~
source NewScratchLogon.csh
cd $NowPath


if( -e Craft$RunNum ) then
    rm Craft$RunNum -r
    rfrm -r -f $Castor/NTupleFullCraftTiming$RunNum
endif


rfmkdir $Castor/NTupleFullCraftTiming$RunNum
rfchmod +777 $Castor/NTupleFullCrafTiming$RunNum

if( -e crab.cfg ) then
    rm crab.cfg
endif 


sed "s/_RUN_/$RunNum/g" crabtemplatetimingstep.cfg > crab.cfg
crab -create -submit
