#!/bin/tcsh

set RunNum = $1
set NowPath = `pwd`
cd ~
source NewScratchLogon.csh
cd $NowPath


if( -e Craft$RunNum ) then
    rm Craft$RunNum -r
    rfrm -r $Castor/NTupleSkimCraft$RunNum
endif


rfmkdir $Castor/NTupleSkimCraft$RunNum
rfchmod +777 $Castor/NTupleSkimCraft$RunNum

if( -e crab.cfg ) then
    rm crab.cfg
endif 


sed "s/_RUN_/$RunNum/g" crabtemplate.cfg > crab.cfg
crab -create -submit
