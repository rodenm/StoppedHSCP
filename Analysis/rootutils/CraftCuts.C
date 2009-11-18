#include "CutCollection.C"

class CraftCuts : public CutCollection
{
public:
  CraftCuts();
};


CraftCuts::CraftCuts()
{
  //  std::vector<TCut> Cuts;
  //  std::vector<string> Names;

  AddCut("Eta < 1.3","LeadingCenJetEnergy>30");
  AddCut("n60 < 6","LeadingCenJetn60<6");
  AddCut("n90 > 3","LeadingCenJetn90>3");
  AddCut("Energy > 50","LeadingCenJetEnergy>50");
  AddCut("Muon Veto","NoOfMuons==0");
  AddCut("TExp Ratio","(TimingRightPeak>0.15)&&(TimingFracRightNextRight>0.1)&&(TimingFracRightNextRight<0.5)");
  AddCut("TFracPeak","(TimingFracInLeader>0.4)&&(TimingFracInLeader<0.7)");
  AddCut("TOuterBins","(TimingFracInCentralFour>0.90)");
}

  
