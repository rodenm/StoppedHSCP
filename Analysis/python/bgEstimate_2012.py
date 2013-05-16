# calculate background

from math import sqrt


##################################################
#
# This is the list that is used for the final 2012 results
#
# inputs [ livetime, haloR, cosmicNM1, final, haloErr]
##################################################
input2012BCD = [ 1011808, 12.8, 2096, 17, 2.5 ]  #haloErr=3.5(stat) + 8.2(sys)

###### OTHER YEARS ######
# inputs [ livetime, haloR, cosmicNM1, final, haloErr]
input2010A  = [ 911594., 0.0023, 1201, 1, 0.0024]
input2010B  = [ 300065., 7, 473, 4 ]
input2011A  = [ 724767., 60, 2243, 9 ]
input2011B  = [ 159283., 45, 423, 3 ]
input2011AB = [ 884051., 105, 2666, 12 ]

input2012A   = [ 140012, 0.0, 211, 2, 0.233 ]
input2012B   = [ 212487, 0.0, 473, 0, 0.19 ]
input2012Cv1 = [ 1, 0, 1, 0, 0 ]
input2012Cv2 = [ 351627, 0.0, 765, 8, 0.98]
input2012D   = [ 319376, 0.52, 740, 8,  0.05 ]

# Not using this because we only consider Run2012BCD
input2012    = [ 1, 0, 1, 0, 0 ]

# fixed numbers
cosmicIneff = [ 0.00214, 0.00023 ]
noiseRate   = [1.e-32/input2010A[0], 1./input2010A[0]]
#noiseRate   = [ 1.e-32, 0. ]
haloScaleFactor = [ 1.5/105, 0.7/105 ]

def totalBackground( livetime, cosmicNM1, haloR):
    
    r1 = livetime[1]/livetime[0]
    r2 = cosmicNM1[1]/cosmicNM1[0]
    
    rn = noiseRate[1]/noiseRate[0]
    rc = cosmicIneff[1]/cosmicIneff[0]

    nHalo = [ ]
    nHalo.append( haloScaleFactor[0] * haloNM1[0] )
    nHalo.append( haloScaleFactor[1] * haloNM1[0] )
    
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

def totalBackground2012( livetime, cosmicNM1, haloR, haloErr ):
    
    r1 = livetime[1]/livetime[0]
    r2 = cosmicNM1[1]/cosmicNM1[0]
    
    rn = 1e32 #noiseRate[1]/noiseRate[0]
    rc = cosmicIneff[1]/cosmicIneff[0]
    
    nHalo = [ ]
    nHalo.append( haloR )
    nHalo.append( haloErr )
    
    nNoise = [ ]
    nNoise.append( livetime[0]*noiseRate[0] )
    nNoise.append( nNoise[0]*sqrt(r1*r1 + rn*rn) )
    #ra = nNoise[1]/nNoise[0]
    
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
livetime  = [ input2010A[0], 23 ]
haloNM1   = [ input2010A[1], sqrt(input2010A[1]) ]
cosmicNM1 = [ input2010A[2], sqrt(input2010A[2]) ]
print "Run2010A - estimating noise background"
res2010A = totalBackground( livetime, cosmicNM1, haloNM1 )
res2010A.append( [input2010A[3]] )

# calculate noise rate from 2010A results
#noiseRate[0] = (res2010A[4][0] - res2010A[1][0])/livetime[0]
#noiseRate[1] = sqrt(res2010A[4][0]) / livetime[0]

print "Noise rate estimate : "+str(noiseRate[0])+" +/- "+str(noiseRate[1])
print

# 2010A
print "Run2010A"
res2010A = totalBackground( livetime, cosmicNM1, haloNM1 )
res2010A.append( [input2010A[3]] )


# 2010B
livetime  = [ input2010B[0], 23 ]
haloNM1   = [ input2010B[1], sqrt(input2010B[1]) ]
cosmicNM1 = [ input2010B[2], sqrt(input2010B[2]) ]
print "Run2010B"
res2010B = totalBackground( livetime, cosmicNM1, haloNM1 )
res2010B.append( [input2010B[3]] )

# 2011A
livetime  = [ input2011A[0], 23 ]
haloNM1   = [ input2011A[1], sqrt(input2011A[1]) ]
cosmicNM1 = [ input2011A[2], sqrt(input2011A[2]) ]
print "Run2011A"
res2011A = totalBackground( livetime, cosmicNM1, haloNM1 )
res2011A.append( [input2011A[3]] )

# 2011B
livetime  = [ input2011B[0], 23 ]
haloNM1   = [ input2011B[1], sqrt(input2011B[1]) ]
cosmicNM1 = [ input2011B[2], sqrt(input2011B[2]) ]
print "Run2011B"
res2011B = totalBackground( livetime, cosmicNM1, haloNM1 )
res2011B.append( [input2011B[3]] )

