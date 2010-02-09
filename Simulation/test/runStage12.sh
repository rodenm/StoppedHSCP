#!/bin/sh
jobno=$1
option=$2
if [ "$option" = "" ]; then
    option=$SGE_TASK_ID
fi
if [ "$option" = "" ]; then
    option=6
fi
nevents=10000
global_tag="STARTUP3X_V8M::All"
destination_dir="$HOME/scratch/hscp/336/gluino1jet"
tmp_dir="/scratch/hh/lustre/cms/user/ratnikov/tmp"

export CMSSW_SEARCH_PATH=$tmp_dir:$CMSSW_SEARCH_PATH

SCAN_POINTS=gluinoMassPoints.txt

echo Searching decay parameters for option ${option}
`awk '/^'${option}'[\t ]/  {print "export gluino_mass="$2"\nexport neutralino_mass="$3}' $SCAN_POINTS`
if [ "$neutralino_mass" = "" ]; then
  echo Failed to find parameters for option # ${option} in the file $SCAN_POINTS
  exit 1
fi

rhadron_spectra_file="StoppedHSCP/Simulation/data/particles_gluino_${gluino_mass}_GeV.txt" 
if [ ! -s $rhadron_spectra_file ] 
then
    echo "rhadrons spectra file $rhadron_spectra_file does not exists"
    exit 1
fi

postfix=${gluino_mass}_${neutralino_mass}_${jobno}

stopped_points_basename="stopped_rhadrons_gluino_${postfix}.txt"
stopped_points_file="${tmp_dir}/${stopped_points_basename}"
raw_file="${tmp_dir}/RAW_HLT_${postfix}.root"
output_file="${destination_dir}/gluino_1jet_336_${postfix}.root"
fjr_file="${output_file}.xml"

echo =================== Set environment ==================================
echo Working directory `pwd`:
echo 'ls -lt'; ls -lt *
echo Enviroment:
env

echo PY files
#cat *.py


echo ======================================================================
echo begin all at `date`
echo ======================================================================
echo run stage1 ...
echo cmsRun StoppedHSCP/Simulation/test/rhadron_stage1.py nevents=${nevents} gluinoMass=${gluino_mass} stoppedPoints=${stopped_points_file} globalTag=${global_tag} randomize=${jobno}
     cmsRun StoppedHSCP/Simulation/test/rhadron_stage1.py nevents=${nevents} gluinoMass=${gluino_mass} stoppedPoints=${stopped_points_file} globalTag=${global_tag} randomize=${jobno}
if [ ! -s ${stopped_points_file} ]
then
    echo "Failed stage1 step"
    exit 1
fi
nevents=`wc -l ${stopped_points_file} | awk '{print $1}'`
echo "Stage1 produced ${nevents} events"
echo ======================================================================
date
echo run simulation ...
echo cmsRun StoppedHSCP/Simulation/test/rdecay_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.py nevents=$nevents gluinoMass=$gluino_mass neutralinoMass=$neutralino_mass  stoppedPoints=${stopped_points_file} outputFile=$raw_file globalTag=$global_tag  randomize=$jobno
     cmsRun StoppedHSCP/Simulation/test/rdecay_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.py nevents=$nevents gluinoMass=$gluino_mass neutralinoMass=$neutralino_mass  stoppedPoints=${stopped_points_file} outputFile=$raw_file globalTag=$global_tag  randomize=$jobno
echo ======================================================================
date
echo run reconstruction ...
echo cmsRun -j $fjr_file StoppedHSCP/Simulation/test/doRAW2DIGI_RECO.py rawFile=$raw_file recoFile=$output_file globalTag=$global_tag  
echo ======================================================================
     cmsRun -j $fjr_file StoppedHSCP/Simulation/test/doRAW2DIGI_RECO.py rawFile=$raw_file recoFile=$output_file globalTag=$global_tag

exit 0
