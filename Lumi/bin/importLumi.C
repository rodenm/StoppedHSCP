#include "importLumi.h"

void importLumi (const char* inputFile, const char* outputFile) {
  std::vector<std::string> input;
  input.push_back (std::string (inputFile));
  std::string output (outputFile);
  importLumi (input, output, true);
}
