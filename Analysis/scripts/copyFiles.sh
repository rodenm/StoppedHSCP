#!/bin/bash

# copy files from grid location to local disk

label=$1
nfiles=$2
first=$3
crab=$4

griddir=srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN=/pnfs/pp.rl.ac.uk/data/cms/store/user/jbrooke/$label
odir=/data/sdd1/phjjb/stoppedHSCP/$label
filebase=stoppedHSCPTree

echo "Copying files from $griddir to $odir"

if [ ! -d $odir ]; then
    mkdir $odir
fi

for i in $(seq $first 1 $nfiles)
do
  echo "lcg-cp $griddir/${filebase}_${i}_${crab}.root $odir/${filebase}_$i.root"
  lcg-cp $griddir/$filebase\_$i\_$crab.root $odir/$filebase\_$i.root
done

