#!/bin/bash
scaleerr=0.11
bkgerr=0.3

for ii in `seq 61`; do
    `awk 'NR=='$ii' {print "export lifetime="$1"\nexport background="$6"\nexport backgroundsigma="$8"\nexport observed="$11}' tmp.txt` 
    echo running lt=$lifetime bkg=$background bkgerr=$backgroundsigma obs=$observed
    root.exe -n -b -q 'runCountingCL95CMS.C('$lifetime' , '$observed' , '$background' , '${backgroundsigma}', '${bkgerr}', '${scaleerr}')'
done
