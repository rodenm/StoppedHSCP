#include "ChainCollection.C"


class SignalOneFile : public ChainCollection
{
public:
  SignalOneFile();
  ~SignalOneFile();
  void PrintEfficienciesAfter(CutCollection *, CutCollection*);
  void PrintEfficienciesAfterTopological();

  void PrintEfficiencies();
  
};

SignalOneFile::SignalOneFile(string File)
{
    std::vector<string> Names;
    std::vector<string> Modules;

    Names.push_back("BOF");              Modules.push_back("BOF");
    Names.push_back("All");              Modules.push_back("an_All/EventTree");
    Names.push_back("L1");               Modules.push_back("an_L1/EventTree");
    Names.push_back("HLT");              Modules.push_back("an_HLT/EventTree");
    AddOneFile(Names,Modules,File.c_str());
}

void SignalOneFile::PrintEfficiencies(CutCollection * CC)
{
  int TotalEvents = GetChain(1)->GetEntries(); 
  TChain * LastChain;

  std::cout<<std::endl<<"Total Events      \t"<<TotalEvents<<std::endl;
  std::cout << std::endl<<"==== Chain Contents ==== "<<std::endl<<std::endl;
  std::cout << "Chain Name \tEvents \t\tEfficiency"<<std::endl;
  for(int i=1; i<=GetNumberOfChains(); i++)
    {
      int iEntries = GetChain(i)->GetEntries();
      std::cout << GetName(i) << "\t\t"<<iEntries<<"\t\t"<<float(iEntries)/TotalEvents<<std::endl;
    }
  
  int NoOfCuts = CC->GetNoOfCuts();

  std::cout << std::endl<< "==== Cuts in sequence ====" <<std::endl<<std::endl;
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
  
  std::cout<<"Signal efficiency after triggers + cumulative cut: " <<std::endl<<std::endl<<"**********"<<std::endl;
  std::cout<<"of stopped \t of triggered (L1) \t of triggered (HLT)"<<std::endl;
 
  TCut Cut = CC->GetFullCut();
 
  printf("%.4f  \t %.4f \t\t %.4f \n********** \n",
	 double(GetChain("HLT")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	double(GetChain("HLT")->GetEntries(Cut))/GetChain("L1")->GetEntries(),
	double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
  std::cout<<std::endl<<std::endl;


}





void SignalOneFile::PrintEfficienciesAfter(CutCollection * CC1, CutCollection * CC2)
{
  int TotalEvents = GetChain(1)->GetEntries(); 
  TChain * LastChain;

  std::cout<<std::endl<<"Total Events      \t"<<TotalEvents<<std::endl;
  std::cout << std::endl<<"==== Chain Contents ==== "<<std::endl<<std::endl;
  std::cout << "Chain Name \tEvents \t\tEfficiency"<<std::endl;
  for(int i=1; i<=GetNumberOfChains(); i++)
    {
      int iEntries = GetChain(i)->GetEntries();
      std::cout << GetName(i) << "\t\t"<<iEntries<<"\t\t"<<float(iEntries)/TotalEvents<<std::endl;
    }
  

  
  int NoOfCuts = CC2->GetNoOfCuts();

  std::cout << std::endl<< "==== Cuts in sequence ====" <<std::endl<<std::endl;
  std::cout << "Cut No \t Cut Name \t\t Frac of All \t Frac of L1 \t Frac of HLT"<<std::endl;
  
  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC2->GetCutName(i);
      TCut Cut = TCut(CC2->GetSequenceCut(CutName)); 
      Cut += TCut(CC1->GetFullCut());
      
      printf( "%i \t %s \t\t %.4f \t %.4f \t %.4f \n", i,CutName.c_str(), 
		double(GetChain("HLT")->GetEntries(Cut))/GetChain("All")->GetEntries(CC1->GetFullCut()),
		double(GetChain("HLT")->GetEntries(Cut))/GetChain("L1")->GetEntries(CC1->GetFullCut()), 
		double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries(CC1->GetFullCut()) );
    }

  std::cout << std::endl << "==== Cuts standalone efficiency ==== " <<std::endl<<std::endl;
  std::cout << "Cut Name \t\t Applied on All\t Applied at L1 \t Applied at HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC2->GetCutName(i);
      TCut Cut = CC1->GetFullCut();
      Cut += CC2->GetCut(CutName);
      printf("%s \t\t %.4f \t %.4f \t %.4f \n", CutName.c_str(),
	     double(GetChain("All")->GetEntries(Cut))/GetChain("All")->GetEntries(CC1->GetFullCut()),
	     double(GetChain("L1")->GetEntries(Cut))/GetChain("L1")->GetEntries(CC1->GetFullCut()),
	     double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries(CC1->GetFullCut()));
    }


  
  std::cout << std::endl << "==== Cuts n-1 efficiency ====" << std::endl<<std::endl;
  std::cout << "Cut Name \t\t N-1 Efficiency after HLT"<<std::endl;


  for(int i=0; i!=NoOfCuts; i++)
    {
      string CutName = CC2->GetCutName(i);
      TCut NMinus1Cut = CC1->GetFullCut();
      NMinus1Cut += CC2->GetNMinus1Cut(CutName);
      TCut FullCut = CC1->GetFullCut();
      FullCut += CC2->GetFullCut();
      printf("%s \t\t %.4f \n", CutName.c_str(),
	     double(GetChain("HLT")->GetEntries(FullCut))/GetChain("HLT")->GetEntries(NMinus1Cut));
    }

  std::cout<<std::endl<<std::endl;
  
  std::cout<<"==== THE BOTTOM LINE =====" <<std::endl<<std::endl;
  
  std::cout<<"Signal efficiency after triggers + cumulative cut: " <<std::endl<<std::endl<<"**********"<<std::endl;
  std::cout<<"of stopped \t of triggered (L1) \t of triggered (HLT)"<<std::endl;
 
  TCut Cut = CC1->GetFullCut();
  Cut += CC2->GetFullCut();
 
  printf("%.4f  \t %.4f \t\t %.4f \n********** \n",
	 double(GetChain("HLT")->GetEntries(Cut))/GetChain("All")->GetEntries(),
	double(GetChain("HLT")->GetEntries(Cut))/GetChain("L1")->GetEntries(),
	double(GetChain("HLT")->GetEntries(Cut))/GetChain("HLT")->GetEntries());
  std::cout<<std::endl<<std::endl;
  

}


void SignalOneFile::PrintEfficienciesAfterTopological()
{
  CraftCutsNoTiming * CC1 = new CraftCutsNoTiming();
  CraftCutsTiming * CC2 = new CraftCutsTiming();
  PrintEfficienciesAfter(CC1, CC2);
}

