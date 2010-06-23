#ifndef LUMIREADER_H
#define LUMIREADER_H

#include <string>
#include <vector>

class LumiReader {
 public:
  static LumiReader *getLumiReader(std::string str) {return new LumiReader;}

  double sectionStartTime(uint32_t index);
  double sectionEndTime(uint32_t index);
  double sectionEmptyBunchesFraction(uint32_t index);
  uint32_t getIndex(double);
  double instantLuminosity(uint32_t index);
  uint32_t entries();
  std::vector<uint32_t> &getAllTimestamps();

 private:
  std::vector<uint32_t> timestamps;
  std::vector<uint32_t> lumi;
};

#endif
