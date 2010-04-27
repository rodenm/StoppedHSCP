
CXX       = g++
CXXFLAGS  = -pipe -g -Wall
INCPATH   = -I$(ROOTSYS)include
LINK      = g++
LIBS      = -ldl -L$(ROOTSYS)/lib -lCore -lMathCore -lHist -lTree

all: makeHistograms

makeHistograms: macros/BasicHistograms.cpp macros/StoppedHSCPTree.h
	$(LINK) $(CXXFLAGS) $(INCPATH) -o makeHistograms $< $(LIBS)

clean:
	rm makeHistograms
