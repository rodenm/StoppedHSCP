#!/bin/tcsh

set RunNum = $1
set NowPath = `pwd`
cd ~
source NewScratchLogon.csh
cd $NowPath


if( -e Craft$RunNum ) then
    rm Craft$RunNum -r
    rfrm -r -f $Castor/NTupleFullCraft$RunNum
endif


rfmkdir $Castor/NTupleFullCraft$RunNum
rfchmod +777 $Castor/NTupleFullCraft$RunNum

if( -e crab.cfg ) then
    rm crab.cfg
endif 


sed "s/_RUN_/$RunNum/g" crabtemplatenodigis.cfg > crab.cfg
crab -create -submit
