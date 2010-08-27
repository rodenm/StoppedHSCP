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

  std::vector<unsigned long> getFills();

  // get info about a particular fill
  std::vector<unsigned long> getRuns(unsigned fill);
  std::string getFillingScheme(unsigned fill);
  std::vector<unsigned> getCollisions(unsigned fill);
  std::vector<unsigned> getBunches(unsigned fill);

  // get info about a particular run
  unsigned long getFillFromRun(unsigned long run);
  std::string getFillingSchemeFromRun(unsigned long run);
  std::vector<unsigned> getCollisionsFromRun(unsigned long run);
  std::vector<unsigned> getBunchesFromRun(unsigned long run);

  // print info
  void printSummary(std::ostream& o);
  void print(std::ostream& o);

  // write files etc
  void writeBunchMaskFile();

 private:

  bool blankString(std::string& s);

 private:

  struct Fill {
    unsigned long number;
    std::string scheme;
    std::vector<unsigned long> runs;
    std::vector<unsigned> beam1;
    std::vector<unsigned> beam2;
  };

  std::vector<Fill> fills_;

};

#endif
