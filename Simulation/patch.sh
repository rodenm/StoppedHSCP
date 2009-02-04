#!/bin/sh

# Stopped HSCP simulation
# script to patch external packages

eval `scramv1 ru -sh`
cd $CMSSW_BASE/src
addpkg IOMC/EventVertexGenerators
addpkg SimDataFormats/HepMCProduct

mv StoppedHSCP/Simulation/src/RHDecay.cc IOMC/EventVertexGenerators/src/.
mv StoppedHSCP/Simulation/src/RHDecay.h IOMC/EventVertexGenerators/interface/.
mv StoppedHSCP/Simulation/src/RHDecay_module.cc IOMC/EventVertexGenerators/src/module.cc
mv StoppedHSCP/Simulation/src/BuildFile_RHDecay IOMC/EventVertexGenerators/BuildFile

mv StoppedHSCP/Simulation/src/HepMCProduct.cc SimDataFormats/HepMCProduct/src/.

