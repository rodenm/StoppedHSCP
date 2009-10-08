[CRAB]

jobtype = cmssw
scheduler = glite
#server_name =

[CMSSW]

datasetpath=/Calo/Commissioning08-v1/RAW
runselection=68021

pset=test/stoppedHSCPTree_CRAFT08.py
total_number_of_events=-1
events_per_job = 50000

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
user_remote_dir          = /store/user/jbrooke/StoppedHSCP_CRAFT08_v5

ui_working_dir = CRAFT08_v5

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

#se_black_list = 
#ce_black_list = 

## By ComputingElement 
#se_white_list = heplnx204.pp.rl.ac.uk


