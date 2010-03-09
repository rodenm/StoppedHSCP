import FWCore.ParameterSet.Config as cms

def UESettings () :
    return cms.vstring(
        'MSTJ(11)=3     ! Choice of the fragmentation function', 
        'MSTJ(22)=2     ! Decay those unstable particles', 
        'PARJ(71)=10 .  ! for which ctau  10 mm', 
        'MSTP(2)=1      ! which order running alphaS', 
        'MSTP(33)=0     ! no K factors in hard cross sections', 
        'MSTP(51)=10042     ! CTEQ6L1 structure function chosen', 
        'MSTP(52)=2     ! work with LHAPDF', 
        'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
        'MSTP(82)=4     ! Defines the multi-parton model', 
        'MSTU(21)=1     ! Check on possible errors during program execution', 
        'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
        'PARP(89)=1960. ! sqrts for which PARP82 is set', 
        'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
        'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
        'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
        'PARP(67)=2.5    ! amount of initial-state radiation', 
        'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
        'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
        'PARP(62)=1.25   ! ', 
        'PARP(64)=0.2    ! ', 
        'MSTP(91)=1     !', 
        'PARP(91)=2.1   ! kt distribution', 
        'PARP(93)=15.0  ! '
        )
        
def setupGluinoProduction (process, gluinoMass, particlesLSHAFile) :
    return cms.EDFilter("Pythia6GeneratorFilter",
                        pythiaPylistVerbosity = cms.untracked.int32(2),
                        filterEfficiency = cms.untracked.double(0.701),
                        pythiaHepMCVerbosity = cms.untracked.bool(True),
                        comEnergy = cms.double(10000.0),
                        crossSection = cms.untracked.double(1232),
                        maxEventsToPrint = cms.untracked.int32(2),
                        stopHadrons = cms.bool(False),
                        gluinoHadrons =  cms.bool(True),  
                        
                        PythiaParameters = cms.PSet(
        pythiaUESettings = UESettings (),
        processParameters = cms.vstring(
        'MSEL=0          ! User defined processes',
        'IMSS(1)=1       !  brute force',
        'MSUB(243)=1     !  subprocess',
        'MSUB(244)=1     !  subprocess',
        
        'IMSS(3)=1',
        'RMSS(1)=%f !should be gluino mass/2' % (gluinoMass/2.),
        'RMSS(2)=%f !should be gluino mass/2' % (gluinoMass/2.),
        'RMSS(3)=%f !should be gluino mass' % gluinoMass,
        'RMSS(10)=%f !RMSS(10)=2.2*mass gluino' % (gluinoMass*2.2),
        'RMSS(11)=%f !RMSS(10)=2.1*mass gluino' % (gluinoMass*2.1),
        'RMSS(12)=%f !should be gluino mass X2' % (gluinoMass*2.),
        ##    'RMSS(4)=10000.',
        
        'MDCY(309,1)=0                   ! set gluino stable',
        'IMSS(5)=1',
        #    'IMSS(21)=33  !read SLHAFILE from LUN33',
        #    'IMSS(23)=32  !write SLHA data',
        'MSTJ(14)=-1',
        'MSTP(111)=0 ! no hadronization'
        ),
        parameterSets = cms.vstring(
        'pythiaUESettings', 
        'processParameters',
        'SLHAParameters'
        ),
        SLHAParameters = cms.vstring('SLHAFILE = %s' % particlesLSHAFile)
        
        )
                        )

def setupStopProduction (process, stopMass, particlesLSHAFile) :
    return cms.EDFilter("Pythia6GeneratorFilter",
                        pythiaPylistVerbosity = cms.untracked.int32(2),
                        filterEfficiency = cms.untracked.double(0.701),
                        pythiaHepMCVerbosity = cms.untracked.bool(True),
                        comEnergy = cms.double(10000.0),
                        crossSection = cms.untracked.double(1232),
                        maxEventsToPrint = cms.untracked.int32(2),
                        stopHadrons = cms.bool(True),
                        gluinoHadrons = cms.bool(False),

                        PythiaParameters = cms.PSet(
        pythiaUESettings = UESettings (),
        processParameters = cms.vstring(
        'MSEL=0           !  User defined processes',
        'IMSS(1)=1        !  brute force',
        'MSUB(261)=1      !  subprocess ffbar-t1t1bar',
        'MSUB(264)=1      !  subprocess gg-t1t1bar',
        'IMSS(3)=1',
        'RMSS(3)=1000.    ! gluino mass',  
        'RMSS(1)=1000.    ! gluino mass',
        'RMSS(2)=1000.    ! gluino mass',
        'RMSS(4)=5000.    ',
        'MDCY(302,1)=0    ! set stop stable',
        'MWID(302)=0      ! set stop width',
        'IMSS(5)=1',
        'RMSS(12)=%f    ! stop mass' % stopMass,
        'RMSS(10)=%f    ! 1.5*stopmass' % (stopMass*1.5)
           ### 'MSTJ(14)=-1', # this is actually hardcoded in Py6Had class
           ### 'MSTP(111)=0'  # this is a MANDATORY, thus it's hardcoded in Py6Had class
         ),
        parameterSets = cms.vstring(
        'pythiaUESettings', 
        'processParameters',
        'SLHAParameters'
        ),
        SLHAParameters = cms.vstring('SLHAFILE = %s' % particlesLSHAFile)
        
        )
                        )

def setupStauProduction (process, stauMass, particlesLSHAFile) :
    return cms.EDFilter("Pythia6GeneratorFilter",
                        pythiaPylistVerbosity = cms.untracked.int32(2),
                        filterEfficiency = cms.untracked.double(0.701),
                        pythiaHepMCVerbosity = cms.untracked.bool(True),
                        comEnergy = cms.double(10000.0),
                        crossSection = cms.untracked.double(1232),
                        maxEventsToPrint = cms.untracked.int32(2),
                        gluinoHadrons =  cms.bool(True),  
                        
                        PythiaParameters = cms.PSet(
        pythiaUESettings = UESettings (),
        processParameters = cms.vstring(
        'MSEL=39                  ! All SUSY processes ',
        'IMSS(1) = 11             ! Spectrum from external SLHA file',
        'IMSS(21) = 33            ! LUN number for SLHA File (must be 33) ',
        'IMSS(22) = 33            ! Read-in SLHA decay table ',
        'MDCY(C1000015,1)=0       ! set the stau stable.'
        ),
        parameterSets = cms.vstring(
        'pythiaUESettings', 
        'processParameters',
        'SLHAParameters'
        ),
        SLHAParameters = cms.vstring('SLHAFILE = %s' % particlesLSHAFile)
        )
                        )
                        
def setupProduction (process, flavor, iMass, particlesLSHAFile) :
    if flavor == "gluino":
        return setupGluinoProduction (process, iMass, particlesLSHAFile)
    elif flavor == "stau":
        return setupStauProduction (process, iMass, particlesLSHAFile)
    elif flavor == "stop":
        return setupStopProduction (process, iMass, particlesLSHAFile)
    else:
        return None
