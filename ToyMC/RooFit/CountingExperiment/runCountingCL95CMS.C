void runCountingCL95CMS (double lifetime, int observed, double bkg, double bkgStat, double bkgSys, double scaleSys)
{
  cout << "=== running  runCountingCL95CMS->" << lifetime 
       << ' ' << bkg << ' ' << bkgStat << ' ' << bkgSys
       << ' ' << scaleSys
       << ' ' << observed << endl;

  gSystem->Load("cl95cms_new_C.so");


  double bkgerrStat = bkgStat/bkg;
  double bkgerrSys = bkg*sqrt(bkgerrStat*bkgerrStat + bkgSys*bkgSys);
  bkgerrStat = bkgStat;

  double cl95NoSys = CL95 (1.,0.,1.,0.,bkg,bkgerrStat,observed, false, 0);     
  std::cout << "CL95(" << 1.<<','<<0.<<','<<1.<<','<<0.<<','<<bkg<<','<<bkgerrStat<<','<<observed<<','<< false<<','<< 0 << ") = " << cl95NoSys << std::endl;
  double cl95Sys = CL95 (1.,0.,1.,scaleSys,bkg,bkgerrSys,observed, false, 0); 
  std::cout << "CL95(" << 1.<<','<<0.<<','<<1.<<','<<scaleSys<<','<<bkg<<','<<bkgerrSys<<','<<observed<<','<< false<<','<< 0 << ") = " << cl95Sys << std::endl;
  // std::vector<double> result = CLA(1.,0.,1.,0.0001,bkg,bkgerrStat, 0);
  std::vector<double> result = CLA(1.,0.,1.,scaleSys,bkg,bkgerrSys, 0);

  char buffer[10000];
  sprintf (buffer, "lifetime: %6.3e  bkg: %5.3f observed: %3i limNoSys %5.3f limit: %5.3f expectedmean: %5.3f rms1sigma:  %5.3f %5.3f rms2sigma: %5.3f %5.3f  expectedmed: %5.3f qtile1sigma: %5.3f %5.3f qtile2sigma: %5.3f %5.3f",
 	   lifetime, bkg, observed, cl95NoSys, cl95Sys, 
	   result[5], result[6], result[7], result[8], result[9], 
	   result[0], result[1], result[2], result[3], result[4]); 
  ofstream outdata ("lifetimePoinrCL95CMS_out.txt", ios_base::app);
    outdata << buffer << endl;
  outdata.close();
  return;
}

