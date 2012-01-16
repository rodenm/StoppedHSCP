#include "StoppedHSCP/Analysis/interface/RunReducedHistograms.h"
#include "StoppedHSCP/Analysis/interface/BadRuns.h"


RunReducedHistograms::RunReducedHistograms(TFile* outfile, 
					   std::vector<std::string> ifiles,
					   LhcFills* fills) :
  fills_(fills),
  base_()
{
  // create directory structure
  outfile->mkdir("runsReduced");
  base_ = outfile->GetDirectory("runsReduced");
  base_->cd();

  // book histograms by identifying runs
  std::map<unsigned long,unsigned long> LSPerRun;
  std::map<unsigned long,unsigned long> EventsPerRun;
  unsigned long firstrun=999999;
  unsigned long lastrun=0;
  int nruns=0;
  for (unsigned i=0;i<ifiles.size();++i)
    {
      TFile *mytest=new TFile(ifiles[i].c_str(),"READ");
      // Look in subsidiary histograms to get full list of lumi sections
      // (even for events that didn't pass "REDUCED" cuts)
      TDirectory* thisdir=mytest->GetDirectory("stoppedHSCPHistograms");
      TDirectory* thissubdir=thisdir->GetDirectory("runs");
      TIter nextkey(thissubdir->GetListOfKeys());
      TKey *key;
      
      while ((key = (TKey*)nextkey()))
	{
	  
	  std::string thisName = std::string(key->GetName());

	  /* Instead of taking number of lumi sections from hLS_ histograms
	     (filled once at each beginLuminosityBlock call),
	     require that there be at least one event in the lumi section
	     (using the hEventLS_ histograms below).  This keeps with 
	     the earlier definitiona of valid lumi blocks in runs/hrunlb
	  */
	  if (thisName.find("hLS_")==0)
	    {
	    /*
	    unsigned long thisRun =(unsigned long)atol((thisName.substr(4)).c_str());
	    // Take number of lumi sections from sections with at least one event (hEventLS_, below)
	    
	    TH1F* thisHist=(TH1F*) key->ReadObj();
	    unsigned long NLS = thisHist->Integral();
	    //for (int bin=1;bin<=thisHist->GetNbinsX();++bin)
	      //if (thisHist->GetBinContent(bin)>0) ++NLS;
	      
	      if (LSPerRun.find(thisRun)==LSPerRun.end())
		{
		  LSPerRun[thisRun]=NLS;
		  ++nruns;
		}
	      else
		  LSPerRun[thisRun]+=NLS;
	      */
	    }
	  if (thisName.find("hEventLS_")==0)
	    {
	      unsigned long thisRun =(unsigned long)atol((thisName.substr(9)).c_str());
	      //std::cout <<"RUNREDUCED RUN = "<<thisRun<<std::endl;
	      if (isBadRun(thisRun)) 
		{
		  //std::cout <<"RUNREDUCED BAD RUN "<<thisRun<<std::endl;
		  continue;
		}
	      if (thisRun>lastrun)
		lastrun=thisRun;
	      if (thisRun<firstrun)
		firstrun=thisRun;
	      TH1F* thisHist=(TH1F*) key->ReadObj();
	      unsigned long NLS = 0;
	      for (int bin=1;bin<=thisHist->GetNbinsX();++bin)
		if (thisHist->GetBinContent(bin)>0) ++NLS;
	      if (NLS>0)
		{
		  if (LSPerRun.find(thisRun)==LSPerRun.end())
		    {
		      LSPerRun[thisRun]=NLS;
		      ++nruns;
		    }
		  else
		    LSPerRun[thisRun]+=NLS;
		}
	      unsigned long NEvent = thisHist->Integral();
	      if (EventsPerRun.find(thisRun)==EventsPerRun.end())
		EventsPerRun[thisRun]=NEvent;
	      else
		EventsPerRun[thisRun]+=NEvent;
	    }

	} // loop over keys (i.e., histograms for individual runs) in stoppedHSCPHistograms subdirectory
    } //loop over input files

  hEventsPerRun_   = new TH1D("hrunevt_REDUCED","HLT counts",nruns,0.,0.);
  hLiveTimePerRun_ = new TH1D("hruntime_REDUCED","Live time",nruns,0.,0.);
  hLSPerRun_       = new TH1D("hrunlb_REDUCED","N lumi blocks",nruns,0.,0.);

  // fill histograms
  std::map<unsigned long,unsigned long>::const_iterator it;
  for (it=LSPerRun.begin();it!=LSPerRun.end();++it)
    {
      unsigned long run=it->first;
      std::stringstream runss;
      runss<<run;
      std::string runstr=runss.str();
      hLSPerRun_->Fill(runstr.c_str(),it->second);
      hLiveTimePerRun_->Fill(runstr.c_str(), it->second*TIME_PER_LS*fills->getLiveFractionFromRun(it->first));
    }
  for (it=EventsPerRun.begin();it!=EventsPerRun.end();++it)
    {
      unsigned long run=it->first;
      std::stringstream runss;
      runss<<run;
      std::string runstr=runss.str();

      hEventsPerRun_->Fill(runstr.c_str(),it->second);
    }
}


RunReducedHistograms::~RunReducedHistograms() {

}

void RunReducedHistograms::save() {

}


void RunReducedHistograms::summarise() {

  base_ ->cd();
  hLSPerRun_->Write("",TObject::kOverwrite);
  hLiveTimePerRun_->Write("",TObject::kOverwrite);
  hEventsPerRun_->Write("",TObject::kOverwrite);

}


