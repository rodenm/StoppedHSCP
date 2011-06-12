//
// Program to make limit plots
// 

#include "StoppedHSCP/Analysis/interface/LimitPlots.h"

//namespace po = boost::program_options;
//using namespace std;

#include <cstdlib>

int main(int argc, char* argv[]) {

  std::string dataset(argv[1]);
  double tpLumi = atof(argv[2]);
  unsigned massIndex = atoi(argv[3]);

  std::string toyFile=dataset+std::string("/toymc/summary.txt");
  std::string tpFile=dataset+std::string("/time_profile.txt");

  LimitPlots plots(tpLumi, toyFile, tpFile);

  plots.calculateCrossSections(massIndex);

  plots.makeBasicPlot();

  plots.makeLifetimePlot();

  plots.makeMassPlot();


}
