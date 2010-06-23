#include "StoppedHSCP/ToyMC/interface/Experiment.h"

ClassImp(Experiment)

Experiment::Experiment() :
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
  lookwhere(BOTH),
  optimizeTimeCut(true),
  scale(1000),
  bgScale(100),
  nObs(0),
  nVetoes(0)
{
}
/*
std::ostream &operator<<(std::ostream &o, const Experiment &e) {
    using namespace std;
  return o
    << "Stopped HSCP experiment" << endl
    << " Physics" << endl
    << "  Gluino mass      : " << e.mass << endl
    << "  Cross-section    : " << e.crossSection << endl
    << "  Lifetime         : " << e.lifetime << endl
    << " Expt parameters" << endl
    << "  Lumi             : " << e.lumi << endl
    << "  BX structure     : " << e.bxStruct << endl
    << "  BG rate          : " << e.bgRate << endl
    << "  Sig eff          : " << e.signalEff << endl
    << "  Running time     : " << e.runningTime << endl
    << "  Beam On  time    : " << e.beamOnTime << endl
    << "  Beam Off time    : " << e.beamOffTime << endl
    << " Anlsys parameters" << endl
    << "  Optimize Time Cut: " << (e.optimizeTimeCut ? "X" : "") << endl
    << "  Beamgap          : " << (e.lookwhere == e.BEAMGAP ||
                                   e.lookwhere == e.BOTH ?
                                   "X" : "") << endl
    << "  Interfill        : " << (e.lookwhere == e.INTERFILL ||
                                   e.lookwhere == e.BOTH ?
                                   "X" : "") << endl
    << "  S Scaling Factor : " << e.scale << endl
    << "  B Scaling Factor : " << e.bgScale << endl
    << " Results" << endl
    << "  N generated decays " << e.nGeneratedDecays << endl
    << "  Ns               : " << e.nSig << endl
    << "  Nb               : " << e.nBg << endl
    << "  Expected Nb      : " << e.nExpectedBg << endl
    << "  Pb               : " << e.Pb << endl
    << "  1 - Pb           : " << e.oneMinusPb << endl
    << "  Psb              : " << e.Psb << endl
    << "  1 - Psb          : " << e.oneMinusPsb << endl
    << endl;
}
*/

Experiment operator+(const Experiment &a, const Experiment &b) {

  Experiment e(a);

  e.nGeneratedDecays += b.nGeneratedDecays;
  e.nSig             += b.nSig;
  e.nSig_d           += b.nSig_d;
  e.nObs             += b.nObs;
  e.nVetoes          += b.nVetoes;
  e.nBg              += b.nBg;
  e.nExpectedBg      += b.nExpectedBg;

  return e;
}
