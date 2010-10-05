#include "StoppedHSCP/Analysis/interface/Histogrammer.h"
#include "StoppedHSCP/Analysis/interface/LhcFills.h"

#include <sstream>
#include <algorithm>

Histogrammer::Histogrammer(std::string filename, std::vector<unsigned> runs, Cuts* cuts) :
  file_(filename.c_str(), "recreate"),
  hists_(cuts, &file_, "All")
{
  // book them
  hists_.book();

  for (unsigned i=0; i<runs.size(); ++i) {
    std::stringstream runss;
    runss << runs.at(i);
    Histograms h(cuts, &file_, runss.str());
    h.book();
    runHists_.push_back(h);
    runs_.push_back(runs.at(i));
  }

}

Histogrammer::~Histogrammer() {

}

void Histogrammer::fill(StoppedHSCPEvent& event) {

  hists_.fill(event);

  for (unsigned i=0; i<runs_.size(); ++i) {
    if (runs_.at(i) == event.run) {
      runHists_.at(i).fill(event);
      break;
    }
  }
  
}


void Histogrammer::fillCollisionsHistos(unsigned run, LhcFills* fills) {

  hists_.fillCollisionsHisto(fills->getCollisionsFromRun(run));

  std::vector<Histograms>::iterator hists;
  for (unsigned i=0; i<runs_.size(); ++i) {
    if (runs_.at(i)==run) {
      runHists_.at(i).fillCollisionsHisto(fills->getCollisionsFromRun(run));
      break;
    }
  }

}


void Histogrammer::save() {

  // save histograms
  hists_.save();

  // loop over run histos
  for (unsigned i=0; i<runs_.size(); ++i) {

    // create directory for run
    char runstr[10];
    sprintf(runstr, "%d", runs_.at(i));
    
    if ( file_.cd(runstr) != kTRUE ){
      file_.mkdir(runstr);
      file_.cd(runstr);
    }

    // save them
    runHists_.at(i).save();

  }

}
