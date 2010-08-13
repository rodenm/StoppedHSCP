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

  std::vector<unsigned> getFills();

  // get info about a particular fill
  std::vector<unsigned> getRuns(unsigned fill);
  std::string getFillScheme(unsigned fill);
  std::vector<unsigned> getCollions(unsigned fill);
  std::vector<unsigned> getBunches(unsigned fill);

  // print info
  void printSummary(std::ostream& o);
  void print(std::ostream& o);

 private:

  struct Fill {
    unsigned number;
    std::string scheme;
    std::vector<unsigned> runs;
    std::vector<unsigned> beam1;
    std::vector<unsigned> beam2;
  };

  std::vector<Fill> fills_;

};

#endif
