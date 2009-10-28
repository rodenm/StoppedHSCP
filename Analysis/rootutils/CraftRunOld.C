#include "GlobalRun.C"


class CraftRunOld : public GlobalRun
{

public:
  

     CraftRunOld(string, int);
     PrintEfficiencies(CutCollection *);
     PrintRates(CutCollection *);
     PrintEfficiencies();
     PrintRates();
  
};





CraftRunOld::CraftRunOld(string Directory, int NoOfFiles)
{
  std::vector<string> Names;
  std::vector<string> Modules;

  Names.push_back("BOF");              Modules.push_back("BOF");
  Names.push_back("All");              Modules.push_back("an_HLT_1l1trigger/EventTree");
  Names.push_back("L1");               Modules.push_back("an_HLT_1l1trigger/EventTree");
  Names.push_back("HLT");              Modules.push_back("an_HLT_4energycut/EventTree");
  //  Names.push_back("L1Central");        Modules.push_back("l1jetfilter/L1CenTree");
  //  Names.push_back("L1Tau");            Modules.push_back("l1jetfilter/L1TauTree");


  AddMultiple(Names,Modules,Directory.c_str(),"Filter_Data_Histos",NoOfFiles);


}


void CraftRunOld::PrintRates()
{
  CraftCuts * CC = new CraftCuts();
  PrintRates(CC);
}

void CraftRunOld::PrintEfficiencies()
{
  CraftCuts * CC = new CraftCuts();
  PrintEfficiencies(CC);
}


void CraftRunOld::PrintEfficiencies(CutCollection * CC)
{
  int TotalEvents = GetChain(1)->GetEntries(); 
  TChain * LastChain;

  std::cout<<std::endl<<"Total Events      \t"<<TotalEvents<<std::endl;
  std::cout << std::endl<<"==== Chain Contents ==== "<<std::endl;
  std::cout << "Chain Name \tEvents \t\tEfficiency"<<std::endl;
  for(int i=1; i<=GetNumberOfChains(); i++)
    {
      int iEntries = GetChain(i)->GetEntries();
      std::cout << GetName(i) << "\t\t"<<iEntries<<"\t\t"<<float(iEntries)/TotalEvents<<std::endl;
    }
  

  int NoOfCuts = CC->GetNoOfCuts();

  std::cout << std::endl<< "==== Cuts in sequence (efficiency of cut applied at each stage) ====" <<std::endl;
  std::cout << "Cut No \t Cut Name \t\t Frac of All \t Frac of L1 \t Frac of HLT"<<std::endl;
  
  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetSequenceCut(CutName); 
      printf( "%i \t %s \t\t %.4f \t %.4f \t %.4f \n", i,CutName.c_str(), 
	      double(GetChain("HLT")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	      double(GetChain("HLT")->GetEntries(Cut))/GetChain("L1")->GetEntries(), 
	      double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries() );
    }

  std::cout << std::endl << "==== Cuts standalone efficiency ==== " <<std::endl;
  std::cout << "Cut Name \t\t  Applied on All \t Applied at L1 \t Applied at HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetCut(CutName);
      printf("%s \t\t %.4f \t %.4f \t %.4f \n", CutName.c_str(),
	     double(GetChain("All")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	     double(GetChain("L1")->GetEntries(Cut))/GetChain("L1")->GetEntries(),
	     double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
    }


  
  std::cout << std::endl << "==== Cuts n-1 efficiency ====" << std::endl;
  std::cout << "Cut Name \t\t N-1 Efficiency after HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetNMinus1Cut(CutName);
      printf("%s \t\t %.4f \n", CutName.c_str(),
	     double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
    }

  std::cout<<std::endl<<std::endl;
  
  std::cout<<"==== THE BOTTOM LINE =====" <<std::endl<<std::endl;
  
  std::cout<<"Signal efficiency after triggers + cumulative cut: " <<std::endl;
  std::cout<<"of stopped \t  of triggered (L1) \t of triggered (HLT)"<<std::endl;
 
  TCut Cut = CC->GetFullCut();
 
  printf("%.4f  \t %.4f \t\t %.4f \n",
	 100.*double(GetChain("HLT")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	 100.*double(GetChain("HLT")->GetEntries(Cut))/GetChain("L1")->GetEntries(),
	 100.*double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
  std::cout<<std::endl<<std::endl;
 




}





void CraftRunOld::PrintRates(CutCollection * CC)
{
  int TotalEvents = GetChain(1)->GetEntries(); 
  TChain * LastChain;

  int RunLength=GetRunLength();

  std::cout<<std::endl<<"Total Rates      \t"<<TotalEvents<<std::endl;
  std::cout << std::endl<<"==== Chain Contents ==== "<<std::endl<<std::endl;
  std::cout << "Chain Name \t\tRate"<<std::endl;
  for(int i=1; i<=GetNumberOfChains(); i++)
    {
      double Rate = double(GetChain(i)->GetEntries())/RunLength;
      std::cout << GetName(i) << "\t\t"<<Rate<<std::endl;
    }
  

  int NoOfCuts = CC->GetNoOfCuts();

  std::cout << std::endl<< "==== Cuts in sequence ====" <<std::endl<<std::endl;
  std::cout << "Cut No \t Cut Name \t\t Rate "<<std::endl;
  
  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetSequenceCut(CutName); 
      printf( "%i \t %s \t\t %.4f\n", i,CutName.c_str(), 
		double(GetChain("HLT")->GetEntries(Cut))/RunLength);
    }

  std::cout << std::endl << "==== Cuts standalone efficiency ==== " <<std::endl<<std::endl;
  std::cout << "Cut Name \t\t Applied on All\t Applied at L1 \t Applied at HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetCut(CutName);
      printf("%s \t\t %.4f \t %.4f \t %.4f \n", CutName.c_str(),
	     double(GetChain("All")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	     double(GetChain("L1")->GetEntries(Cut))/GetChain("L1")->GetEntries(),
	     double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
    }


  
  std::cout << std::endl << "==== Cuts n-1 efficiency ====" << std::endl<<std::endl;
  std::cout << "Cut Name \t\t N-1 Efficiency after HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut NMinus1Cut = CC->GetNMinus1Cut(CutName);
      TCut FullCut = CC->GetFullCut();
      printf("%s \t\t %.4f \n", CutName.c_str(),
	     double(GetChain("HLT")->GetEntries(FullCut))/GetChain("HLT")->GetEntries(NMinus1Cut));
    }

  std::cout<<std::endl<<std::endl;
  
  std::cout<<"==== THE BOTTOM LINE =====" <<std::endl<<std::endl;
  
  std::cout<<"Background rate after triggers + cumulative cut: " <<std::endl<<std::endl;
  TCut Cut = CC->GetFullCut();
 
  printf("%.4f \n",
	 double(GetChain("HLT")->GetEntries(Cut))/RunLength);
  std::cout<<std::endl<<std::endl;

}

