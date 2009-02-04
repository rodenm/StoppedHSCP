#!/bin/sh

# Stopped HSCP simulation
# script to patch external packages

eval `scramv1 ru -sh`
cd $CMSSW_BASE
addpkg IOMC/EventVertexGenerators
addpkg SimDataFormats/HepMCProduct

cp StoppedHSCP/Simulation/src/RHDecay.cc IOMC/EventVertexGenerators/src/.
cp StoppedHSCP/Simulation/src/RHDecay_module.cc IOMC/EventVertexGenerators/src/module.cc

cp StoppedHSCP/Simulation/src/HepMCProduct.cc SimDataFormats/HepMCProduct/src/.

