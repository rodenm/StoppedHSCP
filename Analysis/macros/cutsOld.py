from ROOT import TCut

# define all cuts in one place
# using Ben's TTree definition

initCut = TCut("LeadingCenJetEnergy>30.")
jetECut = TCut("LeadingCenJetEnergy>50.")
n60Cut = TCut("LeadingCenJetn60<6")
n90Cut = TCut("LeadingCenJetn90>3")
nMuCut = TCut("NoOfMuons==0")
r1Cut = TCut("TimingRightPeak>0.15")
r1Cut = TCut("(TimingFracRightNextRight>0.1)&&TimingFracRightNextRight<0.5)")
peakCut = TCut("(TimingFracInLeader>0.4)&&(TimingFracInLeader<0.7)")
outCut = TCut("(TimingFracInCentralFour>0.90)")