# 2011AB
livetime  = [ input2011AB[0], 23 ]
haloNM1   = [ input2011AB[1], sqrt(input2011AB[1]) ]
cosmicNM1 = [ input2011AB[2], sqrt(input2011AB[2]) ]
print "Run2011AB"
res2011AB = totalBackground( livetime, cosmicNM1, haloNM1 )
res2011AB.append( [input2011AB[3]] )

# (livetime, cosmicNM1, haloR, haloErr ):

# 2012A
livetime  = [ input2012A[0], 23 ]
#haloNM1   = [ input2012A[1], sqrt(input2012A[1]) ]
cosmicNM1 = [ input2012A[2], sqrt(input2012A[2]) ]
print "Run2012A"
res2012A = totalBackground2012( livetime, cosmicNM1, input2012A[1], input2012A[4] )
res2012A.append( [input2012A[3]] )

#2012B
livetime  = [ input2012B[0], 23 ]
#haloNM1   = [ input2012B[1], sqrt(input2012B[1]) ]
cosmicNM1 = [ input2012B[2], sqrt(input2012B[2]) ]
print "Run2012B"
res2012B = totalBackground2012( livetime, cosmicNM1, input2012B[1], input2012B[4] )
res2012B.append( [input2012B[3]] )

#2012C-v1
livetime  = [ input2012Cv1[0], 23 ]
#haloNM1   = [ input2012Cv1[1], sqrt(input2012Cv1[1]) ]
cosmicNM1 = [ input2012Cv1[2], sqrt(input2012Cv1[2]) ]
print "Run2012Cv1"
res2012Cv1 = totalBackground2012( livetime, cosmicNM1,  input2012Cv1[1], input2012Cv1[4] )
res2012Cv1.append( [input2012Cv1[3]] )

#2012C-v2
livetime  = [ input2012Cv2[0], 23 ]
#haloNM1   = [ input2012Cv2[1], sqrt(input2012Cv2[1]) ]
cosmicNM1 = [ input2012Cv2[2], sqrt(input2012Cv2[2]) ]
print "Run2012Cv2"
res2012Cv2 = totalBackground2012( livetime, cosmicNM1,  input2012Cv2[1], input2012Cv2[4] )
res2012Cv2.append( [input2012Cv2[3]] )

#2012D
livetime  = [ input2012D[0], 23 ]
#haloNM1   = [ input2012D[1], sqrt(input2012D[1]) ]
cosmicNM1 = [ input2012D[2], sqrt(input2012D[2]) ]
print "Run2012D"
res2012D = totalBackground2012( livetime, cosmicNM1,  input2012D[1], input2012D[4] )
res2012D.append( [input2012D[3]] )

#2012BCD
livetime  = [ input2012BCD[0], 23 ]
#haloNM1   = [ input2012BCD[1], sqrt(input2012BCD[1]) ]
cosmicNM1 = [ input2012BCD[2], sqrt(input2012BCD[2]) ]
print "Run2012BCD"
res2012BCD = totalBackground2012( livetime, cosmicNM1,  input2012BCD[1], input2012BCD[4] )
res2012BCD.append( [input2012BCD[3]] )

#2012
livetime  = [ input2012[0], 23 ]
#haloNM1   = [ input2012[1], sqrt(input2012[1]) ]
cosmicNM1 = [ input2012[2], sqrt(input2012[2]) ]
print "Run2012"
res2012 = totalBackground2012( livetime, cosmicNM1,  input2012[1], input2012[4] )
res2012.append( [input2012[3]] )


print "[TABLE border='1']"
print "Period | Noise         | Cosmic         | Halo          | Total         | NObs |-"

print '2010A  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010A[0][0], res2010A[0][1], res2010A[1][0], res2010A[1][1], res2010A[2][0], res2010A[2][1], res2010A[3][0], res2010A[3][1], res2010A[4][0] )

print '2010B  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2010B[0][0], res2010B[0][1], res2010B[1][0], res2010B[1][1], res2010B[2][0], res2010B[2][1], res2010B[3][0], res2010B[3][1], res2010B[4][0] )

print '2011AB  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2011AB[0][0], res2011AB[0][1], res2011AB[1][0], res2011AB[1][1], res2011AB[2][0], res2011AB[2][1], res2011AB[3][0], res2011AB[3][1], res2011AB[4][0] )

print '---------------------------------------------------------------------------------'

print '2012A    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012A[0][0], res2012A[0][1], res2012A[1][0], res2012A[1][1], res2012A[2][0], res2012A[2][1], res2012A[3][0], res2012A[3][1], res2012A[4][0] )

