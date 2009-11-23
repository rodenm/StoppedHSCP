#
# Use this CRAB config for generating stopped HSCP Trees
# Multiple options for filtering, re-running HLT etc
# Jim Brooke, Sept 09
# 


[CRAB]

jobtype = cmssw
scheduler = glitecoll
### NOTE: just setting the name of the server (pi, lnl etc etc ) 
###       crab will submit the jobs to the server...   
#server_name = cnaf

[CMSSW]

### The data you want to access (to be found on DBS) 
# CRAFT 09
datasetpath=/Calo/CRAFT09-GR09_31X_V5P_StoppedHSCP-332_v4/RAW-RECO
runselection=110958,110972,110987,110998,111009,111039,111138

# CRAFT 08
#datasetpath=/Calo/Commissioning08-v1/RAW
#runselection=68021

### The ParameterSet you want to use
pset=test/stoppedHSCPTree.py

### Splitting parameters
total_number_of_events=-1 
events_per_job = 100000
#number_of_jobs = -1

### The output files (comma separated list)
output_file = stoppedHSCPTree.root
	
[USER]

### OUTPUT files Management
##  output back into UI 
return_data = 0

### OUTPUT files INTO A SE
copy_data = 1
storage_element          = lcgse02.phy.bris.ac.uk
storage_path             = /srm/managerv2?SFN=/cms
storage_port             = 8444
user_remote_dir          = /store/user/jbrooke/StoppedHSCP_CRAFT09_v13

ui_working_dir = StoppedHSCP_CRAFT09_v13

#if server 
thresholdLevel = 50
eMail = jim.brooke@cern.ch

[GRID]

## RB/WMS management:
rb = CERN
proxy_server = myproxy.cern.ch

##  Black and White Lists management:
## By Storage
#se_black_list = 
#se_white_list = 

se_black_list = 
ce_black_list = 

## By ComputingElement 
#se_white_list = heplnx204.pp.rl.ac.uk
#ce_white_list = heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk 

[CONDORG]

# Set this to condor to override the batchsystem defined in gridcat.
#batchsystem = condor

# Specify addition condor_g requirments
# use this requirment to run on a cms dedicated hardare
# globus_rsl = (condor_submit=(requirements 'ClusterName == \"CMS\" && (Arch == \"INTEL\" || Arch == \"X86_64\")'))
# use this requirement to run on the new hardware
#globus_rsl = (condor_submit=(requirements 'regexp(\"cms-*\",Machine)'))

