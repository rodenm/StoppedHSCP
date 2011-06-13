#!/bin/sh

scheme=$1

# Allow user to specify fillingSchemes file
fillingtext=$CMSSW_BASE/src/StoppedHSCP/Ntuples/data/fillingSchemes.txt

if [ $# -ge 2 ]
then
    fillingtext=$2
fi

echo $scheme
echo $fillingtext

# get filling scheme from the web
curl http://lpc.web.cern.ch/lpc/documents/FillPatterns/$scheme.txt > scheme.tmp
#curl http://lpc-afs.web.cern.ch/lpc-afs/FILLSCHEMES/$scheme.txt > scheme.tmp

# chop out beam 1 bunches
sed -n "/#  BEAM1    BEAM2 slots/{:a;n;/#  BEAM2    BEAM1 slots/b;p;ba}" scheme.tmp > beam1.tmp
sed -n "/#  BEAM2    BEAM1 slots/{:a;n;/#  --- NON COLLIDING BUNCHES (IP1\/5) --------------/b;p;ba}" scheme.tmp > beam2.tmp

# strip hashes
(echo "g/#/d"; echo 'wq') | ex -s beam1.tmp
(echo "g/#/d"; echo 'wq') | ex -s beam2.tmp

awk '{print $1}' < beam1.tmp > beam1.tmp1
awk '{print $1}' < beam2.tmp > beam2.tmp1

perl -pi -e "s,\n,\,," beam1.tmp1
perl -pi -e "s,\n,\,," beam2.tmp1

# Get size of beam files
beam1size=$(stat -c%s "beam1.tmp1")
beam2size=$(stat -c%s "beam2.tmp1")

echo $beam1size $beam2size
# if files are empty, don't write to output file
if  [ $beam1size -eq 0 ] || [ $beam2size -eq 0 ]
then
    echo 'ERROR  beam1.tmp1 size = '$beam1size
    echo '       beam2.tmp1 size = '$beam2size
else
    echo ' ' >> $fillingtext
    echo $scheme >> $fillingtext
    cat beam1.tmp1 >> $fillingtext
    echo ' ' >> $fillingtext
    cat beam2.tmp1 >> $fillingtext
    echo ' ' >> $fillingtext
fi