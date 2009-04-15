#include "GlobalRun.C"

class CraftTiming : public GlobalRun
{

public:
  

     CraftTiming(string, int);
     PrintEfficiencies(CutCollection *);
     PrintEfficiencies();
   
  
};





CraftTiming::CraftTiming(string Directory, int NoOfFiles)
{
  std::vector<string> Names;
  std::vector<string> Modules;

  Names.push_back("BOF");              Modules.push_back("BOF");
  Names.push_back("Timing");           Modules.push_back("an_Timing/EventTree");



  AddMultiple(Names,Modules,Directory.c_str(),"Filter_Data_Histos",NoOfFiles);


}


void CraftTiming::PrintEfficiencies()
{
  CraftCutsTiming * CC = new CraftCutsTiming();
  PrintEfficiencies(CC);
}


void CraftTiming::PrintEfficiencies(CutCollection * CC)
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
  std::cout << "Cut No \t Cut Name \t\t Efficiency"<<std::endl;
  
  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetSequenceCut(CutName); 
      printf( "%i \t %s \t\t %.4f \n", i,CutName.c_str(), 
	      double(GetChain("Timing")->GetEntries(Cut))/GetChain("Timing")->GetEntries());

    }

  std::cout << std::endl << "==== Cuts standalone efficiency ==== " <<std::endl;
  std::cout << "Cut Name \t\t  Applied on All"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetCut(CutName);
      printf("%s \t\t %.4f \n", CutName.c_str(),
	     double(GetChain("Timing")->GetEntries(Cut))/GetChain("Timing")->GetEntries());

    }


  
  std::cout << std::endl << "==== Cuts n-1 efficiency ====" << std::endl;
  std::cout << "Cut Name \t\t N-1 Efficiency after Topological Cuts"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC->GetCutName(i);
      TCut Cut = CC->GetNMinus1Cut(CutName);
      printf("%s \t\t %.4f \n", CutName.c_str(),
	     double(GetChain("Timing")->GetEntries(CC->GetFullCut()))/GetChain("Timing")->GetEntries(Cut));
    }

  std::cout<<std::endl<<std::endl;
  
  std::cout<<"==== THE BOTTOM LINE =====" <<std::endl<<std::endl;
  
  std::cout<<"Signal efficiency after triggers + cumulative cut: " <<std::endl;
   
  TCut Cut = CC->GetFullCut();
 
  printf("%.4f  \n",
	 100.*double(GetChain("Timing")->GetEntries(Cut))/GetChain("Timing")->GetEntries());

  std::cout<<std::endl<<std::endl;
 




}


