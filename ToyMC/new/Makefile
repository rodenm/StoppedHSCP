CXX       = g++
CXXFLAGS  = -pipe -g -Wall
INCPATH   = -I$(ROOTSYS)/include
LINK      = g++
LIBS      = -ldl -L$(ROOTSYS)/lib -lCore -lMathCore -lGraf -lHist -lGpad -lTree

SIM_OBJECTS = Experiment.o Simulator.o simulate_main.o experiment_dict.o
ANA_OBJECTS = Experiment.o Reducer.o Plotter.o analyze_main.o experiment_dict.o

all: simulate analyze

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

simulate: $(SIM_OBJECTS)
	$(LINK) -o simulate $(SIM_OBJECTS) $(LIBS)

analyze: $(ANA_OBJECTS)
	$(LINK) -o analyze $(ANA_OBJECTS) $(LIBS)

experiment_dict.cpp: Experiment.h
	rootcint -f $@ -c $^

clean:
	rm *.o experiment_dict.cpp simulate analyze
