# script to run entire analysis for a particular dataset

# get options
if [ $# -eq 2 ]
then
    dataset=$2
    flag=$1
else
    dataset=$1
    flag=""
fi

# default variables
ntuple=ntuples/stoppedHSCP_tree_$dataset.root
runs=0
CRAFTopt=""
doRuns=""
doPrint="-p"
mc=""

# option-dependent variables
if [[ $flag != *r* ]]
then
    doRuns="-r"
fi

# dataset dependent variables
if [[ "$dataset" =~ Coll10\_Run2010A\_* ]]
then
    runs=136294,136297
fi

if [[ "$dataset" =~ Coll10\_Run2010A\_May27th\_* ]]
then
    runs=136087,136088
fi

if [[ "$dataset" =~ Coll10\_May6th\_* ]]
then
    runs=133320,133321,133446,133448,133450,133474,133483,133874,133875,133877,133881,133885,133927,133928
#133324,133336,133463,133472,133509,133510,133511,133876
fi

if [[ "$dataset" =~ Coll10\_Promptv9\_* ]]
then
    runs=133874,133875,133876,133877,133881,133885
fi

if [[ "$dataset" =~ Coll10\_Promptv8\_* ]]
then
    runs=133320,133321,133446,133448,133450,133474,133483
fi

if [[ "$dataset" =~ Coll10\_Promptv3\_* ]]
then
    runs=128074,128094,128096,128097,128101,128291,128292,128293,128294,128295,128296,128298,128740,128741,128743,128744,128745,128746,128747,128749,128750,128752,128753,128755,128757,128762,128764,128765,128766,128891,129196,129316,129319,129320,129321,129393,129398,129407,130231,130239,130242,130244,130252,130258,130747,130751,130767,130768,130771,130772,130777,130787,130792,131065,131297,131300,131420,131626,132033,132202,132226,132348,132349,132361,132362,132365,132366,132562,132563,132589,132592,132916,132922
fi

if [[ "$dataset" =~ Coll09\_* ]]
then
    runs=124022,124023,124024,124025,124026,124027,124029,124030,124108,124112,124115,124119,124120,124228,124229,124230,124275
fi

if [[ "$dataset" =~ CRAFT09\_* ]]
then
    runs=110958,110972,110987,110998,111009,111039
    CRAFTopt="-c"
fi

# need a better way to deal with MC...
if [[ "$dataset" =~ MC_May6th_300_100_v1 ]]
then
    ntuple="ntuples/stoppedHSCP_tree_MC_May6th/stoppedHSCPTree_May6th_gluino_1jet_336_300_100_2.root"
    doRuns=""
    doPrint=""
    mc="MC"
fi

# run analysis
echo "Runlist  : $runs"
echo "Log file : $dataset.log"

# if not 'quick' flag, make histograms
if [[ $flag != *q* ]]
then
    echo "Making histograms from ntuples/stoppedHSCP_tree_$dataset.root"
    ./makeHistograms $doPrint $ntuple $dataset
fi

# make plots
echo "Making plots"
python macros/makePlots.py $doRuns $dataset/histograms.root $runs

if [[ $mc == "" ]]
then
    python macros/sumRuns.py $dataset $runs
    python macros/makePlots.py $dataset/selectedRuns.root
    python macros/makePlotsByRun.py $CRAFTopt $dataset $runs
fi

# tarball
echo "Making tarball"
tar -czvf $dataset.tgz $dataset/*
cp $dataset.tgz /users/phjjb/stoppedHSCP/.

echo "Done"
