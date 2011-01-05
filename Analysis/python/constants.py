
# constants
lumiBlockLength = 25.e-9 * 3564. * pow(2., 18)

# cuts
nCuts    = 16
iJet50   = 8
in90     = 10
iCT      = 11
iAllCuts = 15



### Numbers derived from control sample ###

# final rate
#ctrlFinRate       = 5.54884e-05
ctrlFinRate        = 5.09013e-05  # leading iphi fraction test
#ctrlFinRate        = 5.37292e-05  # tiziano test

# stat error on final rate (relative)
#errCtrlFinRate    = 0.229416
errCtrlFinRate    = 0.235702  # leading iphi fraction test
#errCtrlFinRate    = 0.229416  # tiziano test

# CT N-1 rate
#ctrlCTNM1Rate    = 0.00136677
ctrlCTNM1Rate    = 0.00134606  # leading iphi fraction test
#ctrlCTNM1Rate    = 0.00134606  # tiziano test

# stat error on CT N-1 rate (relative)
#errCtrlCTNM1Rate = 0.046225
errCtrlCTNM1Rate = 0.0458349  # leading iphi fraction test
#errCtrlCTNM1Rate = 0.0458349  # tiziano test

# N90 N-1 rate
#ctrlN90NM1Rate     = 0.00193917
ctrlN90NM1Rate     = 0.0002234  # leading iphi fraction test
#ctrlN90NM1Rate     = 0.0019399  # tiziano test

# stat error on N90 N-1 rate (relative)
#errCtrlN90NM1Rate  = 0.0388075
errCtrlN90NM1Rate  = 0.112509   # leading iphi test
#errCtrlN90NM1Rate  = 0.0381802   # tiziano test

# rate coefficients
rateCoeffN90      = ctrlFinRate/ctrlN90NM1Rate
rateCoeffCT       = ctrlFinRate/ctrlCTNM1Rate

# dn90/dCT syst error (relative)
errSystRateCoeff  = 0.10691
