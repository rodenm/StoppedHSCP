{
  std::vector<string> MassPointList;
  MassPointList.push_back("300_50");
  MassPointList.push_back("300_100");
  MassPointList.push_back("300_200");
  MassPointList.push_back("200_50");
  MassPointList.push_back("200_100");
  MassPointList.push_back("500_100");
  MassPointList.push_back("900_200");
  MassPointList.push_back("1200_300");

  for(int i=0; i!=MassPointList.size();i++)
    {
      stringstream NewString;
      NewString<<"../../SignalOutput/GenSimReco_"<<MassPointList.at(i).c_str()<<".root";
      std::cout<<"===============================================";
      std::cout<<std::endl<<"  MASS POINT " << MassPointList.at(i).c_str()<<std::endl;
      std::cout<<"     File : " << NewString.str().c_str()<<std::endl;
      std::cout<<"==============================================";
      std::cout<<std::endl<<std::endl;
      SignalOneFile * S1F = new SignalOneFile(NewString.str().c_str());
      S1F->PrintEfficiencies();
    }
  
}
