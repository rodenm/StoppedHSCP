#include "ChainCollection.C"

class GlobalRun : public ChainCollection
{
public:

  GlobalRun();


 
  float                GetRunLength();        //done
  
  int                  GetNoOfLumis();        //done

  float                GetDeadTime() { return 91*GetNoOfDeadLumis();}  

  float                GetLiveTime() { return 91*GetNoOfLiveLumis();}

  float                GetNoOfLiveLumis();    //done

  int                  GetNoOfDeadLumis();    //done

  int                  GetFirstLiveLumi();    //done
  
  int                  GetLastLiveLumi();     //done
  
  TH1D *               GetRatePlot(int, TCut="");

  TH1D *               GetRateProfile(int, TCut="");

  TH1D *               GetHistogram(int, string, int, float, float, TCut="", string="",string="" );

  void                 DrawRates(int, TCut="");     

  void                 MakeTimingPlots(int, TCut="");

public:
  
  int TOPLUMI;
  

  
};






void MakeTimingPlots(int ID, TCut Cut)
{
  if(Check(ID))
    {
      TCanvas *TC1 = new TCanvas;
      TC1->cd();
      TC1->SetLogy();
      TH1D * hist1 = new TH1D("hist1","hist1",100,0,400);
      GetChain(ID)->Draw("TimingLast2Bins>>hist1",Cut);
      hist1->SetXTitle("Energy in Last 2 Bins");
      hist1->SetYTitle("Arbitrary units");
      
      TCanvas *TC2 = new TCanvas;
      TC2->cd();
      TC2->SetLogy();
      TH1D * hist2 = new TH1D("hist2","hist2",100,0,400);
      GetChain(ID)->Draw("TimingFirst2Bins>>hist2",Cut);
      hist2->SetXTitle("Energy in First 2 Bins");
      hist2->SetYTitle("Arbitrary Units");
      
      TCanvas *TC3 = new TCanvas;
      TC3->cd();
      TH2D * hist3 = new TH2D("hist3","hist3",20,0,1,20,0,1);
      GetChain(ID)->Draw("TimingRightPeak:TimingFracRightNextRight>>hist3",Cut);
      hist3->SetYTitle("BX_Peak+1 / BX_Peak");
      hist3->SetXTitle("BX_Peak+2 / BX_Peak+1");
      hist3->Draw("cont0");
      
      TCanvas * TC4= new TCanvas;
      TC4->cd();
      hist3->Draw("surf1");
      
      TCanvas * TC5 = new TCanvas;
      TC5->cd();
      TH1D * hist5 = new TH1D("hist5","hist5",50,0,1);
      GetChain(ID)->Draw("TimingFracInLeader>>hist5",Cut);
      hist5->SetXTitle("Fraction Of Energy In Peak BX");
      hist5->SetYTitle("Arbitrary Units");
      hist5->Draw();
    }
}






TH1D * GlobalRun::GetHistogram(int ID, string Variable, int Divs, float Min, float Max, TCut Cut, string XTitle, string YTitle)
{
  if(CheckID(ID))
    {
      TH1D * NewHist = new TH1D("hist1","hist1",Divs,Min,Max);
      std::stringstream Command;
      Command.str("");
      Command << Variable << ">>hist1";
      GetChain(ID)->Draw(Command.str().c_str(), Cut, "goff");
      NewHist->SetXTitle(XTitle.c_str());
      NewHist->SetYTitle(YTitle.c_str());
      NewHist->Draw();
      return NewHist;
    }   
}








