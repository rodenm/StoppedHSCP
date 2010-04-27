
CXX       = g++
CXXFLAGS  = -pipe -g -Wall
INCPATH   = -I$(ROOTSYS)include
LINK      = g++
LIBS      = -ldl -L$(ROOTSYS)/lib -lCore -lMathCore -lHist -lTree

SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc, %.o,$(SRCS))
HDRS = $(wildcard *.h)

all: BasicHistograms

BasicHistograms: BasicHistograms.cpp StoppedHSCPTree.h
	$(LINK) $(CXXFLAGS) $(INCPATH) -o BasicHistograms $< $(LIBS)

clean:
	rm BasicHistograms

print:
	echo $(OBJS) $(SRCS) $(HDRS)

