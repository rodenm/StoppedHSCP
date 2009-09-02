#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "TObject.h"

class Experiment : public TObject
{
public:
    Experiment();

    enum lookwhere_type {
        BEAMGAP,
        INTERFILL,
        BOTH
    };

    //inputs
    // particle parameters
    double mass;
    double crossSection;
    double lifetime;
    // experiment parameters
    double lumi;
    unsigned int bxStruct;
    double runningTime;
    double bgRate;
    double signalEff;
    double beamOnTime;
    double beamOffTime;
    // analysis parameters
    lookwhere_type lookwhere;
    bool optimizeTimeCut;
    double scale;
    double bgScale;

    //outputs
    // event counts - Changed to be just run one "type" of experiment
    // (i.e. beamgap or interfill or both)
    unsigned nGeneratedDecays;
    unsigned nSig;
    unsigned nBg;
    // expected calculated background
    double nExpectedBg;
    // experiment p-values
    double Pb;
    double oneMinusPb;
    double Psb;
    double oneMinusPsb;

    ClassDef(Experiment,1);
};

#endif // EXPERIMENT_H
