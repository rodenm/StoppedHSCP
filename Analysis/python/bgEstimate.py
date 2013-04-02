# calculate background

from math import sqrt

# fixed numbers [ value, uncertainty ]
noiseRate   = [ 1.6E-6, 2.52E-6 ]
cosmicIneff = [ 0.00214, 0.00023 ]

def totalBackground( livetime, cosmicNM1, nHalo ):

    r1 = livetime[1]/livetime[0]
    r2 = cosmicNM1[1]/cosmicNM1[0]
    r3 = nHalo[1]/nHalo[0]

    rn = noiseRate[1]/noiseRate[0]
    rc = cosmicIneff[1]/cosmicIneff[0]

    nNoise = [ ]
    nNoise.append( livetime[0]*noiseRate[0] )
    nNoise.append( nNoise[0]*sqrt(r1*r1 + rn*rn) )
    ra = nNoise[1]/nNoise[0]

    nCosmic = [ ]
    nCosmic.append( cosmicIneff[0]*cosmicNM1[0] )
    nCosmic.append( nCosmic[0]*sqrt(r2*r2 + rc*rc) )
    rb = nCosmic[1]/nCosmic[0]

    nTot = [ ]
    nTot.append( nHalo[0] + nNoise[0] + nCosmic[0] )
    nTot.append( sqrt(nHalo[1]*nHalo[1] + nNoise[1]*nNoise[1] + nCosmic[1]*nCosmic[1]) )

#    print "Expected backgrounds"
#    print "  Noise  : "+str(nNoise[0])+" +/- "+str(nNoise[1])
#    print "  Cosmic : "+str(nCosmic[0])+" +/- "+str(nCosmic[1])
#    print "  Halo   : "+str(nHalo[0])+" +/- "+str(nHalo[1])
#    print "  Total  : "+str(nTot[0])+" +/- "+str(nTot[1])
#    print

    return [nNoise, nCosmic, nHalo, nTot]


# 2010A
livetime  = [ 897802, 23 ]
cosmicNM1 = [ 1663, sqrt(1663) ]
nHalo     = [ 1e-32, 0.0 ]
#print "Run2010A"
res2010A = totalBackground( livetime, cosmicNM1, nHalo )
res2010A.append( [5] )

# 2010B
livetime  = [ 300065, 23 ]
cosmicNM1 = [ 473, sqrt(473) ]
nHalo     = [ 0.33, 0.16 ]
#print "Run2010B"
res2010B = totalBackground( livetime, cosmicNM1, nHalo )
res2010B.append( [4] )

# 2011A
livetime  = [ 724767, 23 ]
cosmicNM1 = [ 2243, sqrt(2243) ]
nHalo     = [ 1.2, 0.6 ]
#print "Run2011A"
res2011A = totalBackground( livetime, cosmicNM1, nHalo )
res2011A.append( [9] )

# 2011B
livetime  = [ 159283, 23 ]
cosmicNM1 = [ 423, sqrt(423) ]
nHalo     = [ 0.3, 0.1 ]
#print "Run2011B"
res2011B = totalBackground( livetime, cosmicNM1, nHalo )
res2011B.append( [3] )

# 2011A+B
livetime  = [ 884051, 23 ]
cosmicNM1 = [ 2666, sqrt(2666) ]
nHalo     = [ 1.5, 0.7 ]
#print "Run2011A+B"
res2011AB = totalBackground( livetime, cosmicNM1, nHalo )
res2011AB.append( [12] )

# Calculate halo rate based on Elog 513 in which we estimate 1.5 +/- 0.7 background for N-1=105
# 2012 rates are calculated with: 1.5/105 * (current N-1)
#
# 2012A
# N-1 halo: 35
livetime  = [ 140012, 23 ]
cosmicNM1 = [ 211, sqrt(211) ]
nHalo     = [ 0.50, 0.233 ]
#print "Run2012A"
res2012A = totalBackground( livetime, cosmicNM1, nHalo )
res2012A.append( [2] ) # THIS IS nOBS

# 2012B
# N-1 halo: 28
livetime  = [ 212487, 23 ]
cosmicNM1 = [ 473, sqrt(473) ]
nHalo     = [ 0.40, 0.187 ]
#print "Run2012B"
res2012B = totalBackground( livetime, cosmicNM1, nHalo )
res2012B.append( [0] ) # THIS IS nOBS

