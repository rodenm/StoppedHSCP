# merge root files on castor

import sys
import subprocess

dir=sys.argv[1]
ofile=dir+"/"+sys.argv[2]

print "Merging files from "+dir
print "to "+ofile

# get list of files
print "rfdir "+dir
rfdir=subprocess.Popen("rfdir "+dir,
                       shell=True,
                       stdout=subprocess.PIPE,
                       )

filelist=rfdir.communicate()[0]

# remove lines and other garbage (why doesn't rfdir support this!)
files=" "
for line in filelist.splitlines():
    fields = line.split()
    files+=dir+"/"+fields[8]+' '
        
# call hadd
print "hadd "+dir+ofile+files
hadd=subprocess.Popen("hadd "+ofile+files,
                       shell=True,
                       )

print hadd.communicate()[0]
