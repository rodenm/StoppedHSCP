#ifndef LhcFills_h
#define LhcFills_h

// Class that stores everything you need to know about a series of LHC fills

#include <vector>
#include <string>
#include <iostream>

class LhcFills {

 public:

  static const unsigned NBX_PER_ORBIT;// = 3564;
  static const double TIME_PER_BX;// = 25.e-9;
  static const double TIME_WINDOW;// = 1.256;

  LhcFills();
  ~LhcFills();

  // set up internal info
  void readFiles();
  void setupCollisions();
  void setupBunches();
  void setupLifetimeMask(double lifetime);

  // get everything
  std::vector<unsigned long> getFills();

  // get info about a particular fill
  std::vector<unsigned long> getRuns(unsigned fill);
  std::string getFillingScheme(unsigned fill);
  std::vector<unsigned> getCollisions(unsigned fill);
  std::vector<unsigned> getBunches(unsigned fill);
  std::vector<bool> getMask(unsigned fill);
  std::vector<bool> getLifetimeMask(unsigned fill);

  // get info about a particular run
  unsigned long getFillFromRun(unsigned long run);
  std::string getFillingSchemeFromRun(unsigned long run);
  std::vector<unsigned> getCollisionsFromRun(unsigned long run);
  std::vector<unsigned> getBunchesFromRun(unsigned long run);
  std::vector<bool> getMaskFromRun(unsigned run);
  std::vector<bool> getLifetimeMaskFromRun(unsigned run);

  // get info about a particular filling scheme
  //   std::vector<unsigned> getCollisionsFromScheme(std::string scheme);
  //   std::vector<unsigned> getBunchesFromScheme(std::string scheme);  

  // print info
  void printSummary(std::ostream& o);
  void print(std::ostream& o);

  // write files etc
  void writeBunchMaskFile();

 private:

  bool blankString(std::string& s);

  // get indices
  unsigned getIndexFromFill(unsigned fill);
  unsigned getIndexFromRun(unsigned run);

 private:

  struct Fill {
    unsigned long number;
    std::string scheme;
    std::vector<unsigned long> runs;
    std::vector<unsigned> beam1;
    std::vector<unsigned> beam2;
    std::vector<unsigned> collisions;
    std::vector<unsigned> bunches;
    std::vector<bool> mask;         // masked bunches (usually any bunch +/- 1 BX)
    std::vector<bool> lifetimeMask; // lifetime dependent mask
  };

  std::vector<Fill> fills_;

  // vectors recording collisions and filled bunches for fast access
/*   std::vector< std::vector<unsigned> > colls_; */
/*   std::vector< std::vector<unsigned> > bunches_; */
  
  // vector which stores index of fill for fast access
  std::vector<unsigned> lookupFillIndex_;
  std::vector<unsigned> lookupRunIndex_;

};

#endif
