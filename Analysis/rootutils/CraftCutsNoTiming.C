#include "CutCollection.C"

class CraftCutsNoTiming : public CutCollection
{
public:
  CraftCutsNoTiming();
};


CraftCutsNoTiming::CraftCutsNoTiming()
{
  std::vector<TCut> Cuts;
  std::vector<string> Names;

  AddCut("Eta < 1.3","LeadingCenJetEnergy>30");
  AddCut("n90 > 3","LeadingCenJetn90>3");
  AddCut("n60 < 6","LeadingCenJetn60<6");
  AddCut("Energy > 50","LeadingCenJetEnergy>50");
  AddCut("Muon Veto","NoOfMuons==0");

}

  
