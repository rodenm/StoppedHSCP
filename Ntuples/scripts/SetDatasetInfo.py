#!/usr/bin/env python
import sys,os,string

class DatasetInfo:
    '''Class that stores special variables (l1jet, hlt tags, etc). that change from dataset to dataset.  Each instance of this class stores the information for one dataset.'''

    def __init__(self,name=None,trigger="2011",datatype=None):
        self.name=name
        self.trigger=trigger
        self.datatype=datatype
        
        ''' self.InputInfo stores list variables to be changed for a given dataset.
        If variable value is None, no change is made.
        Variables are assumed to by strings, except for hltL3Tag, which is an InputTag.  The variables are dealt with by makeTreeJob.py -- maybe a future iteration will allow the user to specify input type within this class, and makeTreeJob will just use that info?
        '''
        self.InputInfo={}  
        self.InputInfo["hltL3Tag"]=None
        self.InputInfo["l1JetNoBptxName"]=None # was L1_SingleJet20_NotBptxOR; changed to  L1_SingleJet20_NotBptxOR with fill 1960 (new dataset)
        self.InputInfo["l1JetNoBptxNoHaloName"]=None
        return

    def Print(self):
        print "Name =",self.name
        print "trigger = ",self.trigger
        print "datatype=",self.datatype
        keys=self.InputInfo.keys()
        keys.sort()
        for k in keys:
            print k,self.InputInfo[k]

def GetDatasets():
    ''' Set dataset info for all  datasets.'''

    datasets={}

    ########################################
    # 2010 datasets

    #/MinimumBias/Run2010A-HSCPSD-Apr21ReReco-v2/RAW-RECO
    name="/MinimumBias/Run2010A-HSCPSD-Apr21ReReco-v2/RAW-RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2010",
                                    datatype="RAWRECO")
    #"RAWRECO" indicates RAW+RECO in makeTreeJob.py
    
    # What are the values for 2010 l1JetNobptxName, l1JetNoBptxNoHaloName?
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy"


    #/MinimumBias/Run2010B-HSCPSD-Apr21ReReco-v1/RAW-RECO
    name="/MinimumBias/Run2010B-HSCPSD-Apr21ReReco-v1/RAW-RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2010",
                                    datatype="RAWRECO")
    #"RAWRECO" indicates RAW+RECO in makeTreeJob.py
     
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy"

    ###############################################
    #2011 datasets

    ###############################################
    # first datasets use 'old' hltL3Tag 'hltStoppedHSCPTight1CaloJetEnergy30'

    # /MinimumBias/Run2011A-PromptReco-v2/RECO
    name="/MinimumBias/Run2011A-PromptReco-v2/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPTight1CaloJetEnergy30"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_NotBptxOR_NotMuBeamHalo'
    

    # /MinimumBias/Run2011A-HSCPSD-May10ReReco-v2/RECO
    # replaces promptreco-v2 above
    name="/MinimumBias/Run2011A-HSCPSD-May10ReReco-v2/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPTight1CaloJetEnergy30"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_NotBptxOR_NotMuBeamHalo'


    #############################################
    # newer 2011 datasets use new hltL3Tag 'hltStoppedHSCPCaloJetEnergy50'

    # /MinimumBias/Run2011A-HSCPSD-PromptSkim-v4/RECO
    name="/MinimumBias/Run2011A-HSCPSD-PromptSkim-v4/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_NotBptxOR_NotMuBeamHalo'


    # Beginning with this skim (c. fill 1960), l1JetNoBptx names change
    # /MinimumBias/Run2011A-HSCPSD-PromptSkim-v5/RECO
    name="/MinimumBias/Run2011A-HSCPSD-PromptSkim-v5/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    # /MinimumBias/Run2011A-HSCPSD-05Aug2011-v1/RECO
    # replaces PromptSkim v5 above; v5 had error
    name="/MinimumBias/Run2011A-HSCPSD-05Aug2011-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    # /MinimumBias/Run2011A-HSCPSD-PromptSkim-v6/RECO
    name="/MinimumBias/Run2011A-HSCPSD-PromptSkim-v6/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    # /MinimumBias/Run2011B-HSCPSD-PromptSkim-v1/RECO
    name="/MinimumBias/Run2011B-HSCPSD-PromptSkim-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    ################################################
    # Nov08 ReReco for all of 2011 into CMSSW_4_4_2
    #
    # I'm really not sure these values are right for
    # the 2011A dataset. There were so many different
    # settings in 2011A and I don't know what happened
    # when all of the various datasets were combined
    ################################################
    # /MinimumBias/Run2011A-HSCPSD-08Nov2011-v1/RECO
    name="/MinimumBias/Run2011A-HSCPSD-08Nov2011-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    # /MinimumBias/Run2011B-HSCPSD-19Nov2011-v1/RECO 
    name="/MinimumBias/Run2011B-HSCPSD-19Nov2011-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                                    trigger="2011",
                                    datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCPCaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJet20_Central_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJet20_Central_NotBptxOR_NotMuBeamHalo'

    #############################################
    # 2012 Datasets
    #############################################

    #/MinimumBias/Run2012A-PromptReco-v1/RECO
    name="/MinimumBias/Run2012A-PromptReco-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    #/MinimumBias/Run2012A-13Jul2012-v1/RECO
    name="/MinimumBias/Run2012A-13Jul2012-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'
                     
    #/NoBPTX/Run2012B-PromptReco-v1/RECO
    name="/NoBPTX/Run2012B-PromptReco-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'
                     
    #/NoBPTX/Run2012B-13Jul2012-v1/RECO
    name="/NoBPTX/Run2012B-13Jul2012-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'
                     
    #/NoBPTX/Run2012C-PromptReco-v1/RECO
    name="/NoBPTX/Run2012C-PromptReco-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'
                     
    #/NoBPTX/Run2012C-24Aug2012-v1/RECO
    name="/NoBPTX/Run2012C-24Aug2012-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'
                           
    #/NoBPTX/Run2012C-PromptReco-v2/RECO
    name="/NoBPTX/Run2012C-PromptReco-v2/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    name="/NoBPTX/Run2012D-PromptReco-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'


    ########################################
    # 22Jan2013 rereco datasets
    ########################################
    name="/MinimumBias/Run2012A-22Jan2013-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    name="/NoBPTX/Run2012B-22Jan2013-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    name="/NoBPTX/Run2012C-22Jan2013-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    name="/NoBPTX/Run2012D-22Jan2013-v1/RECO"
    datasets[name]=DatasetInfo(name=name,
                               trigger="2012",
                               datatype="RECO")
    datasets[name].InputInfo["hltL3Tag"]="hltStoppedHSCP1CaloJetEnergy50"
    datasets[name].InputInfo["l1JetNoBptxName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1JetNoBptxNoHaloName"]='L1_SingleJetC20_NotBptxOR'
    datasets[name].InputInfo["l1Jet32NoBptxNoHaloName"]='L1_SingleJetC32_NotBptxOR'

    return datasets



if __name__=="__main__":
    datasets=GetDatasets()
    if len(sys.argv)>1:
        name=sys.argv[1]
    else:
        name=raw_input("enter dataset name:")
    if name in datasets.keys():
        print "KEY = ",name
        datasets[name].Print()