# 2012C (v1 + v2)
# N-1 halo: 147
livetime  = [ 351627, 23 ]
cosmicNM1 = [ 765, sqrt(765) ]
nHalo     = [ 2.1, 0.98 ]
#print "Run2012C"
res2012C = totalBackground( livetime, cosmicNM1, nHalo )
res2012C.append( [8] ) # THIS IS nOBS

# 2012D
# N-1 halo: 94
livetime  = [ 203945, 23 ]
cosmicNM1 = [ 475, sqrt(475) ]
nHalo     = [ 1.34, 0.63 ]
#print "Run2012D"
res2012D = totalBackground( livetime, cosmicNM1, nHalo )
res2012D.append( [4] ) # THIS IS nOBS

# 2012 <-------------out of date!
# N-1 halo: 223
livetime  = [ 757853, 23 ]
cosmicNM1 = [ 1568, sqrt(1568) ]
nHalo     = [ 3.19, 1.49 ]
#print "Run2012"
res2012 = totalBackground( livetime, cosmicNM1, nHalo )
res2012.append( [11] ) # THIS IS nOBS

# 2012BCD 
# Using halo background estimate from HaloBackground.cpp
livetime  = [ 989364, 23 ]
cosmicNM1 = [ 1815, sqrt(1713) ]
nHalo     = [ 0.132,0.009 ]
#print "Run2012BCD"
res2012BCD = totalBackground( livetime, cosmicNM1, nHalo )
res2012BCD.append( [16] ) # THIS IS nOBS

print "[TABLE border='1']"  
print "Period | Noise         | Cosmic         | Halo          | Total         | NObs |-"

print '---------------------------------------------------------------------------------'

print '2010A  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010A[0][0], res2010A[0][1], res2010A[1][0], res2010A[1][1], res2010A[2][0], res2010A[2][1], res2010A[3][0], res2010A[3][1], res2010A[4][0] )

print '2010B  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010B[0][0], res2010B[0][1], res2010B[1][0], res2010B[1][1], res2010B[2][0], res2010B[2][1], res2010B[3][0], res2010B[3][1], res2010B[4][0] )

print '---------------------------------------------------------------------------------'

print '2011A   | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011A[0][0], res2011A[0][1], res2011A[1][0], res2011A[1][1], res2011A[2][0], res2011A[2][1], res2011A[3][0], res2011A[3][1], res2011A[4][0] )

print '2011B   | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011B[0][0], res2011B[0][1], res2011B[1][0], res2011B[1][1], res2011B[2][0], res2011B[2][1], res2011B[3][0], res2011B[3][1], res2011B[4][0] )

print '2011AB  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011AB[0][0], res2011AB[0][1], res2011AB[1][0], res2011AB[1][1], res2011AB[2][0], res2011AB[2][1], res2011AB[3][0], res2011AB[3][1], res2011AB[4][0] )

print '---------------------------------------------------------------------------------'

print '2012A    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012A[0][0], res2012A[0][1], res2012A[1][0], res2012A[1][1], res2012A[2][0], res2012A[2][1], res2012A[3][0], res2012A[3][1], res2012A[4][0] )

print '2012B    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012B[0][0], res2012B[0][1], res2012B[1][0], res2012B[1][1], res2012B[2][0], res2012B[2][1], res2012B[3][0], res2012B[3][1], res2012B[4][0] )

print '2012C    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012C[0][0], res2012C[0][1], res2012C[1][0], res2012C[1][1], res2012C[2][0], res2012C[2][1], res2012C[3][0], res2012C[3][1], res2012C[4][0] )

print '2012D    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012D[0][0], res2012D[0][1], res2012D[1][0], res2012D[1][1], res2012D[2][0], res2012D[2][1], res2012D[3][0], res2012D[3][1], res2012D[4][0] )

print '2012BCD  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012BCD[0][0], res2012BCD[0][1], res2012BCD[1][0], res2012BCD[1][1], res2012BCD[2][0], res2012BCD[2][1], res2012BCD[3][0], res2012BCD[3][1], res2012BCD[4][0] )

print '2012     | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012[0][0], res2012[0][1], res2012[1][0], res2012[1][1], res2012[2][0], res2012[2][1], res2012[3][0], res2012[3][1], res2012[4][0] )

print "[/TABLE]"
