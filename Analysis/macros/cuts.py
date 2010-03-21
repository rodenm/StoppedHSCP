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

newcuts.jetMu = newcuts[0] and newcuts[1] and newcuts[2] and newcuts[3] and newcuts[4] and newcuts[5]

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

oldcuts.jetMu = oldcuts[0] and oldcuts[1] and oldcuts[2] and oldcuts[3] and oldcuts[4] and oldcuts[5]

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

