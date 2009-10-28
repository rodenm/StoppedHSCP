#include <vector>
#include "TObject.h"
#include <map>
#include "TChain.h"
#pragma link C++ class TChain;
#pragma link C++ class vector<TChain*>;


class ChainCollection 
{
  public:
     
     bool             AddChain(string, string, string, string, int);

     bool             AddMultiple(vector<string>, vector<string>,string,string,int);  

     bool             ChainOneFile(vector<string>,vector<string>,string);

     TChain *         GetChain(int);

     TChain *         GetChain(string);

     bool             ReplaceChain(int, string, string, string, int, string);
    
     string           GetName(int);

     string           GetDirectory(int);

     string           GetModule(int);

     int              GetNumberOfFiles(int);

     int              GetID(string);

     int              GetNumberOfChains();

     bool             IsGood();

     ChainCollection();

  

  protected:


     vector<string>   mChainDirectory; 

     vector<TChain*>   mChain;
  
     vector<string>   mChainName;
  
     vector<string>   mModule;
     
     vector<int>      mNumberOfFiles;

     map<string,int>  NameLookup;  

     vector<string>   mFileName;

     int              MakeChain(TChain*, string, string, string, string, int);

     bool             CheckID(int);
  
 
};

bool ChainCollection::IsGood()
{
  bool Result=true;
  int NumberOfChains = GetNumberOfChains();
  if(NumberOfChains==0) Result=false;
  //  for(int i=0; i!=NumberOfChains; i++)
  //  {
  //      if(GetNumberOfFiles(i+1)==0) Result=false;
  //  }
  return Result;

}


bool ChainCollection::CheckID(int ID)
{
  if((ID>0) && (ID <=GetNumberOfChains()))
    {
      return true;
    }
  else
    {
      std::cerr<< " Error, chain index out of range"<<std::endl;
      return false;
    }
}



ChainCollection::ChainCollection()
{
  TChain * NewChain = new TChain;
  mChain.push_back(NewChain);
  mFileName.push_back("BOF");
  mNumberOfFiles.push_back(0);
  mChainDirectory.push_back("BOF");
  mModule.push_back("BOF");
  mChainName.push_back("BOF");

}


ChainCollection::AddOneFile(vector<string> Names, vector<string> Modules, string FileName)
{
  
  ifstream f;
  f.open(FileName.c_str());
  bool FileOK;
  if(!f.fail())
    {
      std::cout<<"File " << FileName.c_str()<< " found... " << std::endl;
      FileOK=true;
    }
  else
    {
      std::cout<<"File not found, not added to tree"<<std::endl;
      FileOK=false;
    }
  if(FileOK)
    {
      for(int i=1; i!=Names.size(); i++)
	{
	  NewChainToAdd = new TChain;
	  NewChainToAdd->SetName(Modules.at(i).c_str());
	  NewChainToAdd->Add(FileName.c_str());
	  
      	  mChain.push_back(NewChainToAdd);
	  mChainDirectory.push_back("N/A - single file");
	  mChainName.push_back(Names.at(i).c_str());
	  mModule.push_back(Modules.at(i).c_str());
	  mFileName.push_back(FileName.c_str());
	  mNumberOfFiles.push_back(1);
	  NameLookup[Names.at(i).c_str()]=mChain.size()-1;
	  std::cout<<"Extracted Chain "<<Names.at(i)<<std::endl;
	}  

    }

}

ChainCollection::AddMultiple(vector<string> Names, vector<string> Modules, string Directory, string FileName, int NoOfFiles)
{
  

  std::vector<string> FileList;

    
  int ActualNoOfFiles=0;
  
  stringstream InputString;
  for(int i=1; i!=NoOfFiles; i++)
    {
      InputString.str("");
      InputString <<Directory.c_str() <<"/"<<FileName.c_str()<<"_"<<i<<".root";
      std::cout<<InputString.str();
      
      string CString(InputString.str());
      ifstream f;
      f.open(CString.c_str());
      if(!f.fail())
	{
	  FileList.push_back(CString);
	  std::cout<<"  ... OK"<<std::endl;
	}
      else
	{
	  std::cout<<"  File not found, not added to tree"<<std::endl;
	}
    }
  
  TChain * NewChainToAdd;
  std::cout<<"No Of Files added: " << FileList.size()<<std::endl;
  if(FileList.size()>0)
    {
      for(int i=1; i!=Names.size(); i++)
	{
	  NewChainToAdd = new TChain;
	  NewChainToAdd->SetName(Modules.at(i).c_str());
	  for(int j=0; j!=FileList.size(); j++)
	    {
	      NewChainToAdd->Add(FileList.at(j).c_str());
	    }
      	  mChain.push_back(NewChainToAdd);
	  mChainDirectory.push_back(Directory.c_str());
	  mChainName.push_back(Names.at(i).c_str());
	  mModule.push_back(Modules.at(i).c_str());
	  mFileName.push_back(FileName.c_str());
	  mNumberOfFiles.push_back(ActualNoOfFiles);
	  NameLookup[Names.at(i).c_str()]=mChain.size()-1;
	  std::cout<<"Filled Chain "<<Names.at(i)<<std::endl;
	}
    }
}


