#ifndef LhcFill_h
#define LhcFill_h
// 
// Manages LHC filling scheme. Initiated by the standard LHC data
// fedor.ratnikov@cern.ch 16 May 2011
// 

#include <vector>
#include <string>
#include <iostream>

class LhcFill {
 public:
  LhcFill (const std::string& fBeamStructure = "");
  
  void vetoCollision (int fMin, int fLast);
  void vetoParasitic (int fMin, int fLast);
  void vetoLate (double fTimeWindow);
  
  const std::string& name () const {return mName;}
  
  double expectedLumi (int fBX) const;
  bool collisionBX (int fBX) const;
  bool vetoedBX (int fBX) const;
  bool sensitiveBX (int fBX) const;
  
  std::vector<int> collisionBXs () const;
  std::vector<int> sensitiveBXs () const;
  std::vector<int> insensitiveBXs () const;
  std::vector<std::pair<int, int> > sensitivePeriods () const; // pair: (firstBX, # of BXs)
  
  void printSummary (std::ostream& fOut);
  
 private:
  std::vector<float> mBunches;
  std::string mName;
};

#endif
