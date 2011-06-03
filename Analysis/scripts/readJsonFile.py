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

for i in sys.argv[1:]:
    if not os.path.isfile(i):
        print "Sorry, file '%s' does not exist!"%i
        continue
    try:
        temp=open(i,'r')
        tempjson=json.load(temp)
        keys=tempjson.keys()
        keys.sort()
        print "Json file '%s'"%i
        print "\t contains %i runs:"%len(keys)
        for k in keys:
            print "\t\t Run %s:  %s"%(k,tempjson[k])
    except SyntaxError:
        print "Unable to read file '%s' as a json file!"%i
