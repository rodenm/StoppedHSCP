{
  // Marissa Rodenburg, March 2012
  // This script is used to produce the plot summer12_8TeV_detectionEff.pdf
  //
  // From root:
  // [0] .x StoppedHSCP/Analysis/scripts/energyscan_fit.C
  //

  TCanvas canvas;

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  //gStyle->SetOptFit();

  Int_t nG400points=6;
  Int_t nG700points=10;
  Int_t nG1200points=8;
  Double_t bothxG[nG400points+nG700points+nG1200points] = {50,50,75,75,85,85,95,105,105,145,150,
							   185,195,220,250,260,300,300,350,400,450,
							   500,550,595};
  // selected EB+HB
  Double_t countBoth[nG400points+nG700points+nG1200points] = {21.,
							      16.,
							      685.,
							      716.,
							      1155.,
							      1096.,
							      1410.,
							      1509.,
							      1612.,
							      1685.,
							      1645.,
							      1639.,
							      1611.,
							      1581.,
							      3487.,
							      1505.,
							      3305.,
							      1424.,
							      3117.,
							      3042.,
							      2972.,
							      2756.,
							      2634.,
							      2517.};
  // stopped EB+HB
  Double_t totalBoth[nG400points+nG700points+nG1200points] = {3843.,
							      3932.,
							      3845.,
							      3926.,
							      3925.,
							      3851.,
							      3844.,
							      3843.,
							      3934.,
							      3841.,
							      3923.,
							      3844.,
							      3928.,
							      3843.,
							      8945.,
							      3865.,
							      8823.,
							      3847.,
							      8647.,
							      8950.,
							      8944.,
							      8856.,
							      8683.,
							      8835.};
  Double_t bothyG[nG400points+nG700points+nG1200points];
  Double_t bothyGplus1[nG400points+nG700points+nG1200points];
  Double_t bothyGminus1[nG400points+nG700points+nG1200points];
  Double_t bothErrG[nG400points+nG700points+nG1200points];
  for (int ib = 0; ib < nG400points+nG700points+nG1200points; ib++) {
    bothyG[ib] = countBoth[ib]/totalBoth[ib];
    bothErrG[ib] = bothyG[ib]*TMath::Sqrt(1./countBoth[ib]+1./totalBoth[ib]);
    std::cout<<bothyG[ib]<<"\t"<<countBoth[ib]<<"\t"<<totalBoth[ib]<<std::endl;;

    bothyGplus1[ib] = bothyG[ib] + bothErrG[ib];
    bothyGminus1[ib] = bothyG[ib] - bothErrG[ib];
  }

  Double_t xaxisG400[nG400points] = {50.,75.,85.,105.,150.,195.,};
  Double_t countG400[nG400points] = {16.,716.,1155.,1612.,1645.,1611.,};
  Double_t totalG400[nG400points] = {3932.,3926.,3925.,3934.,3923.,3928.};
  Double_t yaxisG400[nG400points];
  Double_t errorG400[nG400points];
  for (int ig = 0; ig < nG400points; ig++) {
    yaxisG400[ig] = countG400[ig]/totalG400[ig];
    errorG400[ig] = yaxisG400[ig]*TMath::Sqrt(1./countG400[ig]+1./totalG400[ig]);
  }

  Double_t xaxisG700[nG700points] = {50.,75.,85.,95.,105.,145.,185.,220.,260.,300};
  Double_t countG700[nG700points] = {21.,685.,1096.,1410.,1509.,1685.,1639.,1581.,1505.,1424.};
  Double_t totalG700[nG700points] = {3843.,3845.,3851.,3844.,3843.,3841.,3844.,3843.,3865.,3847};
  Double_t yaxisG700[nG700points];
  Double_t errorG700[nG700points];
  for (int ig = 0; ig < nG700points; ig++) {
    yaxisG700[ig] = countG700[ig]/totalG700[ig];
    errorG700[ig] = yaxisG700[ig]*TMath::Sqrt(1./countG700[ig]+1./totalG700[ig]);
  }
  Double_t xaxisG1200[nG1200points] = {250,300,350,400,450,500,550,595};
  Double_t countG1200[nG1200points] = {3487,3305,3117,3042,2972,2756,2634,2517};
  Double_t totalG1200[nG1200points] = {8945,8823,8647,8950,8944,8856,8683,8835};
  Double_t yaxisG1200[nG1200points];
  Double_t errorG1200[nG1200points];
  for (int ig = 0; ig < nG1200points; ig++) {
    yaxisG1200[ig] = countG1200[ig]/totalG1200[ig];
    errorG1200[ig] = yaxisG1200[ig]*TMath::Sqrt(1./countG1200[ig]+1./totalG1200[ig]);
  }


  TGraphErrors *gluino400   = new TGraphErrors(nG400points, xaxisG400, 
					       yaxisG400, 0, errorG400);
  TGraphErrors *gluino700   = new TGraphErrors(nG700points, xaxisG700, 
					       yaxisG700, NULL, errorG700);
  TGraphErrors *gluino1200  = new TGraphErrors(nG1200points, xaxisG1200, 
					       yaxisG1200, NULL, errorG1200);
  TGraphErrors *gluino      = new TGraphErrors(nG400points+nG700points+nG1200points, bothxG, 
					       bothyG,NULL,NULL);
  TGraphErrors *gluinoPlus  = new TGraphErrors(nG400points+nG700points+nG1200points, bothxG, 
					       bothyGplus1, NULL, NULL);
  TGraphErrors *gluinoMinus = new TGraphErrors(nG400points+nG700points+nG1200points, bothxG, 
					       bothyGminus1, NULL, NULL);

  gluino->SetTitle("gluino400 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{detection}");
  gluino400->SetTitle("gluino400 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{detection}");
  gluino700->SetTitle("gluino700 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{detection}");
  gluino1200->SetTitle("gluino1200 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{detection}");

  gluino->SetMarkerSize(0.1);
  gluino->SetMarkerColor(kWhite);

  gluino400->SetLineColor(kRed);
  gluino400->SetMarkerColor(kRed);
  gluino400->SetMarkerStyle(24);
  gluino400->SetMarkerSize(1.15);

  gluino700->SetLineColor(kRed+2);
  gluino700->SetMarkerColor(kRed+2);
  gluino700->SetMarkerStyle(26);
  gluino700->SetMarkerSize(1.15);

  gluino1200->SetLineColor(kRed+3);
  gluino1200->SetMarkerColor(kRed+3);
  gluino1200->SetMarkerStyle(25);
  gluino1200->SetMarkerSize(1.15);

  gluino400->SetLineWidth(2);
  gluino700->SetLineWidth(2);
  gluino1200->SetLineWidth(2);

  gluino->Draw("AP"); //AP 
  gluinoPlus->Draw("P same");
  gluinoMinus->Draw("P same");

  
  TF1* gfit = new TF1("gfit","[0]*TMath::Erf([1]*x-[2])+[3]",0,500);
  gfit.SetParameters(0.25,0.034,2.33,0.25);
  TF1* gfitp = new TF1("gfitp","[0]*TMath::Erf([1]*x-[2])+[3]",0,500);
  gfitp->SetParameters(0.25,0.034,2.33,0.25);
  gfitp->SetFillStyle(1001); //1001
  gfitp->SetFillColor(kRed-10);
  gfitp->SetLineColor(kRed-10);
  gfitp->SetLineWidth(7);
  gfitp->Draw("FC same");
  TF1* gfitm = new TF1("gfitm","[0]*TMath::Erf([1]*x-[2])+[3]",0,500);
  gfitm->SetParameters(0.25,0.034,2.33,0.25);
  gfitm->SetFillStyle(1001);
  gfitm->SetFillColor(10);
  gfitm->SetLineColor(kRed-10);
  gfitm->SetLineWidth(7);
  gfitm->Draw("FC same");
  

  gluino700->Draw("P same");
  gluino400->Draw("P same");
  gluino1200->Draw("P same");
  
  gluino->Fit(gfit);
  gluinoPlus->Fit(gfitp);
  gluinoMinus->Fit(gfitm);
  std::cout << "=================gluino max = "
	    << gfit->GetMaximum() 
	    <<"=================" << std::endl;
  
  
  
  /****** REPEAT FOR STOP ********/
  
  Int_t nS300points=5;
  Int_t nS400points=6;
  Int_t nS600points=4;
  Int_t nS1000points=7;
  Int_t nSallpoints=nS300points+nS400points+nS600points+nS1000points;

  // selected EB+HB
  Double_t countBothS[nSallpoints] = {586,
				      643,
				      721,
				      576,
				      731,
				      800,
				      900,
				      802,
				      827,
				      919,
				      746,
				      814,
				      832,
				      1223,
				      752,
				      728,
				      1166,
				      1147,
				      1130,
				      1049,
				      1099,
				      979,
  };

  // stopped EB+HB
  Double_t totalBothS[nSallpoints] = {3218,
				      2861,
				      3217,
				      2519,
				      2857,
				      3144,
				      3215,
				      2858,
				      2865,
				      3219,
				      2502,
				      2865,
				      2859,
				      4322,
				      2515,
				      2514,
				      4233,
				      4418,
				      4421,
				      4317,
				      4368,
				      4016};
  // visible energy (top energy)
  Double_t bothxS[nSallpoints] = {89,
				  98,
				  98,
				  99,
				  111,
				  118,
				  130,
				  141,
				  189,
				  192,
				  192,
				  210,
				  231,
				  250,
				  251,
				  299,
				  300,
				  351,
				  400,
				  450,
				  500,
				  510};

  Double_t bothyS[nSallpoints];
  Double_t bothErrS[nSallpoints];
  Double_t bothySplus1[nSallpoints];
  Double_t bothySminus1[nSallpoints];
  for (int ib = 0; ib < nSallpoints; ib++) {
    bothyS[ib] = countBothS[ib]/totalBothS[ib];
    bothErrS[ib] = bothyS[ib]*TMath::Sqrt(1./countBothS[ib]+1./totalBothS[ib]);

    bothySplus1[ib] = bothyS[ib] + bothErrS[ib];
    bothySminus1[ib] = bothyS[ib] - bothErrS[ib];
  }

  Double_t xaxisS300[nS300points] = {89.2,98.2,117.6,129.7,191.5};
  Double_t countS300[nS300points] = {586.,721.,800.,900.,919.};
  Double_t totalS300[nS300points] = {3218.,3217.,3144.,3215.,3219.};
  Double_t yaxisS300[nS300points];
  Double_t errorS300[nS300points];
  for (int is = 0; is < nS300points; is++) {
    yaxisS300[is] = countS300[is]/totalS300[is];
    errorS300[is] = yaxisS300[is]*TMath::Sqrt(1./countS300[is]+1./totalS300[is]);
  }

  Double_t xaxisS400[nS400points] = {98.0,110.8,141.4,188.5,210.1,231.3};
  Double_t countS400[nS400points] = {643.,731.,802.,827.,814.,832.};
  Double_t totalS400[nS400points] = {2861.,2857.,2858.,2865.,2865.,2859.};
  Double_t yaxisS400[nS400points];
  Double_t errorS400[nS400points];
  for (int is = 0; is < nS400points; is++) {
    yaxisS400[is] = countS400[is]/totalS400[is];
    errorS400[is] = yaxisS400[is]*TMath::Sqrt(1./countS400[is]+1./totalS400[is]);
  }
  
  
  // STOP 600
  Double_t xaxisS600[nS600points] = {98.7,192.0,250.5,298.8};
  Double_t countS600[nS600points] = {576.,746.,752.,728.};
  Double_t totalS600[nS600points] = {2519.,2502.,2515.,2514.};
  Double_t yaxisS600[nS600points];
  Double_t errorS600[nS600points];
  for (int is = 0; is < nS600points; is++) {
    yaxisS600[is] = countS600[is]/totalS600[is];
    errorS600[is] = yaxisS600[is]*TMath::Sqrt(1./countS600[is]+1./totalS600[is]);
  }
  // STOP 1000
  Double_t xaxisS1000[nS1000points] = {250.,300.,351.,400.,450.,500.,510.,};
  Double_t countS1000[nS1000points] = {1223.,1166.,1147.,1130.,1049.,1099.,979.,};
  Double_t totalS1000[nS1000points] = {4322,4233,4418,4421,4317,4368,4016};
  Double_t yaxisS1000[nS1000points];
  Double_t errorS1000[nS1000points];
  for (int is = 0; is < nS1000points; is++) {
    yaxisS1000[is] = countS1000[is]/totalS1000[is];
    errorS1000[is] = yaxisS1000[is]*TMath::Sqrt(1./countS1000[is]+1./totalS1000[is]);
  }
  
  TGraphErrors *stop300 = new TGraphErrors(nS300points, xaxisS300, 
					   yaxisS300, 0, errorS300);
  TGraphErrors *stop400 = new TGraphErrors(nS400points, xaxisS400, 
					   yaxisS400, 0, errorS400);
  TGraphErrors *stop600 = new TGraphErrors(nS600points, xaxisS600, 
					   yaxisS600, 0, errorS600);
  TGraphErrors *stop1000 = new TGraphErrors(nS1000points, xaxisS1000, 
					   yaxisS1000, errorS1000);
  TGraphErrors *stop = new TGraphErrors(nSallpoints, bothxS, 
					bothyS, 0, bothErrS);
  TGraphErrors *stopPlus = new TGraphErrors(nSallpoints, bothxS, 
					    bothySplus1, NULL, NULL);
  TGraphErrors *stopMinus = new TGraphErrors(nSallpoints, bothxS, 
					     bothySminus1, NULL, NULL);

  stop300->SetTitle("stop300 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{detection}");
  stop400->SetTitle("stop400 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{detection}");
  stop600->SetTitle("stop600 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{detection}");
  stop1000->SetTitle("stop1000 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{detection}");
  stop->SetTitle("stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{detection}");

  stop->SetMarkerSize(0.0);
  stop->SetMarkerColor(kWhite);
  stop->SetLineColor(kBlue);

  stop300->SetLineColor(kBlue-4);  
  stop300->SetMarkerColor(kBlue-4);// kBlue-4
  stop300->SetMarkerStyle(20);     // 20
  stop300->SetMarkerSize(1.15);
  stop400->SetLineColor(kBlue+1);
  stop400->SetMarkerColor(kBlue+1);// kBlue+1
  stop400->SetMarkerStyle(22);     // 22
  stop400->SetMarkerSize(1.15);
  stop600->SetLineColor(kBlue+3);
  stop600->SetMarkerColor(kBlue+3);// kBlue+3
  stop600->SetMarkerStyle(21);     // 23
  stop600->SetMarkerSize(1.15);
  stop1000->SetLineColor(kCyan+3);
  stop1000->SetMarkerColor(kCyan+3);// kBlue+3
  stop1000->SetMarkerStyle(34);     // 24
  stop1000->SetMarkerSize(1.15);

  stop300->SetLineWidth(2);
  stop400->SetLineWidth(2);
  stop600->SetLineWidth(2);
  stop1000->SetLineWidth(2);

  stop->Draw("P same");  
  stopPlus->Draw("p same");
  stopMinus->Draw("p same");
  stop600->Draw("P same");
  stop400->Draw("P same");
  stop300->Draw("P same");
  stop1000->Draw("P same");
  
  //TF1* sfit = new TF1("sfit","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  //sfit->SetParameters(0.323,0.034,2.33,-0.0084);
  TF1* sfit = new TF1("sfit","[0]*TMath::Erf(0.034*x-2.33)+[1]",0,500);
  sfit->SetParameters(0.323,-0.0084);
  sfit->SetLineColor(kBlue-9); // 10
  sfit->SetRange(50,500);

  //TF1* sfitp = new TF1("sfitp","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  //sfitp->SetParameters(0.13,0.02,2.0,0.12);
  TF1* sfitp = new TF1("sfitp","[0]*TMath::Erf(0.034*x-2.33)+[1]",0,500);
  sfitp->SetParameters(0.323,-0.0084);
  sfitp->SetLineColor(kBlue-9); // 10
  sfitp->SetRange(50,500);
  sfitp->SetFillStyle(1001); // 1001
  sfitp->SetFillColor(kBlue-9); // 10
  sfitp->SetLineWidth(7);
  sfitp->Draw("FC same");

  //TF1* sfitm = new TF1("sfitm","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  //sfitm->SetParameters(0.13,0.02,2.0,0.12);
  TF1* sfitm = new TF1("sfitm","[0]*TMath::Erf(0.034*x-2.33)+[1]",0,500);
  sfitm->SetParameters(0.323,-0.0084);
  sfitm->SetLineColor(kBlue-9); // 10
  sfitm->SetLineWidth(7);
  sfitm->SetFillColor(10);
  sfitm->SetFillStyle(1001);
  sfitm->SetRange(50,500);
  sfitm->Draw("FC same");

  //sfit->SetLineColor(kBlue-10);
  sfit->Draw("f same");
  stop600->Draw("P same");
  stop400->Draw("P same");
  stop300->Draw("P same");
  stop1000->Draw("P same");
  stop->Fit(sfit);
  std::cout << "=================stop max = "
	    << sfit->GetMaximum() 
	    <<"=================" << std::endl;
  stopPlus->Fit(sfitp);
  stopMinus->Fit(sfitm);
  

  /****** LEGEND ********/
  
  leg = new TLegend(0.55,0.15,0.9,0.45,NULL,"brNDC");
  leg->SetTextFont(42);
  leg->SetHeader("CMS Simulation,  #sqrt{s} = 8 TeV");
  leg->AddEntry(gluino400,"m_{#tilde{g}} = 400 GeV","ep");
  leg->AddEntry(gluino700,"m_{#tilde{g}} = 700 GeV","ep");
  leg->AddEntry(gluino1200,"m_{#tilde{g}} = 1000 GeV","ep");
  leg->AddEntry(stop300,"m_{#tilde{t}} = 300 GeV","ep");
  leg->AddEntry(stop400,"m_{#tilde{t}} = 400 GeV","ep");
  leg->AddEntry(stop600,"m_{#tilde{t}} = 600 GeV","ep");
  leg->AddEntry(stop1000,"m_{#tilde{t}} = 1000 GeV","ep");
  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->Draw();
  
  canvas->RedrawAxis();

  canvas->Print("summer12_8TeV_detectionEff.pdf");

}
