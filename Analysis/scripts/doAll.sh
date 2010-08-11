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
if [[ "$dataset" =~ Run2010A\_Jul16th\_* ]]
then
    runs=139779,139780,139781,139784,139786,139788,139789,139790,139965,139966,139967,139968,139969,139971,139972,139973,139974,139975,139976,139980,140058,140059,140070,140076,140116,140119,140123,140124,140158,140159
fi

if [[ "$dataset" =~ Run2010A\_Promptv6\_* ]]
then    runs=138562,138563,138564,138570,138571,138572,138737,138738,138739,138742,138744,138746,138747,138749,138750,138751,138919,138920,138921,138923,138924,138937,138939,139020,139096,139098,139100,139102,139103,139195,139239,139347,139356,139360,139364,139365,139368,139370,139372,139375,139399,139400,139407,139411,139457,139458,139459
fi

if [[ "$dataset" =~ Run2010A\_Promptv6\_v9b ]]
then
    runs=140160,140180,140181,140182
fi

if [[ "$dataset" =~ Run2010A\_May27th\_* ]]
then
    runs=136035,136066,136080,136082,136087,136088,136097,136098,136100
fi

if [[ "$dataset" =~ Coll10\_May6th\_* ]]
then
    runs=133320,133321,133446,133448,133450,133474,133483,133874,133875,133877,133881,133885,133927,133928
#133324,133336,133463,133472,133509,133510,133511,133876
fi

if [[ "$dataset" =~ Comm10\_May6th\_* ]]
then
    runs=133321,133446,133448,133450,133474,133483,133874,133875,133877,133881,133885,133927,133928
#133320,133321,133446,133448,133450,133474,133483,133874,133875,133877,133881,133885,133927,133928
fi

if [[ "$dataset" =~ Coll10\_Promptv9\_* ]]
then
    runs=133874,133875,133876,133877,133881,133885
fi

if [[ "$dataset" =~ Coll10\_Promptv8\_* ]]
then
    runs=133320,133321,133446,133448,133450,133474,133483
fi

if [[ "$dataset" =~ Comm10\_Promptv3\_* ]]
then
    runs=128074,128094,128096,128097,128101,128291,128292,128293,128294,128295,128296,128298,128740,128741,128743,128744,128745,128746,128747,128749,128750,128752,128753,128755,128757,128762,128764,128765,128766,128891,129196,129316,129319,129320,129321,129393,129398,129407,130231,130239,130242,130244,130252,130258
#,130747,130751,130767,130768,130771,130772,130777,130787,130792,131065,131297,131300,131420,131626,132033,132202,132226,132348,132349,132361,132362,132365,132366,132562,132563,132589,132592,132916,132922
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
    makeHistograms $doPrint $ntuple $dataset
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

# summary
python macros/printSummary $dataset/selectedRuns.root


# tarball
echo "Making tarball"
tar -czvf $dataset.tgz $dataset/*
cp $dataset.tgz /users/phjjb/stoppedHSCP/.

echo "Done"
