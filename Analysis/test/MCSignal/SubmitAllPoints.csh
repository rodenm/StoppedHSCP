#!/bin/tcsh

bsub -q 1nd SubmitScript.sh 300_50
bsub -q 1nd SubmitScript.sh 200_50
bsub -q 1nd SubmitScript.sh 200_100
bsub -q 1nd SubmitScript.sh 300_100
bsub -q 1nd SubmitScript.sh 300_200
bsub -q 1nd SubmitScript.sh 500_100
bsub -q 1nd SubmitScript.sh 900_200
bsub -q 1nd SubmitScript.sh 1200_300
