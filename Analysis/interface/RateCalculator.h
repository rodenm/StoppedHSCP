
#include <map>
#include <vector>
#include <string>

#include "TFile.h"
#include "TH1D.h"
#include "TGraphErrors.h"

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"


const int BX_IN_ORBIT = 3564;

// JsonFileReader* jsonFileReader = 0;
const double lbSeconds = 89.1e-6*double(int(0x40000)); // 98mks*2^18
const char* cutName [] = {"HLT", "BX", "GT", "Nmu", "Jet30",
			  "Jet50", "N60", "N90", "Nphi", "R1", 
			    "R2", "Rpeak", "Router", "Emf"}; 

class RateCalculator : public BasicAnalyser {
 public:
  struct Counts {
    int countsX;
    int countsY;
    Counts () : countsX(0), countsY(0) {}
  };
  typedef std::map<int,Counts> RunStats;
  typedef std::map<int, RunStats> MapRun;
  
 public:

  RateCalculator (const std::string& name,
		  const std::string& file,
		  const std::string& ofile);
  ~RateCalculator();

  void addXcut (int cut);
  void addYcut (int cut);
  
  void process ();
  std::string xTitle();
  std::string yTitle();

  void printOut ();
  
  TH1D* plotByRunProjection (bool x);
  TGraphErrors* plotByRun ();  
  TGraphErrors* plotByPeriod (int fPeriods);

  void loop();

 private:
  MapRun::iterator mCurrentRun;
  MapRun mCollector; 
  std::vector<int> mXCuts;
  std::vector<int> mYCuts;
  std::string mName;

  TFile ofile_;
  
};

