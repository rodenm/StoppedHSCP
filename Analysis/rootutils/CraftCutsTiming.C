#include "CutCollection.C"

class CraftCutsTiming : public CutCollection
{
public:
  CraftCutsTiming();
};


CraftCutsTiming::CraftCutsTiming()
{
  std::vector<TCut> Cuts;
  std::vector<string> Names;


  AddCut("TExp Ratio","(TimingRightPeak>0.15)&&(TimingFracRightNextRight>0.1)&&(TimingFracRightNextRight<0.5)");
  AddCut("TFracPeak","(TimingFracInLeader>0.4)&&(TimingFracInLeader<0.7)");
  AddCut("TOuterBins","(TimingFracInCentralFour>0.90)");
}

  
