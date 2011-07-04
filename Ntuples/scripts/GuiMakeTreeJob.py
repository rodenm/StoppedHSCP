#!/usr/bin/python

from Tkinter import *
import sys, os, string
from optparse import OptionParser
sys.path.append(os.path.join(os.environ["CMSSW_BASE"],
                             "src/StoppedHSCP/Ntuples/scripts"))
#sys.path.append(os.path.join(os.environ["CMSSW_BASE"],
#                             "src/StoppedHSCP/Analysis/scripts"))
from make_tree_job_for_gui import makeTreeJob
from copyFiles import CopyFiles, copySites

class TreeJobGui:

    def __init__(self, parent=None):

        self.ReadInputs()

        if parent==None:
            self.main=Tk()
            self.main.title("TreeJob Generator")
        else:
            self.main=parent

        self.main.columnconfigure(0,weight=1)
        self.main.columnconfigure(1,weight=1)
        row=0
        self.TreeFrame=Frame(self.main)
        self.TreeFrame.columnconfigure(0,weight=1)
        self.CopyFrame=Frame(self.main)
        self.CopyFrame.columnconfigure(0,weight=1)

        self.TreeFrame.grid(row=row,column=0,sticky=EW)
        self.CopyFrame.grid(row=row,column=1,sticky=EW)
        # Fill Tree Gui
        self.FillTreeFrame(self.TreeFrame)
        self.FillCopyFrame(self.CopyFrame)

        # Create MessageFrame
        row=row+1
        self.MessageFrame=Frame(self.main)
        self.MessageFrame.grid(row=row,column=0,columnspan=2)
        self.MessageFrame.columnconfigure(0,weight=1)
        self.Comments=Label(self.MessageFrame,text="TreeJob Generator GUI")
        self.Comments.grid(row=0,column=0,sticky=EW)

        # Set up defaults for copy locations
        self.SetStorage()
        return

    def FillTreeFrame(self,parent):
        self.InFrame=Frame(parent)
        row=0
        self.InFrame.grid(row=row,column=0,sticky=EW)
        self.GridInFrame()
        row=row+1
        self.CrabFrame=Frame(parent)
        self.CrabFrame.grid(row=row,column=0)
        self.GridCrabFrame()
        row=row+1
        self.checkJSON()
        return

    def Print(self,message):
        print message
        try:
            self.Comments.configure(text=message)
            self.Comments.update()
        except:
            print "Could not configure Comments window for message '%s'"%message
        return


    def usage(self):
        return

    def ReadInputs(self):

        self.INuseLocalDBS = False
        self.INuseJSON = True  # default should be true, not false?
        self.INtrigger = '2011'
        self.INdatatype = 'RECO'
        self.INscheduler='glite'
        self.INwhitelist=None
        
        parser=OptionParser()
        parser.add_option("-l",action="store_true",
                          default=False,
                          dest="useLocalDBS",
                          help="Use Local DBS (http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet)"
                          )
        parser.add_option("-j",action="store_true",
                          default=True,
                          dest="useJSON",
                          help="use JSON file to run on good LS")
        parser.add_option("-c",action="store_true",
                          default=False,
                          dest="useCAF",
                          help="Use CAF")
        parser.add_option("-f",action="store_true",
                          default=False,
                          dest="useCONDOR",
                          help="Use FNAL (condor)")
        parser.add_option("-g",default="glite",
                          dest="scheduler",
                          help="Specify scheduler (default=glite)")
        parser.add_option("-t",dest="triggerType",
                          default="2011",
                          help="Specify trigger type (default is 2011)")
        parser.add_option("--2010",
                          dest="oldTriggerType",
                          default=False,
                          action="store_true",
                          help="Set trigger type to 2010")
        parser.add_option("--2011",
                          dest="newTriggerType",
                          default=False,
                          action="store_true",
                          help="Set trigger type to 2011") 
        parser.add_option("-r",
                          dest="myreco",
                          default="RECO",
                          help="Specify reco type (default=RECO)")
        parser.add_option("--raw",
                          dest="rawtype",
                          default=False,
                          action="store_true",
                          help="Set reco type to RAW+RECO")
        parser.add_option("--reco",
                          dest="recotype",
                          default=False,
                          action="store_true",
                          help="Set reco type to RECO")
        parser.add_option("--mc",
                          dest="mctype",
                          default=False,
                          action="store_true",
                          help="Set reco type to MC")
        parser.add_option("-w",
                          dest="whitelist",
                          default=None,
                          help="Specify CE whitelist")
        parser.add_option("-B",
                          dest="BristolWhiteList",
                          action="store_true",
                          default=False,
                          help="Use Bristol sites (heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk) for CE whitelist")
        parser.add_option("-E","--era",
                          dest="era", 
                          default=None,
                          help="Specify Era (e.g. Run2011A_414_v2)")
        parser.add_option("-L","--label",
                          dest="label",
                          default=None,
                          help="Specify Label (e.g. the fill range:  1711_1731")
        parser.add_option("-D","--dataset",
                          dest="dataset",
                          default=None,
                          help="Specify dataset")
        parser.add_option("-G","--globaltag",
                          dest="globaltag",
                          default=None,
                          help="Specify globaltag")
        parser.add_option("--json",
                          dest="json",
                          default=None,
                          help="Specify json file")
        parser.add_option("--runs",
                          dest="runs",
                          default=None,
                          help="Specify runlist file")
        parser.add_option("--storage",
                          dest="storage",
                          default="T2_UK_SGrid_RALPP",
                          help="Specify storage location (default is T2_UK_SGrid_RALPP)")
        parser.add_option("--hltL3Tag",
                          dest="hltL3Tag",
                          default="Default",
                          help="Specify hltL3Tag  (default is 'Default', which will use whatever is already specified in cfg file.)")
        parser.add_option("--newhlttag",
                          dest="newhlttag",
                          default=False,
                          action="store_true",
                          help="Specify new hltL3Tag (hltStoppedHSCPCaloJetEnergy50)")
        parser.add_option("--oldhlttag",
                          dest="oldhlttag",
                          default=False,
                          action="store_true",
                          help="Specify old hltL3Tag (hltStoppedHSCPTight1CaloJetEnergy30)")
        parser.add_option("-s",
                          "--site",
                          default="RAL",
                          help="Specify copysite location.  Choices are: %s"%copySites.keys()
                          )
        parser.add_option("-p",
                          "--srmcp",
                          default=False,
                          action="store_true",
                          help="Use srmcp to copy files.  Default is false (lcg is used by default.)")

        (options, args) = parser.parse_args()

        if options.newhlttag==True and options.oldhlttag==True:
                print "Cannot specify both old and new hlttags as true!  Pick one!"
        else:
            if options.newhlttag==True:
                if options.hltL3Tag=="Default":
                    options.hltL3Tag="hltStoppedHSCPCaloJetEnergy50"
                else:
                    print "Cannot specify both '--newhlttag' and a separate '--hltL3Tag'!"
                    print "Using the hltL3tag value '%s'"%options.hltL3Tag
            elif options.oldhlttag==True:
                if options.hltL3Tag=="Default":
                    options.hltL3Tag="hltStoppedHSCPTight1CaloJetEnergy30"
                else:
                    print "Cannot specify both '--oldhlttag' and a separate '--hltL3Tag'!"
                    print "Using the hltL3tag value '%s'"%options.hltL3Tag
            

        self.INuseLocalDBS=options.useLocalDBS
        self.INuseJSON=options.useJSON
        self.INscheduler=options.scheduler
        self.INhltL3Tag=options.hltL3Tag
        self.site=options.site
        self.srmcp=options.srmcp
        
        if options.useCAF==True and options.useCONDOR==True:
            self.Print( "Error!  Both CAF and CONDOR cannot be set to True!")
            sys.exit()
        if options.useCAF==True:
            self.INscheduler="caf"
        if options.useCONDOR==True:
            self.INscheduler="condor"

        if options.oldTriggerType==True and options.newTriggerType==True:
            self.Print( "Error!  Can't specify trigger type as both 2010 and 2011!")
            sys.exit()
        elif options.oldTriggerType==True:
            self.INtrigger="2010"
        elif options.newTriggerType==True:
            self.INtrigger="2011"
        else:
            self.INtrigger=options.triggerType

        if options.rawtype==True:
            self.INdatatype="RAWRECO"
        elif options.recotype==True:
            self.INdatatype="RECO"
        elif options.mctype==True:
            self.INdatatype=="MC"
        else:
            self.INdatatype=options.myreco

        if options.BristolWhiteList==True:
            self.INwhitelist="heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk"
        else:
            if (options.whitelist<>None):
                self.INwhitelist=options.whitelist
            else:
                self.INwhitelist="#heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk"


        self.INera=options.era
        self.INlabel=options.label
        self.INdataset=options.dataset
        self.INgtag=options.globaltag
        self.INjsonfile=options.json
        self.INruns=options.runs
        self.INstorage=options.storage
        self.outputloc=["T2_UK_SGrid_RALPP", "T2_CH_CAF",
                        "T2_US_Purdue", "T3_US_UMD"]
        if self.INstorage not in self.outputloc:
            self.outputloc.append(self.INstorage)
        else:
            self.outputloc.append("None")
        
        for a in args:
            #print a
            if self.INera==None:
                self.INera=a
                #print "era = ",a
            elif self.INlabel==None:
                self.INlabel=a
                #print "label = ",a
            elif self.INdataset==None:
                self.INdataset=a
                #print "dataset=",a
            elif self.INgtag==None:
                self.INgtag=a
            elif self.INuseJSON==True and self.INjsonfile==None:
                self.INjsonfile=a
                #print "jsonfile = ",a
            elif self.INuseJSON==False and self.INruns==None:
                self.INruns=a

        # Last argument is either jsonfile or runlist
        # Make them equal, but disable one based on whether useJSON is True
        if self.INjsonfile==None:
            self.INjsonfile=self.INruns
        if self.INruns==None:
            self.INruns=self.INjsonfile
                
        return
    

    def GridInFrame(self):
        self.InFrame.columnconfigure(1,weight=1)

        myvars=["era","label","dataset","gtag","jsonfile","runs","whitelist"] # remove "storage", as it's now an option menu

        row=0
        for v in myvars:
            exec("self.%s=StringVar()"%v)
            exec("self.%s.set(self.IN%s)"%(v,v))
            exec("self.%sL=Label(self.InFrame,text='%s:')"%(v,v))
            exec("self.%sE=Entry(self.InFrame,textvariable=self.%s,width=60)"%(v,v))
            exec("x=self.%s.get()"%v)
            if x=="None":
                exec("self.%sE.configure(state=DISABLED)"%v)
            if (v not in ["jsonfile","runs"]):
                exec("self.%sE.bind('<Double-Button-1>',lambda e,t=self:t.enableEntry(e,t.%sE))"%(v,v))
            exec("self.%sL.grid(row=%i,column=0)"%(v,row))
            exec("self.%sE.grid(row=%i,column=1,sticky=EW)"%(v,row))
            row=row+1

        # Set defaults
        if (self.era.get()=="None"):
            self.era.set("Run2011A_414_v2")
        if (self.label.get()=="None"):
            self.label.set("1711_1716")
        if (self.dataset.get()=="None"):
            self.dataset.set("/MinimumBias/Run2011A-PromptReco-v2/RECO")
        if (self.gtag.get()=="None"):
            self.gtag.set("GR_P_V17::All")
        return

    def enableEntry(self,event,entry):
        if entry.cget("state")=="disabled":
            entry.configure(state=NORMAL)
        return
    
    def checkJSON(self,val=None):
        if (val==None):
            val=self.useJSON.get()
        if val==True:
            self.jsonfileE.configure(state=NORMAL)
            self.runsE.configure(state=DISABLED)
        else:
            self.jsonfileE.configure(state=DISABLED)
            self.runsE.configure(state=NORMAL)
        return

    def SetStorage(self):
        if self.scheduler.get()=="caf":
            self.storage.set("T2_CH_CAF")
        else:
            # reset self.storage to input value
            if self.INstorage<>None:
                self.storage.set(self.INstorage)
        #Set grid location based on storage elements
        self.SetGridLoc()
        return

    def GridCrabFrame(self):
        self.CrabFrame.columnconfigure(1,weight=1)

        row=0
        self.storage=StringVar()
        self.storage.set(self.INstorage)
        self.storageMenu=OptionMenu(self.CrabFrame,self.storage,
                                    self.outputloc[0],
                                    self.outputloc[1],
                                    self.outputloc[2],
                                    self.outputloc[3],
                                    command = lambda y=self.storage.get():self.SetGridLoc(y))
        self.storageMenu["width"]=15
        self.storageL=Label(self.CrabFrame,text="storage:")
        self.storageL.grid(row=row,column=0)
        self.storageMenu.grid(row=row,column=1,sticky=EW)
        row=row+1
        
        self.scheduler=StringVar()
        self.schedulerchoices=["glite","caf","condor"]
        if self.INscheduler not in self.schedulerchoices:
            self.schedulerchoices.append(self.INscheduler)
        else:
            self.schedulerchoices.append(None)  # ugly hack, because 'command' in option menu apparently can't be set outside initial declaration
        self.scheduler.set(self.INscheduler)

        if (self.INscheduler=="caf"):
            self.storage.set("T2_CH_CAF")

        #else:
        #    self.storage.set("T2_UK_SGrid_RALPP")
        self.schedulerMenu=OptionMenu(self.CrabFrame,self.scheduler,
                                      "glite","caf","condor",self.schedulerchoices[3],

                                      command=lambda y=self.scheduler.get(): self.SetStorage())
        self.schedulerMenu["width"]=15

        self.schedulerL=Label(self.CrabFrame,text="scheduler:")
        self.schedulerL.grid(row=row,column=0)
        self.schedulerMenu.grid(row=row,column=1,sticky=EW)
        row=row+1

        self.useLocalDBS=BooleanVar()
        self.useLocalDBS.set(self.INuseLocalDBS)
        self.useLocalDBSchoices=[True,False]
        if self.INuseLocalDBS not in self.useLocalDBSchoices:
            self.Print( "ERROR!  Input UseLocal DBS choice '%s' not in available list of choices!"%self.INuseLocalDBS)
        self.useLocalDBSMenu=OptionMenu(self.CrabFrame,self.useLocalDBS,
                                      *self.useLocalDBSchoices)
        self.useLocalDBSMenu["width"]=15
        self.useLocalDBSL=Label(self.CrabFrame,text="useLocalDBS:")
        self.useLocalDBSL.grid(row=row,column=0)
        self.useLocalDBSMenu.grid(row=row,column=1,sticky=EW)
        row=row+1

        self.useJSON=BooleanVar()
        self.useJSON.set(self.INuseJSON)
        self.useJSONchoices=[True,False]
        if self.INuseJSON not in self.useJSONchoices:
            self.Print( "ERROR!  Input Use JSON choice '%s' not in available list of choices!"%self.INuseJSON)
        self.useJSONMenu=OptionMenu(self.CrabFrame,
                                    self.useJSON,
                                    #*self.useJSONchoices,
                                    True, False,
                                    command=lambda y=self.useJSON.get(): self.checkJSON(y)
                                    )
        self.useJSONMenu["width"]=15
        self.useJSONL=Label(self.CrabFrame,text="useJSON:")
        self.useJSONL.grid(row=row,column=0)
        self.useJSONMenu.grid(row=row,column=1)
        row=row+1
        
        self.trigger=StringVar()
        self.triggerchoices=["2010","2011"]
        self.trigger.set(self.INtrigger)
        if self.INtrigger not in self.triggerchoices:
            self.triggerchoices.append(self.INtrigger)
        self.triggerMenu=OptionMenu(self.CrabFrame,self.trigger,
                                      *self.triggerchoices)
        self.triggerMenu["width"]=15
        self.triggerL=Label(self.CrabFrame,text="trigger:")
        self.triggerL.grid(row=row,column=0)
        self.triggerMenu.grid(row=row,column=1)
        row=row+1

        self.datatype=StringVar()
        self.datatypechoices=["RECO","RAWRECO","MC"]
        self.datatype.set(self.INdatatype)
        if (self.INdatatype not in self.datatypechoices):
            self.datatypechoices.append(self.INdatatype)
        self.datatypeMenu=OptionMenu(self.CrabFrame,self.datatype,
                                      *self.datatypechoices)
        self.datatypeMenu["width"]=15
        self.datatypeL=Label(self.CrabFrame,text="datatype:")
        self.datatypeL.grid(row=row,column=0)
        self.datatypeMenu.grid(row=row,column=1)
        row=row+1
        self.hltL3Tag=StringVar()
        self.hltL3Tagchoices=["Default","hltStoppedHSCPTight1CaloJetEnergy30","hltStoppedHSCPCaloJetEnergy50"]
        if self.INhltL3Tag not in self.hltL3Tagchoices:
            self.hltL3Tagchoices.append(self.INhltL3Tag)
        self.hltL3Tag.set(self.INhltL3Tag)
        self.hltL3TagMenu=OptionMenu(self.CrabFrame,self.hltL3Tag,
                                      *self.hltL3Tagchoices)
        self.hltL3TagMenu["width"]=35
        self.hltL3TagL=Label(self.CrabFrame,text="hltL3Tag:")
        self.hltL3TagL.grid(row=row,column=0)
        self.hltL3TagMenu.grid(row=row,column=1)
        row=row+1

        self.MakeTreeButton=Button(self.CrabFrame,text="Make\nTree\nJob",
                                   command=lambda x=self:x.MakeTreeJob(),
                                   height=row,width=20,bg="blue",fg="white")
        self.MakeTreeButton.grid(row=0,column=2,rowspan=row)

        return


    def SetGridLoc(self,storage=None):
        key=""
        if self.storage.get()=="T2_UK_SGrid_RALPP":
            key="RAL"
        elif self.storage.get()=="T2_CH_CAF":
            key="CAF"
        elif self.storage.get()=="T2_US_Purdue":
            key="PUR"
        elif self.storage.get()=="T3_US_UMD":
            key="UMD"

        if key not in copySites.keys():
            self.gridroot.set("")
            self.gridloc.set("")
        else:
            self.gridroot.set(copySites[key][0])
            self.gridloc.set(copySites[key][1])
        # Add other grid sites as necessary
        return

    def MakeTreeJob(self):

        if self.eraE.cget("state")=="disabled":
            self.Print("Must explicitly specify ERA!  \n(Double-click entry box to activate)")
            return
        if self.labelE.cget("state")=="disabled":
            self.Print("Must explicitly specify LABEL!  \n(Double-click entry box to activate)")
            return
        if self.datasetE.cget("state")=="disabled":
            self.Print("Must explicitly specify DATASET!  \n(Double-click entry box to activate)")
            return
        if self.gtagE.cget("state")=="disabled":
            self.Print("Must explicitly specify GLOBAL TAG!  \n(Double-click entry box to activate)")
            return
        if (self.useJSON.get()==True and self.jsonfileE.cget("state")=="disabled"):
            self.Print("Must explicitly specify JSON file!  \n(Toggle useJSON variable to activate)")
            return

        if (self.useJSON.get()==False and self.runsE.cget("state")=="disabled"):
            self.Print("Must explicitly specify RUN file \n(Toggle useJSON variable to activate)")
            return
        


        if self.scheduler.get()=="caf" and self.storage.get()<>"T2_CH_CAF":
            self.Print( "Warning!  CAF should only be run using storage at T2_CH_CAF\nProceed with caution!")
        
        elif self.scheduler.get()<>"caf" and self.storage.get() not in self.outputloc:
            self.Print( "Warning!  Storage output location '%s' differs from expected choices: %s \nProceed with caution! "%(self.storage.get(),self.outputloc))



        if (self.useJSON.get()==True):
            myfile=self.jsonfile.get()
        else:
            myfile=self.runs.get()

        if not os.path.isfile(myfile):
            self.Print ("ERROR!  Runs/Json File '%s' does not exist!"%myfile)
            return

        # print table

        print "Writing info for elog to 'table_info.txt'"

        outtable="table_info.txt"
        x=makeTreeJob(era=self.era.get(),
                      label=self.label.get(),
                      dataset=self.dataset.get(),
                      gtag=self.gtag.get(),
                      runjsonfile= myfile,
                      scheduler=self.scheduler.get(),
                      storage=self.storage.get(),
                      useLocalDBS=self.useLocalDBS.get(),
                      useJSON=self.useJSON.get(),
                      trigger=self.trigger.get(),
                      datatype=self.datatype.get(),
                      whitelist=self.whitelist.get(),
                      hltL3Tag=self.hltL3Tag.get(),
                      outtable=outtable)

        if os.path.exists(outtable):
            outfile=open("table_info.txt",'a')
        else:
            outfile=open("table_info.txt",'w')
        outfile.write( '\n[TABLE border="1"]\n')
        thename="%s_%s"%(self.era.get(),self.label.get())
        outfile.write( "Name | %s |-\n"%thename)
        try:
            temp=string.split(self.label.get(),"_")
            outfile.write( "Fills | %s-%s |-\n"%(temp[0],temp[1]))
        except IndexError:
            outfile.write( "Fills | %s |-\n"%self.label.get())
        outfile.write( "Runs    |      |-\n")
        outfile.write( "Ntuples | %s%s/stoppedHSCP_tree_%s |-\n"%(self.gridroot.get(),os.path.join(self.gridloc.get(),self.user.get()),thename))
        outfile.write( "Lumi    |      |-\n")
        outfile.write( "Dataset  | %s |-\n"%self.dataset.get())
        outfile.write( "Global Tag | %s |-\n"%self.gtag.get())
        try:
            outfile.write( "CMSSW Version | %s |-\n"%os.environ["CMSSW_VERSION"])
        except KeyError:
            outfile.write( "CMSSW Version | NOT SPECIFIED! |-\n")
        outfile.write( "CVS tag  |      |-\n")
        if (self.useJSON.get()==True):
            outfile.write( "JSON file | %s |-\n"%myfile)
        else:
            outfile.write( "JSON file | NOT SPECIFIED! |-\n")
        outfile.write( "[/TABLE]\n\n")
        outfile.close()
        
        if (x==True):
            self.Print("cfg files successfully produced!")
        return


    # Make Copy Frame
    def FillCopyFrame(self,parent):
        #parent.configure(bg="blue")
        self.user=StringVar()
        self.gridroot=StringVar()
        self.gridloc=StringVar()
        self.copydataset=StringVar()
        self.copyoutputdir=StringVar()
        self.verbose=BooleanVar()
        self.overwrite=BooleanVar()
        self.listfiles=BooleanVar()

        self.user.set("jbrooke")
        if os.environ["USER"].find("temple")>-1:
            self.user.set("temple")  # Set to Jeff's grid user name, if user ID'd as Jeff (either temple or jtemple)
        self.gridroot.set("srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN=")
        self.gridloc.set("/pnfs/pp.rl.ac.uk/data/cms/store/user/")
        self.copydataset.set("")
        if (os.path.isdir("/storage/phjjb/stoppedHSCP/")):
            self.odir.set("/storage/phjjb/stoppedHSCP/")
        self.verbose.set(False)
        self.overwrite.set(False)
        self.listfiles.set(False)

        parent.columnconfigure(0,weight=1)
        Label(parent,text="Copy File Utility\n(Run after ntuples from tree job are created)").grid(row=0,column=0,columnspan=2)
        
        self.CopyFrame1=Frame(parent)
        self.CopyFrame1.columnconfigure(1,weight=1)
        self.CopyFrame1.grid(row=1,column=0,sticky=EW)
        #parent.columnconfigure(1,weight=1)
        self.CopyFrame2=Frame(parent)
        self.CopyFrame2.columnconfigure(1,weight=1)
        self.CopyFrame2.grid(row=2,column=0,sticky=EW)
        row=0
        Label(self.CopyFrame1,text="Grid Root = ").grid(row=row,column=0)
        self.gridrootE=Entry(self.CopyFrame1,width=60,textvariable=self.gridroot)
        self.gridrootE.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame1,text="Grid Loc = ").grid(row=row,column=0)
        self.gridlocE=Entry(self.CopyFrame1,width=60,textvariable=self.gridloc)
        self.gridlocE.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame1,text="User = ").grid(row=row,column=0)
        self.userE=Entry(self.CopyFrame1,width=60,textvariable=self.user)
        self.userE.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame1,text="Dataset = ").grid(row=row,column=0)
        self.copydatasetE=Entry(self.CopyFrame1,width=60,textvariable=self.copydataset)
        self.copydatasetE.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame1,text="Output directory\nfor copied files = ").grid(row=row,column=0)
        self.copyoutputdirE=Entry(self.CopyFrame1,width=60,textvariable=self.copyoutputdir)
        self.copyoutputdirE.grid(row=row,column=1,sticky=EW)
        row=0
        Label(self.CopyFrame2,text="Verbose = ").grid(row=row,column=0)
        self.verboseMenu=OptionMenu(self.CopyFrame2,
                                    self.verbose,
                                    True, False,
                                    #command=lambda y=self.useJSON.get(): self.checkJSON(y)
                                    )
        self.verboseMenu.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame2,text="Overwrite = ").grid(row=row,column=0)
        self.overwriteMenu=OptionMenu(self.CopyFrame2,
                                      self.overwrite,
                                      True, False,
                                      #command=lambda y=self.useJSON.get(): self.checkJSON(y)
                                      )
        self.overwriteMenu.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame2,text="List (don't copy) files:").grid(row=row,column=0)
        self.listfileMenu=OptionMenu(self.CopyFrame2,
                                     self.listfiles,
                                     True, False,
                                     command=lambda x=self:self.SwitchListFileButtonName())
        self.listfileMenu.grid(row=row,column=1,sticky=EW)
        row=row+1
        Label(self.CopyFrame2,text="Specify copy location").grid(row=row,column=0)
        self.sourceLocationVar=StringVar()
        self.sourceLocationVar.set(self.site)
        self.sourceLocation=OptionMenu(self.CopyFrame2,
                                       self.sourceLocationVar,
                                       "RAL","CAF","PUR","UMD","",  # How do we specify these from *copySites?
                                       command=lambda x=self:self.SwitchSourceLocation() 
                                      )

        self.sourceLocation.grid(row=row,column=1,sticky=EW)
        row=row+1

        self.copyTypeVar=StringVar()
        if self.srmcp==True:
            self.copyTypeVar.set("srmcp")
        else:
            self.copyTypeVar.set("lcg")
        self.CopyType=OptionMenu(self.CopyFrame2,
                                 self.copyTypeVar,
                                 "lcg","srmcp")
        Label(self.CopyFrame2,text="Copy type:").grid(row=row,column=0)
        self.CopyType.grid(row=row,column=1,sticky=EW)
        row=row+1
        self.CopyButton=Button(self.CopyFrame2,text="\nCopy\nFiles\n",command = lambda x=self:x.CopyFiles(),width=20,bg="blue",fg="white")
        row=row+1
        self.CopyButton.grid(row=row,column=1)
        return

    def SwitchSourceLocation(self):
        if self.sourceLocationVar.get() in copySites.keys():
            temp=copySites[self.sourceLocationVar.get()]
            self.gridroot.set(temp[0])
            self.gridloc.set(temp[1])
        return

    def SwitchListFileButtonName(self):
        if self.listfiles.get()==True:
            self.CopyButton.configure(text="\nList\nFiles\n")
        else:
            self.CopyButton.configure(text="\nCopy\nFiles\n")
        self.CopyButton.update()
        return

    def CopyFiles(self):

        if self.gridroot.get()=="":
            self.Print("ERROR:  No grid root value specified!")
            return
        if self.gridloc.get()=="":
            self.Print("ERROR:  No grid loc value specified!")
            return
        if (self.listfiles.get()==False):
            if self.copydataset.get()=="":
                self.Print("ERROR:  No copy dataset value specified!")
                return
            if not os.path.isdir(self.copyoutputdir.get()):
                self.Print("ERROR!  Copy Output directory '%s' does not exist!"%self.copyoutputdir.get())
                return
        try:
            crabdir=os.environ["CRABDIR"]
        except KeyError:
            self.Print("ERROR!  CRAB DOES NOT APPEAR TO HAVE BEEN SET UP!")
            return
        # use string strip to avoid white spaces that confuse copyFiles
        srmcp=False
        if (self.copyTypeVar.get()=="srmcp"):
            srmcp=True
        CopyFiles(user=string.strip(self.user.get()),
                  gridroot=string.strip(self.gridroot.get()),
                  gridloc=string.strip(self.gridloc.get()),
                  dataset=string.strip(self.copydataset.get()),
                  odir=string.strip(self.copyoutputdir.get()),
                  verbose=self.verbose.get(),
                  overwrite=self.overwrite.get(),
                  listfiles=self.listfiles.get(),
                  srmcp=srmcp)

    ###############################################################

if __name__=="__main__":


    x=TreeJobGui()
    x.main.mainloop()
