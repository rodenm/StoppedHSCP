#ifndef JsonFileReader_h
#define JsonFileReader_h
// simplifyed reader of CMS "good data" json file

#include <string>
#include <vector>
#include <map>

class JsonFileReader {
 public:
  JsonFileReader (const std::string& fJasonFile);
  bool goodLB (int fRun, int fLumiBlock) const;
  std::vector<int> allRuns () const;
  std::vector<int> allLumiBlocks (int fRun) const;
 private:
  std::map<int, std::vector <std::pair<int, int> > > mData;
};
#endif
