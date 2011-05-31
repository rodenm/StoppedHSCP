
from math import *

# constants
TIME_PER_BX       = 25.e-9
BX_PER_ORBIT      = 3564
ORBIT_PER_LS      = pow(2., 18)
TIME_PER_LS       = TIME_PER_BX * BX_PER_ORBIT * ORBIT_PER_LS
lumiBlockLength   = TIME_PER_LS

# cuts
nCuts    = 16
iJet50   = 8
in90     = 10
iCT      = 11
iAllCuts = 15

# systematics
errSystRateCoeff  = 0.10691  # dn90/dCT syst error (relative)
scaleUncert       = 0.13     # combined JES, lumi systematic

# control sample counts for BG estimation

#N_ctrl          = 46    # 2010 values
#N_n90_ctrl      = 202
#N_ct_ctrl       = 1216

N_ctrl          = 29    # from Run2010A_Apr21_423p2_v4_1117_1309
N_n90_ctrl      = 257
N_ct_ctrl       = 1982

# errors (fractional)
N_ctrl_stat     = 1/sqrt(N_ctrl)
N_n90_ctrl_stat = 1/sqrt(N_n90_ctrl)
N_ct_ctrl_stat  = 1/sqrt(N_ct_ctrl)

