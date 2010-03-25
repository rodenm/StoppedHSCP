from ROOT import TCut

# define all cuts in one place
# using new TTree definition


class CutCollection:
#    self.cuts_=[]
#    self.labels_=['']
    # initialise from lists of strings
    def __init__(self, cuts, labels=[]):
        self.cuts_=[]
        self.labels_=[]
        for i in range(0, len(cuts)):
            self.cuts_.append(TCut(cuts[i]))
        self.labels_=labels
    def __getitem__(self, i):
        return self.cuts_[i]
    def __str__(self):
        return str(self.allCuts().Print())
    def size(self):
        return len(self.cuts_)
    def append(self, cut):
        self.cuts_.append(TCut(cut))
    def cut(self, i):
        return self.cuts_[i]
    def nMinusOneCuts(self, n):
        tmp = TCut('')
        for i in range(0,len(self.cuts_)):
            if (i!=n):
                tmp+=self.cuts_[i]
        return tmp
    def allCuts(self):
        tmp = TCut('')
        for i in range(0,len(self.cuts_)):
            tmp+=self.cuts_[i]
        return tmp
    def dump(self):
        for i in range(0,len(self.cuts_)):
            print "Cut "+str(i)+" : "+self.cuts_[i]
        print
    

newcuts = CutCollection(["nTowerSameiPhi<5", \
                         "jets[0].e>30.", \
                         "jets[0].e>50.", \
                         "jets[0].n60<6", \
                         "jets[0].n90>3", \
                         "nMuon==0", \
                         "TimingRightPeak>0.15", \
                         "TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5", \
                         "TimingFracInLeader>0.4 && TimingFracInLeader<0.7", \
                         "TimingFracInCentralFour>0.90"])

newcuts.jetMu = newcuts[0]
newcuts.jetMu += newcuts[1]
newcuts.jetMu += newcuts[2]
newcuts.jetMu += newcuts[3]
newcuts.jetMu += newcuts[4]
newcuts.jetMu += newcuts[5]


newjmcuts = CutCollection(["nTowerSameiPhi<5", \
                           "jets[0].e>30.", \
                           "jets[0].e>50.", \
                           "jets[0].n60<6", \
                           "jets[0].n90>3", \
                           "nMuon==0"])

oldcuts = CutCollection(["nTowerSameiPhi<5", \
                         "LeadingCenJetEnergy>30.", \
                         "LeadingCenJetEnergy>50.", \
                         "LeadingCenJetn60<6", \
                         "LeadingCenJetn90>3", \
                         "NoOfMuons==0", \
                         "TimingRightPeak>0.15", \
                         "TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5", \
                         "TimingFracInLeader>0.4 && TimingFracInLeader<0.7", \
                         "TimingFracInCentralFour>0.90"])

oldcuts.jetMu = oldcuts[0]
oldcuts.jetMu += oldcuts[1]
oldcuts.jetMu += oldcuts[2]
oldcuts.jetMu += oldcuts[3]
oldcuts.jetMu += oldcuts[4]
oldcuts.jetMu += oldcuts[5]


oldjmcuts = CutCollection(["nTowerSameiPhi<5", \
                           "LeadingCenJetEnergy>30.", \
                           "LeadingCenJetEnergy>50.", \
                           "LeadingCenJetn60<6", \
                           "LeadingCenJetn90>3", \
                           "NoOfMuons==0"])

timingcuts = CutCollection(["TimingRightPeak>0.15", \
                            "TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5", \
                            "TimingFracInLeader>0.4 && TimingFracInLeader<0.7", \
                            "TimingFracInCentralFour>0.90"])

#class Cuts:
#    init = "jets[0].e>30. && nTowerSameiPhi<5"
#    jetE = "jets[0].e>50."
#    n60 = "jets[0].n60<6"
#    n90 = "jets[0].n90>3"
#    nMu = "nMuon==0"
#    r1 = "TimingRightPeak>0.15"
#    r2 = "TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5"
#    rpeak = "TimingFracInLeader>0.4 && TimingFracInLeader<0.7"
#    rout = "TimingFracInCentralFour>0.90"
#    nMinusOneJetE = init+" && "+n60+" && "+n90+" && "+nMu
#    nMinusOneN60 = init+" && "+jetE+" && "+n90+" && "+nMu
#    nMinusOneN90 = init+" && "+jetE+" && "+n60+" && "+nMu
#    nMinusOneNMu = init+" && "+jetE+" && "+n60+" && "+n90
#    jetMu = init+" && "+jetE+" && "+n60+" && "+n90+" && "+nMu
#    all = init+" && "+jetE+" && "+n60+" && "+n90+" && "+nMu+" && "+r1+" && "+r2+" && "+rpeak+" && "+rout

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

    all = TCut("NCaloTowersInTopHPD<5 && LeadingCenJetEnergy>50. && LeadingCenJetn60<6 && LeadingCenJetn90>3 && NoOfMuons==0 && TimingRightPeak>0.15 && TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5 && TimingFracInLeader>0.4 && TimingFracInLeader<0.7 && TimingFracInCentralFour>0.90")

