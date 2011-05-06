#!/bin/sh

scheme=$1

echo $scheme

# get filling scheme from the web
curl http://lpc.web.cern.ch/lpc/documents/FillPatterns/$scheme.txt > scheme.tmp

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

echo ' ' >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt
echo $scheme >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt
cat beam1.tmp1 >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt
echo ' ' >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt
cat beam2.tmp1 >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt
echo ' ' >> $CMSSW_BASE/src/StoppedHSCP/Analysis/data/fillingSchemes.txt