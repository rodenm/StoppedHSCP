#!/bin/bash

label=$1

source=/gpfs_phys/storm/cms/user/jbrooke/
local=/storage/phjjb/stoppedHSCP
file=stoppedHSCPTree
dest=~/stoppedHSCP/ntuples/

# create local storage
if [ ! -e $local/$label ]
    then mkdir $local/$label
fi

# copy files
echo "cp $source/$label/stoppedHSCPTree*.root $local/$label/."
cp $source/$label/stoppedHSCPTree*.root $local/$label/.

# merge them with hadd (remove output first to avoid duplicating events!)
if [ -e $local/$label/$label.root ]
    then rm $local/$label/$label.root
fi

ls -l $local/$label

echo "hadd $local/$label/$label.root $local/$label/*.root"
hadd $local/$label/$label.root $local/$label/*.root

# copy merged file to ntuples dir
echo "cp $local/$label/$label.root $dest/$label.root"
cp $local/$label/$label.root $dest/$label.root
