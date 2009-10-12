[CRAB]

jobtype = cmssw
scheduler = caf
### NOTE: just setting the name of the server (pi, lnl etc etc ) 
###       crab will submit the jobs to the server...   
#server_name = cnaf

[CMSSW]

### The data you want to access (to be found on DBS) 
datasetpath=/Calo/CRAFT09-v1/RAW
runselection=111039

### The ParameterSet you want to use
pset=test/HLT_CRAFT09_v2_4_V2.py

### Splitting parameters
total_number_of_events=-1 
events_per_job = 100000
#number_of_jobs = -1

### The output files (comma separated list)
#output_file = stoppedHSCPTree.root
get_edm_output = 1

[USER]

### OUTPUT files Management
##  output back into UI 
return_data = 0

### OUTPUT files INTO A SE
copy_data = 1
storage_element = T1_CH_CERN_Buffer
user_remote_dir = CRAFT09_HLT_v2

ui_working_dir = CRAFT09_HLT_v2

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


[CONDORG]

# Set this to condor to override the batchsystem defined in gridcat.
#batchsystem = condor

# Specify addition condor_g requirments
# use this requirment to run on a cms dedicated hardare
# globus_rsl = (condor_submit=(requirements 'ClusterName == \"CMS\" && (Arch == \"INTEL\" || Arch == \"X86_64\")'))
# use this requirement to run on the new hardware
#globus_rsl = (condor_submit=(requirements 'regexp(\"cms-*\",Machine)'))

