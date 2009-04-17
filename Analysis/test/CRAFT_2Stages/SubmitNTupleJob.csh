#!/bin/tcsh

set RunNum = $1
set NowPath = `pwd`
cd ~
source NewScratchLogon.csh
cd $NowPath


if( -e Craft$RunNum ) then
    rm Craft$RunNum -r
    rfrm $Castor/NTuple2FileSolution$RunNum
endif


rfmkdir $Castor/NTuple2FileSolution$RunNum
rfchmod +777 $Castor/NTuple2FileSolution$RunNum

if( -e crab.cfg ) then
    rm crab.cfg
endif 


sed "s/_RUN_/$RunNum/g" crabtemplate.cfg > crab.cfg
crab -create -submit
