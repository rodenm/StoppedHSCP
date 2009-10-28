#include <string>
#include <vector>
#include <map>
#include <TCut>


class CutCollection
{
public:

  void                        AddCut(string, TCut); //done

  void                        AddCuts(std::vector<string>, std::vector<TCut>); // done
  
  void                        RemoveCut(string); // done

  TCut                        GetFullCut();      //done

  TCut                        GetNMinus1Cut(string); //done

  TCut                        GetCut(string);       //done

  TCut                        GetSequenceCut(string); //done

  int                         GetNoOfCuts();        //done

  void                        PrintCutList();       //done

  string                      GetCutName(int i) {return CutNames.at(i);} //done

  int                         GetCutNumber(string str) {return StringMap(str);} //done
  
  CutCollection();

private :
  
  std::map<std::string, int>  StringMap;

  std::vector<TCut>           CutVector;

  std::vector<string>         CutNames;
  
};



CutCollection::CutCollection()
{
}


int CutCollection::GetNoOfCuts()
{
  return CutVector.size();
}


TCut CutCollection::GetSequenceCut(string TheName)
{
  int CutID = StringMap[TheName];
  TCut CumulativeCut;
  for(int i=0; i<=CutID; i++)
    CumulativeCut+=CutVector.at(i);
  return CumulativeCut;
}

TCut CutCollection::GetCut(string TheName)
{
  return CutVector.at(StringMap[TheName]);
}


void CutCollection::AddCut(string TheName, TCut TheCut)
{
  CutVector.push_back(TheCut);
  CutNames.push_back(TheName);
  StringMap[TheName]=CutVector.size()-1;
}


void CutCollection::AddCuts(std::vector<string> TheNames, std::vector<TCut> TheCuts)
{
  if(TheNames.size()!=TheCuts.size())
    std::cerr << " Error - cut and name vectors of different sizes"<<std::endl;
  else
    for(int i=0; i!=TheNames.size(); i++)
      {
	AddCut(TheNames.at(i), TheCuts.at(i));
      }
}




void CutCollection::RemoveCut(string TheName)
{
  vector<TCut> NewCutVector;
  vector<TCut> NewCutNames;
  std::map<string, int> NewStringMap;
  int CutID = StringMap[TheName];
  for(int i=0; i!=TheCuts.size(); i++)
    {
      if(i!=CutID)
	{
	  NewCutVector.push_back(CutVector.at(i));
	  NewNamesVector.push_back(CutNames.at(i));
	  NewStringMap[CutNames.at(i)]=CutNames.size()-1;
	}
    }
  CutVector = NewCutVector;
  CutNames = NewCutNames;
  StringMap = NewStringMap;
}


void CutCollection::PrintCutList()
{
  std::cout <<"ID\tName\tCut"<<std::endl;
  for(int i=0; i!=CutVector.size(); i++)
    std::cout<<i"\t"<<CutNames.at(i).c_str()<<"\t" <<string(CutVector.at(i))<<std::endl;
}



TCut CutCollection::GetFullCut()
{
  if(CutVector.size()==0)
    std::cerr<<"Error, cut collection is empty"<<std::endl;
  else
    {
      TCut TempCut = CutVector.at(0);
      for(int i=1; i!=CutVector.size(); i++)
	{
	  TempCut = TempCut && CutVector.at(i);
	}
      return TempCut;
    }	    
}

TCut CutCollection::GetNMinus1Cut(string TheName)
{
  if(CutVector.size()==0||StringMap[TheName]=="")
    std::err << "Error, cut does not exist or vector is empty"<<std::endl;
  else
    {
      TCut TempCut;
      bool OneCutAdded=false;
      int CutToSkip=StringMap[TheName];
      for(int i=0; i!=CutVector.size(); i++)
	if(CutToSkip!=i)
	  if(OneCutAdded==false)
	    {
	      OneCutAdded=true;
	      TempCut=CutVector.at(i);
	    }
	  else
	    TempCut=TempCut && CutVector.at(i);
      return TempCut;
      
    }
}
    
