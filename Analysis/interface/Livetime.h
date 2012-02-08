#ifndef Livetime_h
#define Livetime_h

#include <vector>
#include <utility>


class LhcFills;
class TFile;

class Livetime {
 public:

  Livetime(LhcFills* lhcFills);
  ~Livetime();

  void newEvent(unsigned long fill, unsigned long run, unsigned long lb);

  double getLivetimeByRun(unsigned long run);

  double getLivetimeByFill(unsigned long fill);

  double getTotalLivetime();

  std::vector<unsigned long> fillList();

  std::vector<unsigned long> runList();

  std::vector<std::pair<unsigned long, unsigned long> > runLumiPairs();
  
  void writeHistograms(TFile* ofile);

 private:

  LhcFills* lhcFills_;

  std::vector<std::pair<unsigned long, unsigned long> > runLumiPairs_;
  std::vector<unsigned long> fillList_;
  std::vector<unsigned long> runList_;


};

#endif
