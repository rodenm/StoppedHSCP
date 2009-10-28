#include "CutCollection.C"

class MuonCut : public CutCollection
{
public:
  MuonCut();
};


MuonCut::MuonCut()
{
  std::vector<TCut> Cuts;
  std::vector<string> Names;

  AddCut("Energy","LeadingCenJetEnergy>30");
  AddCut("Muon","NoOfMuons>0");
}

  
