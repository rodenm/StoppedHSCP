
CXX       = g++
CXXFLAGS  = -pipe -g -Wall
ROOTINC   = -I$(ROOTSYS)include
LINK      = g++
LIBS      = -ldl -L$(ROOTSYS)/lib -lCore -lMathCore -lHist -lTree

# machine dependent stuff
ifeq ($(HOSTNAME), soolin.phy.bris.ac.uk)
  INCPATH   = $(ROOTINC) -I/opt/g/ui/3.2.2-0/external/usr/include/
else
  INCPATH   = $(ROOTINC)
endif

all: makeHistograms

makeHistograms: macros/BasicHistograms.cpp macros/StoppedHSCPTree.h
	$(LINK) $(CXXFLAGS) $(INCPATH) -o makeHistograms $< $(LIBS)

clean:
	rm makeHistograms
