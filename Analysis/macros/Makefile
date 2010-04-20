
CXX       = gcc
CXXFLAGS  = -pipe -g -Wall
INCPATH   = -I/usr/local/include/root -I/usr/include/c++/4.0.0/
LINK      = gcc
LIBS      = -L/usr/local/lib/root -lCore -lMathCore -lGraf -lHist -lGpad -lTree

OBJECTS = BasicHistograms.o
SOURCES = $(OBJECT,.o=.cc) StoppedHSCPTree.h

all: MyLib

MyLib: $(OBJECTS)
	$(LINK) -o $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)
	$(CXX) $(CXXFLAGS) -c $(SOURCES) $(INCPATH)

clean:
	rm *.o MyLib

