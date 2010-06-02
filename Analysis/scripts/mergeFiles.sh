#!/bin/bash

# hadd a bunch of files together
# and copy output somewhere

label=$1
nfiles=$2
first=$3

idir=/data/sdd1/phjjb/stoppedHSCP
odir=~/stoppedHSCP/ntuples
filebase=stoppedHSCPTree

# remove old output
if [ -e $idir/$label/$label.root ]
    then rm $idir/$label/$label.root
fi

# make list of files
files=""
for ((i=first;i<=nfiles;i+=1)); do
  file="$idir/${filebase}_$i.root"
  files="${files} $file"
done

# merge them
echo "hadd $idir/$label/$label.root $files"
hadd -f $idir/$label/$label.root $idir/$label/*.root

# copy merged file to ntuples dir
echo "cp $idir/$label/$label.root $odir/$label.root"
cp $idir/$label/$label.root $odir/$label.root
