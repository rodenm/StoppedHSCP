# calculate background

from math import sqrt

# fixed numbers [ value, uncertainty ]
noiseRate   = [ 2.4E-7, 1.1E-7 ]
cosmicIneff = [ 0.0029, 0.0007 ]

def totalBackground( livetime, cosmicNM1, nHalo ):

    r1 = livetime[1]/livetime[0]
    r2 = cosmicNM1[1]/cosmicNM1[0]
    r3 = nHalo[1]/nHalo[0]

    Rn = noiseRate[1]/noiseRate[0]
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

    print "Expected backgrounds"
    print "  Noise  : "+str(nNoise[0])+" +/- "+str(nNoise[1])
    print "  Cosmic : "+str(nCosmic[0])+" +/- "+str(nCosmic[1])
    print "  Halo   : "+str(nHalo[0])+" +/- "+str(nHalo[1])
    print "  Total  : "+str(nTot[0])+" +/- "+str(nTot[1])
    print

    return [nNoise, nCosmic, nHalo, nTot]


# 2010A
livetime  = [ 891393, 23 ]
cosmicNM1 = [ 1650, sqrt(1650) ]
nHalo     = [ 1e-32, 0.0 ]
print "Run2010A"
res2010A = totalBackground( livetime, cosmicNM1, nHalo )
res2010A.append( [5] )

# 2010B
livetime  = [ 300088, 23 ]
cosmicNM1 = [ 467, sqrt(467) ]
nHalo     = [ 0.33, 0.16 ]
print "Run2010B"
res2010B = totalBackground( livetime, cosmicNM1, nHalo )
res2010B.append( [7] )

# 2011A
livetime  = [ 848787, 23 ]
cosmicNM1 = [ 2278, sqrt(2278) ]
nHalo     = [ 1.2, 0.6 ]
print "Run2011A"
res2011A = totalBackground( livetime, cosmicNM1, nHalo )
res2011A.append( [9] )

# 2011B
livetime  = [ 203320, 23 ]
cosmicNM1 = [ 530, sqrt(530) ]
nHalo     = [ 0.3, 0.1 ]
print "Run2011B"
res2011B = totalBackground( livetime, cosmicNM1, nHalo )
res2011B.append( [6] )

# 2011A+B
livetime  = [ 1052139, 23 ]
cosmicNM1 = [ 2808, sqrt(2808) ]
nHalo     = [ 1.5, 0.7 ]
print "Run2011A+B"
res2011AB = totalBackground( livetime, cosmicNM1, nHalo )
res2011AB.append( [15] )

print "[TABLE border='1']"  
print "Period | Noise         | Cosmic         | Halo          | Total         | NObs |-"

print '2010A  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010A[0][0], res2010A[0][1], res2010A[1][0], res2010A[1][1], res2010A[2][0], res2010A[2][1], res2010A[3][0], res2010A[3][1], res2010A[4][0] )

print '2010B  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010B[0][0], res2010B[0][1], res2010B[1][0], res2010B[1][1], res2010B[2][0], res2010B[2][1], res2010B[3][0], res2010B[3][1], res2010B[4][0] )

print '2011A  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011A[0][0], res2011A[0][1], res2011A[1][0], res2011A[1][1], res2011A[2][0], res2011A[2][1], res2011A[3][0], res2011A[3][1], res2011A[4][0] )

print '2011B  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011B[0][0], res2011B[0][1], res2011B[1][0], res2011B[1][1], res2011B[2][0], res2011B[2][1], res2011B[3][0], res2011B[3][1], res2011B[4][0] )

print '2011AB  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011AB[0][0], res2011AB[0][1], res2011AB[1][0], res2011AB[1][1], res2011AB[2][0], res2011AB[2][1], res2011AB[3][0], res2011AB[3][1], res2011AB[4][0] )

print "[/TABLE]"
