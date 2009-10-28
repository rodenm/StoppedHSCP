#include <TCanvas>

class SignalDataCompare 
{
public:	
  SignalDataComapare(GlobalRun *, SignalOneFile*);
  void GetSigBackPlot(int, string, TCut, int, float, float, string = "", int = 0 );
  void GetSigBackPlot(int, int, string, string, TCut, TCut, int, float, float, string = "", int = 0);
  void GetLogSigBackPlot(int, string, TCut, int, float, float, string = "", int = 0 );
  TCanvas * GetCurrentCanvas() {return CurrentCanvas;}

private:
  GlobalRun * mBackground;
  SignalOneFile * mSignal;
  TCanvas * CurrentCanvas;

};	




SignalDataCompare::SignalDataCompare(CraftRun * Background, SignalOneFile * Signal)
{	
  if(Background->IsGood())
    mBackground = Background;
  else
    std::cout<<"ERROR : Background object not valid"<<std::endl; 
 
  if(Signal->IsGood())
    mSignal = Signal;
  else
    std::cout<<"ERROR : Signal object not valid"<<std::endl;
}



TCanvas * SignalDataCompare::GetLogSigBackPlot(int Chain, string Var, TCut Cut, int Divs, float Min, float Max, string Title, int NormMode)
{
  TCanvas * TC1 =  GetSigBackPlot(Chain, Chain, Var, Var, Cut, Cut, Divs, Min, Max, Title, ,NormMode);
  TC1->SetLogy();
}


TCanvas *  SignalDataCompare::GetSigBackPlot(int Chain, string Var, TCut Cut, int Divs, float Min, float Max, string Title, int NormMode)
{
  return GetSigBackPlot(Chain, Chain, Var, Var, Cut, Cut, Divs, Min, Max, Title,NormMode);
}




TCanvas *  SignalDataCompare::GetSigBackPlot(int Chain1, int Chain2, string Var1, string Var2, TCut Cut1, TCut Cut2, int Divs, float Min, float Max, string Title, int NormMode)
{ 

  
  TH1D * histBg = new TH1D("HistBg","HistBg",Divs,Min,Max);
  TH1D * histSig = new TH1D("HistSig","HistSig",Divs,Min,Max);
       
  TChain * myChainBg = mBackground->GetChain(Chain1); 
  TChain * myChainSig = mSignal->GetChain(Chain2);

  stringstream DrawCommand;

  DrawCommand.flush();
  DrawCommand<<Var1;
  DrawCommand<<">>HistBg";
  std::cout<<"Drawing:  "<<   DrawCommand.str()<<",  " << string(Cut1)<<std::endl;
  myChainBg->Draw(DrawCommand.str().c_str(), Cut1, "goff");
  
  DrawCommand.str("");
  DrawCommand<<Var2;
  DrawCommand<<">>HistSig";
  std::cout<<"Drawing:  "<<   DrawCommand.str()<<",  " << string(Cut2)<<std::endl;
  myChainSig->Draw(DrawCommand.str().c_str(),Cut2,"goff");
 
 
  histBg->SetFillColor(kGray);
  histBg->SetLineColor(kBlack);
  histSig->SetLineColor(kBlue);
  histSig->SetLineWidth(2);
  
  TCanvas * TC1 = new TCanvas;
  TC1->cd();
  
  
  if(NormMode==0)
    {
      histBg->Scale(1./histBg->Integral());
      histSig->Scale(1./histSig->Integral());
    }
  
  if(NormMode==1)
    {
      histBg->Scale(1./histBg->GetMaximum());
      histSig->Scale(1./histSig->GetMaximum());
    }

  if(NormMode==2)
    {
      histBg->Scale(1.);
      histSig->Scale(1.);
    }

  if(histBg->GetMaximum() < histSig->GetMaximum())
    {
      histBg->GetYaxis()->SetRangeUser(0,1.1*histSig->GetMaximum());
    }
  else
    {
      histBg->GetYaxis()->SetRangeUser(0,1.1*histBg->GetMaximum());
    }
  histBg->SetXTitle(Title.c_str());
  histBg->Draw();
  histSig->Draw("Same");
  CurrentCanvas = TC1;
  return TC1;


}
