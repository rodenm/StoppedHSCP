# generate hadd command to merge root files

import sys
import subprocess

if len(sys.argv)!=5 :
    print "Usage : python merge.py <dir> <base filename> <n files to merge> <n of first file>"

dir=sys.argv[1]
basename=sys.argv[2]
nfiles=int(sys.argv[3])
firstfile=int(sys.argv[4])

print "Merging files from "+dir
print "to "+dir+"/"+basename+".root"

command = "hadd -f "+dir+"/"+basename+".root "


for i in range(firstfile, firstfile+nfiles):
    command += dir+"/"+basename+"_"+str(i)+".root "

# call hadd
print command
hadd=subprocess.Popen(command,
                      shell=True
                      )

print hadd.communicate()[0]
