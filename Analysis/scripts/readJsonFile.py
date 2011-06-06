#!/usr/bin/env python


import sys, os, string

# for json support
try: # FUTURE: Python 2.6, prior to 2.6 requires simplejson
    import json
except:
    try:
        import simplejson as json
    except:
        print "Please use lxplus or set an environment (for example crab) with json lib available"
        sys.exit(1)

if len(sys.argv)==1:
    print "Sorry, you must specify at least one json file in command line!"
    sys.exit()


jsons=[]
for i in sys.argv[1:]:
    if not os.path.isfile(i):
        print "Sorry, file '%s' does not exist!"%i
        continue
    try:
        temp=open(i,'r')
        tempjson=json.load(temp)
        jsons.append(tempjson)
        keys=tempjson.keys()
        keys.sort()
        print "Json file '%s'"%i
        print "\t contains %i runs:"%len(keys)
        for k in keys:
            print "\t\t Run %s:  %s"%(k,tempjson[k])
    except SyntaxError:
        print "Unable to read file '%s' as a json file!"%i


if len(jsons)==2:
    print "\n\nComparing jsons"
    diff=False
    for i in jsons[0].keys():
        if i not in jsons[1].keys():
            print "Run %i  not in %s!"%(i,sys.argv[2])
            diff=True
        if jsons[0][i]<>jsons[1][i]:
            print "Run %i"%i
            print "Lumi's disagree! %s  %s"%(jsons[0][i],jsons[1][i])
            diff=True
    for i in jsons[1].keys():
        if i not in jsons[0].keys():
            print "Run %i  not in %s!"%(i,sys.argv[1])
            diff=True
        if jsons[0][i]<>jsons[1][i]:
            print "Run %i"%i
            print "Lumi's disagree! %s  %s"%(jsons[0][i],jsons[1][i])
            diff=True
    if (diff==False):
        print "No differences found"