TH1D * GlobalRun::GetRatePlot(int ID, TCut Cut)
{
  TH1D * TimePlot = new TH1D("Temp","Temp",TOPLUMI,0,TOPLUMI);
  GetChain(ID)->Draw("LumiNumber>>Temp",Cut,"goff");
  int ActualTopLumi;
  for(int i=TOPLUMI; i!=0; i--)
    {
      if(TimePlot->GetBinContent(i)!=0)
	{
	  ActualTopLumi=i;
	  break;
	}   
    }
  stringstream HistoName;
  HistoName<<"Rate"<<ID;
  TH1D * CutTimePlot = new TH1D(HistoName.str().c_str(),HistoName.str().c_str(),ActualTopLumi, 0, ActualTopLumi);
  for(int i=0; i!=ActualTopLumi; i++)
    {
      CutTimePlot->Fill(i, TimePlot->GetBinContent(i));
    }
  delete TimePlot;
  return CutTimePlot;
}







TH1D * GlobalRun::GetRateProfile(int ID, TCut Cut)
{
  
  TH1D * RateHisto = GetRatePlot(ID, Cut); 
  stringstream HistoName;
  HistoName << "Rate"<<ID<<std::endl;
  TH1D * LumiPlot = new TH1D(HistoName.str().c_str(), HistoName.str().c_str(), 200, 0, RateHisto->GetMaximum()*1.2/91.);

  for(int i=0; i!=RateHisto->GetNbinsX(); i++)
    {
      LumiPlot->Fill(RateHisto->GetBinContent(i)/91.);
    }
  return LumiPlot;

}











GlobalRun::GlobalRun()
{
  TOPLUMI=1000;
}



float GlobalRun::GetRunLength()
{
  if(CheckID(1))
    {
      return ( (GetLastLiveLumi()-GetFirstLiveLumi())*91 );
    } 
}



int GlobalRun::GetFirstLiveLumi()
{

if(CheckID(1))
    {
      TheHist=GetRatePlot(1);
      int TopBin= TheHist->GetNbinsX();
      for(int i=0; i!=TopBin; i++)
	{
	  if(TheHist->GetBinContent(i)>0)
	    {
	      return i;
	      break;
	    }
	}
    }
  else 
    return -1;
}




int GlobalRun::GetLastLiveLumi()
{

 if(CheckID(1))
    {
      TheHist=GetRatePlot(1);
      int TopBin= TheHist->GetNbinsX();
      for(int i=TopBin; i!=0; i--)
	{
	  if(TheHist->GetBinContent(i)>0)
	    {
	      return i;
	      break;
	    }
	}
    }
  else 
    return -1;

}







int GlobalRun::GetNoOfLiveLumis()
{
  int Count=0;
  if(CheckID(1))
    {
      TH1D * TheHist = GetRatePlot(1);
      for(int i=0; i!=TheHist->GetNbinsX(); i++)
	{
	  if(TheHist->GetBinContent(i)!=0)
	    Count++;
	}
    }
  return Count;
}



int GlobalRun::GetNoOfDeadLumis()
{
  int Count=0;
  if(CheckID(1))
    {
      TH1D * TheHist = GetRatePlot(1);
      for(int i=0; i!=TheHist->GetNbinsX(); i++)
	{
	  if(TheHist->GetBinContent(i)==0)
	    Count++;
	}
    }
  return Count;
}



void GlobalRun::DrawRates(int ID, TCut Cut)
{
  if(CheckID(ID))
    {

      TCanvas * TC1 = new TCanvas;
      TCanvas * TC2 = new TCanvas;

      TH1D * RateProfile=GetRateProfile(ID,Cut);
      TH1D * RatePlot=GetRatePlot(ID,Cut);
    
      stringstream HistoName;
      HistoName << "Rate of module " << mModule[ID] << " throughout run ";

      TC1->cd();
      RatePlot->SetXTitle("Lumi Section Number");
      RatePlot->SetYTitle("Rate / Hz");
      RatePlot->SetTitle(HistoName.str().c_str()); 
      RatePlot->Draw();
      
      HistoName.str("");
      HistoName << "Distribution of rates per lumi section for module " <<mModule[ID] << "throughout run" ;

      TC2->cd();
      RateProfile->SetXTitle("Rate / Hz");
      RateProfile->SetYTitle("Lumi Section Count");
      RateProfile->SetTitle(HistoName.str().c_str());
      RateProfile->Draw();
    }

}
