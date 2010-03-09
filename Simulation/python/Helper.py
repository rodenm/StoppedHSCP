import sys

def parseParams ():
    result=[]
    for token in sys.argv:
        if token[0] == '-': continue
        if str.find (token, '=') < 0: continue
        (opt, value) = str.split (token, '=')
        result.append ((opt, value))
    return result

def randomize (randomNumberGeneratorService):
    from IOMC.RandomEngine.RandomServiceHelper import RandomNumberServiceHelper
    RandomNumberServiceHelper(randomNumberGeneratorService).populate()

# One-jet R-hadron decay description
def makeSingleJetRhadronDecay (filename, rhadronId, gluinoMass, neutralinoMass):
    f=open(filename, 'w')
    rhadronMass = gluinoMass + 2
    f.write ('DECAY     %s     1.00000000E-12\n' % rhadronId)
    f.write ('     1.00000000E+00    3     2203    1000021       2\n')
    f.write ('DECAY     1000022     0.00000000E+00 \n')
    f.write ('DECAY     1000021     1.00000000E-12 \n')
    f.write ('     1.00000000E+00    2     1000022       21 \n') 
    f.write ('BLOCK QNUMBERS %s # Rhad\n' % rhadronId)
    f.write ('         1 6  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 1  \n')
    f.write ('BLOCK QNUMBERS 1000021 # gluino\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 8  \n')
    f.write ('         4 1  \n')
    f.write ('BLOCK QNUMBERS 1000022 # chi0_1\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 0  \n')
    f.write ('BLOCK_MASS \n')
    f.write ('   %s  %s \n' % (rhadronId, rhadronMass))
    f.write ('   1000021  %s \n' % gluinoMass)
    f.write ('   1000022  %s \n' % neutralinoMass)

def makeDoubleJetRhadronDecay (filename, rhadronId, gluinoMass, neutralinoMass):
    f=open(filename, 'w')
    rhadronMass = gluinoMass + 2
    f.write ('DECAY     %s     1.00000000E-12\n' % rhadronId)
    f.write ('     1.00000000E+00    3     2203    1000021       2\n')
    f.write ('DECAY     1000022     0.00000000E+00 \n')
    f.write ('DECAY     1000021     1.00000000E-12 \n')
    f.write ('     0.33333333E+00    3     1000022       1      -1 \n') 
    f.write ('     0.33333333E+00    3     1000022       2      -2 \n') 
    f.write ('     0.33333333E+00    3     1000022       3      -3 \n') 
    f.write ('BLOCK QNUMBERS %s # Rhad\n' % rhadronId)
    f.write ('         1 6  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 1  \n')
    f.write ('BLOCK QNUMBERS 1000021 # gluino\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 8  \n')
    f.write ('         4 1  \n')
    f.write ('BLOCK QNUMBERS 1000022 # chi0_1\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 0  \n')
    f.write ('BLOCK_MASS \n')
    f.write ('   %s  %s \n' % (rhadronId, rhadronMass))
    f.write ('   1000021  %s \n' % gluinoMass)
    f.write ('   1000022  %s \n' % neutralinoMass)

def makeStopHadronDecay (filename, stopHadronId, stopMass, neutralinoMass):
    f=open(filename, 'w')
    stopHadronMass = stopMass + 1
    f.write ('DECAY     %s     1.00000000E-12\n' % stopHadronId)
    f.write ('     1.00000000E+00    2     2203    1000006 \n')
    f.write ('DECAY     1000022     0.00000000E+00 \n')
    f.write ('DECAY     1000006     1.00000000E-12 \n')
    f.write ('     1.00000000E+00    2     1000022       6 \n') 
    f.write ('BLOCK QNUMBERS %s # Rhad\n' % stopHadronId)
    f.write ('         1 6  # 3 times electric charge\n')
    f.write ('         2 2  # number of spin states (2S+1)\n')
    f.write ('         3 1  # colour rep (1: singlet, 3: triplet, 8: octet)\n')
    f.write ('         4 1  # Particle/Antiparticle distinction (0=own anti)\n')
    f.write ('BLOCK QNUMBERS 1000022 # chi0_1\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 0  \n')
    f.write ('BLOCK_MASS \n')
    f.write ('   %s  %s \n' % (stopHadronId, stopHadronMass))
    f.write ('   1000006  %s \n' % stopMass)
    f.write ('   1000022  %s \n' % neutralinoMass)

def makeStauDecay (filename, stauMass, neutralinoMass):
    f=open(filename, 'w')
    f.write ('DECAY     1000022     0.00000000E+00 \n')
    f.write ('DECAY     1000015     1.00000000E-12 \n')
    f.write ('     1.00000000E+00    2     1000015       15 \n') 
    f.write ('BLOCK QNUMBERS 1000022 # chi0_1\n')
    f.write ('         1 0  \n')
    f.write ('         2 2  \n')
    f.write ('         3 1  \n')
    f.write ('         4 0  \n')
    f.write ('BLOCK_MASS \n')
    f.write ('   1000015  %s \n' % stauMass)
    f.write ('   1000022  %s \n' % neutralinoMass)
