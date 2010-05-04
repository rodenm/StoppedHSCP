#!/bin/bash

# hadd a bunch of files together
# and copy output somewhere

label=$1

idir=/storage/phjjb/stoppedHSCP
odir=~/stoppedHSCP/ntuples/
filebase=stoppedHSCPTree

# merge them with hadd (remove old output first to avoid duplicating events!)
if [ -e $idir/$label/$label.root ]
    then rm $idir/$label/$label.root
fi

ls -l $idir/$label

echo "hadd $idir/$label/$label.root $idir/$label/*.root"
hadd -f $idir/$label/$label.root $idir/$label/*.root

# copy merged file to ntuples dir
echo "cp $idir/$label/$label.root $dest/$label.root"
cp $idir/$label/$label.root $dest/$label.root