print '2012B    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012B[0][0], res2012B[0][1], res2012B[1][0], res2012B[1][1], res2012B[2][0], res2012B[2][1], res2012B[3][0], res2012B[3][1], res2012B[4][0] )

print '2012Cv1  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012Cv1[0][0], res2012Cv1[0][1], res2012Cv1[1][0], res2012Cv1[1][1], res2012Cv1[2][0], res2012Cv1[2][1], res2012Cv1[3][0], res2012Cv1[3][1], res2012Cv1[4][0] )

print '2012Cv2  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012Cv2[0][0], res2012Cv2[0][1], res2012Cv2[1][0], res2012Cv2[1][1], res2012Cv2[2][0], res2012Cv2[2][1], res2012Cv2[3][0], res2012Cv2[3][1], res2012Cv2[4][0] )

print '2012D    | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012D[0][0], res2012D[0][1], res2012D[1][0], res2012D[1][1], res2012D[2][0], res2012D[2][1], res2012D[3][0], res2012D[3][1], res2012D[4][0] )

print '2012BCD  | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012BCD[0][0], res2012BCD[0][1], res2012BCD[1][0], res2012BCD[1][1], res2012BCD[2][0], res2012BCD[2][1], res2012BCD[3][0], res2012BCD[3][1], res2012BCD[4][0] )

print '2012     | %.2f +/- %.2f |  %.2f +/- %.2f | %.2f +/- %.2f | %.2f +/- %.2f | %i   |-' % ( res2012[0][0], res2012[0][1], res2012[1][0], res2012[1][1], res2012[2][0], res2012[2][1], res2012[3][0], res2012[3][1], res2012[4][0] )


print "[/TABLE]"
print ""
print "Background uncertainty: ", (res2012BCD[3][1]/input2012BCD[0])/(res2012BCD[3][0]/input2012BCD[0])*100., "%"

print
print "parameters.txt :"
print
print "mass                     300"
print "crossSection             106"
print "lifetime                 1"
print "signalEff                0.033652"
print "signalEff_e              0.0"
print "bgRate                  ", res2012BCD[3][0]/input2012BCD[0]
print "bgRate_e                ", res2012BCD[3][1]/input2012BCD[0]
print "scaleUncert              0.0734"
print "optimizeTimeCut          1"
print "histFile                 /home/rodenm/stop_gluino/CMSSW_5_3_7_patch2/src/AllRun2012_537p2_V26_Dec_week3/Search.root"
print "lumiFile                 /home/rodenm/stop_gluino/CMSSW_5_3_7_patch2/src/StoppedHSCP/Analysis/data/lumi_all.csv"
print "jsonFile                 0"
print "lumiFirstRun             190645"
print "lumiLastRun              208686"
print "fills                    2605,2616,2617,2621,2623,2624,2627,2628,2629,2630,2632,2634,2635,2644,2645,2646,2648,2649,2651,2653,2657,2658,2660,2663,2669,2670,2671,2673,2675,2683,2686,2691,2692,2698,2700,2701,2710,2711,2712,2713,2714,2717,2718,2719,2720,2723,2724,2726,2728,2729,2732,2733,2734,2736,2737,2739,2797,2798,2805,2806,2807,2810,2812,2816,2819,2840,2842,2843,2847,2848,2858,2861,2870,2871,2872,2873,2875,2880,2882,2883,2884,2886,2887,2888,2891,2892,2893,2896,2898,2900,2902,2905,2908,2911,2912,2918,2920,2926,2927,2928,2929,2932,2934,2974,2975,2976,2978,2980,2981,2983,2984,2987,2991,2995,2996,2997,2998,3000,3002,3003,3005,3006,3007,3009,3011,3016,3018,3019,3020,3021,3023,3025,3027,3029,3032,3033,3034,3036,3039,3045,3047,3067,3071,3113,3114,3121,3124,3126,3128,3129,3131,3133,3134,3135,3138,3169,3178,3182,3185,3188,3191,3192,3194,3200,3201,3203,3204,3207,3208,3209,3210,3212,3214,3220,3223,3226,3229,3231,3232,3236,3238,3240,3242,3244,3249,3250,3252,3253,3259,3261,3262,3264,3265,3266,3269,3272,3273,3279,3285,3286,3287,3288,3292,3293,3296,3297,3298,3299,3300,3318,3319,3322,3323,3347,3350,3351,3360,3363,3370,3374,3375,3378"
print "eventsFile               /home/rodenm/stop_gluino/CMSSW_5_3_7_patch2/src/AllRun2012_537p2_V26_Dec_week3/searchEvents.txt"
print "nTrialsSignal            100"
print "nTrialsBackground        100"
print "simulateExpt             0"
print "fillScheme               Single_2b_1_1_1"
print "beamOnTime               0."
print "beamOffTime              0."
print "instLumi                 0."
print "runningTime              0."

