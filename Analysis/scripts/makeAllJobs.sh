#!/bin/bash

# make crab files to generate ntuples for 'standard' datasets

# version
ver=$1

# CRAFT 09
python test/makeTreeJob.py -l CRAFT09 Mar3rd_$ver /Calo/jbrooke-StoppedHSCP_CRAFT09_ReRecoMar3rd_v2-da3d6f8cfae87db28fe3c44ff8e9587c/USER CRAFT09_R_V10::All 110958,110972,110987,110998,111009,111039

# Coll09
python test/makeTreeJob.py Coll09 Mar3rd_$ver /MinimumBias/BeamCommissioning09-Skim_StoppedHSCP-Mar3rdSkim_v2/RAW-RECO GR09_R_35X_V2::All 124022,124023,124024,124025,124026,124027,124029,124030,124108,124112,124115,124119,124120,124228,124229,124230,124275

# Comm10  prompt v3
python test/makeTreeJob.py Comm10 Promptv3_$ver /MinimumBias/fedor-Commissioning10-Skim_StoppedHSCP-v3-v2-482d839efd04af784089d248af792fd3/USER GR10_P_V2::All 0

# Comm10 prompt v4
#python test/makeTreeJob.py Comm10 Promptv3_$ver /MinimumBias/fedor-Commissioning10-Skim_StoppedHSCP-v3-v2-482d839efd04af784089d248af792fd3/USER GR10_P_V2::All 0

# Comm10 prompt v5/v6/v7 ???

# Coll10 prompt v8
python test/makeTreeJob.py -j Coll10 Promptv8_$ver /MinimumBias/Commissioning10-Skim_StoppedHSCP-v8/RAW-RECO GR10_P_V5::All 0

