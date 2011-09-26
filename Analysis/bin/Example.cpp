#ifndef Example_h
#define Example_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

using namespace std;

class Example : public BasicAnalyser {

public:
  Example(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("Example.root");  /// SET YOUR OUTPUT FILENAME HERE
  }
  
  ~Example() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TH1D* myHistogram_;

};

#endif


// this is the event loop
void Example::loop() {

  // DO ANY SETUP HERE
  myHistogram_ = new TH1D("test", "", 10, 0., 10.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    myHistogram_->Fill(1);

  }


  // SAVE HISTOGRAMS HERE
  myHistogram_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Example analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