int ChainCollection::MakeChain(TChain * NewChain, string ChainName, string Module, string Directory, string FileName, int NoOfFiles)
{
  

  NewChain->SetName(Module.c_str());
  int ActualNoOfFiles=0;

  stringstream InputString;
  for(int i=1; i<NoOfFiles; i++)
    {
      InputString.str("");
      InputString <<Directory.c_str() <<"/"<<FileName.c_str()<<"_"<<i<<".root";
      std::cout<<InputString.str();
	  
      string CString(InputString.str());
      ifstream f;
      f.open(CString.c_str());
      if(!f.fail())
	{
	  NewChain->Add(CString.c_str());
	  std::cout<<"  ... OK"<<std::endl;
	  ActualNoOfFiles++;
	
	}
      else
	{
	  std::cout<<"  File not found, not added to tree"<<std::endl;
	
	}
    }


  std::cout<<"Added "<< ActualNoOfFiles << " to chain " << ChainName<<std::endl;
  return ActualNoOfFiles;
}



void ChainCollection::ReplaceChain(int ID, string ChainName, string Module, string Directory, string FileName, int NoOfFiles)
{
  if((ID>-1)&&(ID<mChain.size()))
    {
      TChain * NewChain = new TChain;
   
      int ActualNoOfFiles = MakeChain(NewChain,ChainName,Module,Directory,FileName,NoOfFiles);
      
      if(ActualNoOfFiles>0)
	{
	  delete mChain.at(ID);
	  mChain[ID] = NewChain;
	  mChainDirectory[ID] = Directory;
	  mChainName[ID] = ChainName;
	  mModule[ID] = Module;
	  mNumberOfFiles[ID] = ActualNoOfFiles;
	  mChain[ID] = NewChain;
	  NameLookup[ChainName] = ID;
	}
      else
	{
	  delete NewChain;
	  std::cerr << "No files found.  No chain added"<<std::endl;
	}
    }
  else
    {
      std::cerr<<"Chain number "<< ID<<" does not exist.  No change made"<<std::endl;
    }
}





bool ChainCollection::AddChain(string ChainName, string Module, string Directory, string FileName, int NoOfFiles)
{
  TChain * NewChain = new TChain;
  int ActualNoOfFiles = MakeChain(NewChain,ChainName,Module,Directory,FileName,NoOfFiles);
  std::cout<<ActualNoOfFiles<<std::endl;
  if(ActualNoOfFiles>0)
    {
      mChainDirectory.push_back(Directory.c_str());
      mChainName.push_back(ChainName.c_str());
      mModule.push_back(Module.c_str());
      mFileName.push_back(FileName.c_str());
      mNumberOfFiles.push_back(ActualNoOfFiles);
      mChain.push_back(NewChain);
      NameLookup[ChainName]=mChain.size()-1;
    }
  else
    {
      delete NewChain;
      std::cerr << "No files found.  No chain added"<<std::endl;
    }

}


int ChainCollection::NumberOfChains()
{
  return mChain.size();
}





TChain * ChainCollection::GetChain(int ID)
{
  if((0 < ID) && ( ID < mChain.size()))
    {
      return mChain.at(ID);
    }
  else
    {
      std::cerr<<"Chain out of range, returning empty chain"<<std::endl;
      return new TChain;
    }
}






TChain *  ChainCollection::GetChain(string Name)
{
  int ChainID = NameLookup[Name];
  if(ChainID > 0)
    {
      return mChain.at(ChainID);
    }
  else
    {
      std::cerr<<"Chain with name "<<Name<<" does not exist. returning empty chain"<<std::endl;
      return new TChain;
    }
}



string ChainCollection::GetName(int ID)
{
  if((ID>0)&&(ID<mChain.size()))
    return mChainName.at(ID);
  else
    std::cerr<<"invalid ID, no chain found"<<std::endl;
}




string ChainCollection::GetModule(int ID)
{
  if((ID>0)&&(ID<mChain.size()))
    return mModule.at(ID);
  else
    std::cerr<<"invalid ID, no chain found"<<std::endl;
}



string ChainCollection::GetFileName(int ID)
{
  if((ID>0)&&(ID<mChain.size()))
     return mFileName.at(ID);
  else
    std::cerr<<"invalid ID, no chain found"<<std::endl;
}





string ChainCollection::GetDirectory(int ID)
{
  if((ID>0)&&(ID<mChain.size()))
     return mChainDirectory.at(ID);
  else
    std::cerr<<"invalid ID, no chain found"<<std::endl;
}




string ChainCollection::GetNumberOfFiles(int ID)
{
  if((ID>0)&&(ID<mChain.size()))
     return mNumberOfFiles.at(ID);
  else
    std::cerr<<"invalid ID, no chain found"<<std::endl;
}





int ChainCollection::GetNumberOfChains()
{
  return mChain.size()-1;
}




int ChainCollection::GetID(string Name)
{
  return NameLookup[Name];
}



