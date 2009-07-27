#include "importLumi.h"

const bool oldFormat = true;

int main (int argc, char *argv[]) {
  if (argc < 3) {
    std::cout << "Usage: " << argv[0] << " <original LUMI file(s)> <produced LUMI file>" << std::endl;
    return 1;
  }

  std::vector<std::string> inputFiles;
  inputFiles.push_back (std::string (argv[1]));
  std::string outputFile (argv[2]);
  importLumi (inputFiles, outputFile, oldFormat);
  return 0;
}
