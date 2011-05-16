#ifndef LhcFills_h
#define LhcFills_h

// Class that stores everything you need to know about a series of LHC fills

#include <vector>
#include <string>
#include <iostream>

class LhcFills {

 public:

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
  std::vector<unsigned long> getRuns(unsigned long fill);
  std::string getFillingScheme(unsigned long fill);
  std::vector<unsigned long> getCollisions(unsigned long fill);
  std::vector<unsigned long> getBunches(unsigned long fill);
  std::vector<bool> getMask(unsigned long fill);
  std::vector<bool> getLifetimeMask(unsigned long fill);

  // get info about a particular run
  unsigned long getFillFromRun(unsigned long run);
  std::string getFillingSchemeFromRun(unsigned long run);
  std::vector<unsigned long> getCollisionsFromRun(unsigned long run);
  std::vector<unsigned long> getBunchesFromRun(unsigned long run);
  std::vector<bool> getMaskFromRun(unsigned long run);
  std::vector<bool> getLifetimeMaskFromRun(unsigned long run);

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
  unsigned long getIndexFromFill(unsigned long fill);
  unsigned long getIndexFromRun(unsigned long run);

 private:

  struct Fill {
    unsigned long number;
    std::string scheme;
    std::vector<unsigned long> runs;
    std::vector<unsigned long> beam1;
    std::vector<unsigned long> beam2;
    std::vector<unsigned long> collisions;
    std::vector<unsigned long> bunches;
    std::vector<bool> mask;         // masked bunches (usually any bunch +/- 1 BX)
    std::vector<bool> lifetimeMask; // lifetime dependent mask
  };

  std::vector<Fill> fills_;

  // vectors recording collisions and filled bunches for fast access
/*   std::vector< std::vector<unsigned> > colls_; */
/*   std::vector< std::vector<unsigned> > bunches_; */
  
  // vector which stores index of fill for fast access
  std::vector<unsigned long> lookupFillIndex_;
  std::vector<unsigned long> lookupRunIndex_;

};

#endif
