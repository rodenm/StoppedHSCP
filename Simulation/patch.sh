#!/bin/sh

# Stopped HSCP simulation
# script to patch external packages

eval `scramv1 ru -sh`
cd $CMSSW_BASE/src
addpkg IOMC/EventVertexGenerators
addpkg SimDataFormats/HepMCProduct

cp StoppedHSCP/Simulation/patches/RHDecay.cc IOMC/EventVertexGenerators/src/.
cp StoppedHSCP/Simulation/patches/RHDecay.h IOMC/EventVertexGenerators/interface/.
cp StoppedHSCP/Simulation/patches/RHDecay_module.cc IOMC/EventVertexGenerators/src/module.cc
cp StoppedHSCP/Simulation/patches/BuildFile_RHDecay IOMC/EventVertexGenerators/BuildFile

cp StoppedHSCP/Simulation/patches/HepMCProduct.cc SimDataFormats/HepMCProduct/src/.

