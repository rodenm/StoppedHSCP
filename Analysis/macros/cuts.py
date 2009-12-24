from ROOT import TCut

# define all cuts in one place
# using new TTree definition

class Cuts:
    init = TCut("jets[0].e>30.")
    jetE = TCut("jets[0].e>50.")
    n60 = TCut("jets[0].n60<6")
    n90 = TCut("jets[0].n90>3")
    nMu = TCut("nMuon==0")
    r1 = TCut("")
    r2 = TCut("")
    rpeak = TCut("")
    rout = TCut("")


# using old TTree definition

class CutsOld:
    init = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5")
    jetE = TCut("LeadingCenJetEnergy>50.")
    n60 = TCut("LeadingCenJetn60<6")
    n90 = TCut("LeadingCenJetn90>3")
    nMu = TCut("NoOfMuons==0")
    r1 = TCut("TimingRightPeak>0.15")
    r2 = TCut("TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5")
    rpeak = TCut("TimingFracInLeader>0.4 && TimingFracInLeader<0.7")
    rout = TCut("TimingFracInCentralFour>0.90")
    nMinusOneJetE = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetn60<6 && LeadingCenJetn90>3 && NoOfMuons==0")
    nMinusOneN60 = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetEnergy>50. && LeadingCenJetn90>3 && NoOfMuons==0")
    
    nMinusOneN90 = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetEnergy>50. && LeadingCenJetn60<6 && NoOfMuons==0")
    
    nMinusOneNMu = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetEnergy>50. && LeadingCenJetn60<6 && LeadingCenJetn90>3")

    jetMu = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetEnergy>50. && LeadingCenJetn60<6 && LeadingCenJetn90>3 && NoOfMuons==0")

    all = TCut("LeadingCenJetEnergy>30. && nTowerSameiPhi<5 && LeadingCenJetEnergy>50. && LeadingCenJetn60<6 && LeadingCenJetn90>3 && NoOfMuons==0 && TimingRightPeak>0.15 && TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5 && TimingFracInLeader>0.4 && TimingFracInLeader<0.7 && TimingFracInCentralFour>0.90")

