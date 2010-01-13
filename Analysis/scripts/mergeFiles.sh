#!/bin/bash

label=$1
nfiles=$2
first=$3

remote=srm://lcgse02.phy.bris.ac.uk:8444/cms/store/user/jbrooke/
local=/storage/phjjb/stoppedHSCP
file=stoppedHSCPTree
enddir=~/stoppedHSCP/ntuples/

# copy files to local storage
if [ ! -e $local/$label ]
    then mkdir $local/$label
fi
echo "copy.py $remote/StoppedHSCP_$label $local/$label $file $nfiles $first"
copy.py $remote/StoppedHSCP_$label $local/$label $file $nfiles $first

# merge them with hadd
echo "merge.py $local/$label $file $nfiles $first"
merge.py $local/$label $file $nfiles $first

# copy merged file to ntuples dir
echo "cp $local/$label/$file.root ~/stoppedHSCP/ntuples/$file\_$label.root"
cp $local/$label/$file.root ~/stoppedHSCP/ntuples/$file\_$label.root
