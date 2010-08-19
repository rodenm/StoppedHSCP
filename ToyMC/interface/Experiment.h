#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "TObject.h"
#include <vector>
#include <iostream>

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
    bool isProjection;
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
    std::vector<ULong_t> fills;
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
    double nSig_d_statErr;
    unsigned nSig;
    unsigned nObs;
    double nVetoes;
    unsigned nBg;
    // expected calculated background
    double nExpectedBg;
    double nExpectedBg_statErr;
    // experiment p-values
    double Pb;
    double oneMinusPb;
    double Psb;
    double oneMinusPsb;

    ClassDef(Experiment,1);
};

std::ostream &operator<<(std::ostream &o, const Experiment &e);

Experiment operator+(const Experiment &, const Experiment &);

#endif // EXPERIMENT_H
