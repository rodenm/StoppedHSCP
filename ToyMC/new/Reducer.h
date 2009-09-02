#ifndef REDUCER_H
#define REDUCER_H

#include <vector>
#include <TGraph.h>
#include "Experiment.h"

// Reducer takes in a vector of collections, and makes one of many TGraphs

class Reducer
{
public:
    Reducer(const std::vector<Experiment> &input);

    TGraph *getEfficiencyPlot();
    TGraph *getZbPlot(double lifetime);
    TGraph *getExclusionPlot(double mass);

protected:
    const std::vector<Experiment> &exps;
    std::vector<Experiment>::const_iterator cit;
};

#endif // REDUCER_H
