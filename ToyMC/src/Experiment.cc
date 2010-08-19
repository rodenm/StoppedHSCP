#include "StoppedHSCP/ToyMC/interface/Experiment.h"

#include <iostream>

ClassImp(Experiment)

Experiment::Experiment() :
  isProjection(false),
  mass(0),
  crossSection(0),
  lifetime(0),
  lumi(0),
  bxStruct(0),
  runningTime(0),
  bgRate(0),
  errBgRate(0),
  signalEff(0),
  beamOnTime(0),
  beamOffTime(0),
  fills(0),
  lookwhere(BOTH),
  optimizeTimeCut(true),
  scale(1000),
  bgScale(100),
  nObs(0),
  nVetoes(0)
{
}

std::ostream &operator<<(std::ostream &o, const Experiment &e) {
  return o
    << "Stopped HSCP experiment" << std::endl
    << " Physics" << std::endl
    << "  Gluino mass      : " << e.mass << std::endl
    << "  Cross-section    : " << e.crossSection << std::endl
    << "  Lifetime         : " << e.lifetime << std::endl
    << " Expt parameters" << std::endl
    << "  Lumi             : " << e.lumi << std::endl
    << "  BX structure     : " << e.bxStruct << std::endl
    << "  BG rate          : " << e.bgRate << std::endl
    << "  Sig eff          : " << e.signalEff << std::endl
    << "  Running time     : " << e.runningTime << std::endl
    << "  Beam On  time    : " << e.beamOnTime << std::endl
    << "  Beam Off time    : " << e.beamOffTime << std::endl
    << " Anlsys parameters" << std::endl
    << "  Optimize Time Cut: " << (e.optimizeTimeCut ? "X" : "") << std::endl
    << "  Beamgap          : " << (e.lookwhere == e.BEAMGAP ||
                                   e.lookwhere == e.BOTH ?
                                   "X" : "") << std::endl
    << "  Interfill        : " << (e.lookwhere == e.INTERFILL ||
                                   e.lookwhere == e.BOTH ?
                                   "X" : "") << std::endl
    << "  S Scaling Factor : " << e.scale << std::endl
    << "  B Scaling Factor : " << e.bgScale << std::endl
    << " Results" << std::endl
    << "  N generated decays " << e.nGeneratedDecays << std::endl
    << "  Ns               : " << e.nSig << std::endl
    << "  Nb               : " << e.nBg << std::endl
    << "  Expected Nb      : " << e.nExpectedBg << std::endl
    << "  Pb               : " << e.Pb << std::endl
    << "  1 - Pb           : " << e.oneMinusPb << std::endl
    << "  Psb              : " << e.Psb << std::endl
    << "  1 - Psb          : " << e.oneMinusPsb << std::endl
    << std::endl;
}


Experiment operator+(const Experiment &a, const Experiment &b) {

  Experiment e(a);

  e.nGeneratedDecays += b.nGeneratedDecays;
  e.nSig             += b.nSig;
  e.nSig_d           += b.nSig_d;
  e.nSig_d_statErr = a.nSig_d_statErr + b.nSig_d_statErr;
  // e.nObs             += b.nObs;
  e.nVetoes          += b.nVetoes;
  e.nBg              += b.nBg;
  e.nExpectedBg      += b.nExpectedBg;
  e.nExpectedBg_statErr = a.nExpectedBg_statErr + b.nExpectedBg_statErr;

  return e;
}
