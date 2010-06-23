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
    double errBgRate;
    double signalEff;
    double beamOnTime;
    double beamOffTime;
    // analysis parameters
    lookwhere_type lookwhere;
    bool optimizeTimeCut;
    double scale;
    double bgScale;
    bool sendToLifetimeFit;

    double collisionL1Arate;

    //outputs
    // event counts - Changed to be just run one "type" of experiment
    // (i.e. beamgap or interfill or both)
    double nGeneratedDecays;
    double nSig_d;
    unsigned nSig;
    unsigned nObs;
    double nVetoes;
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

Experiment operator+(const Experiment &, const Experiment &);

#endif // EXPERIMENT_H
