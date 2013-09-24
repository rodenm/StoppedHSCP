{
  //
  // Marissa Rodenburg, March 2012
  // This script is used to produce the plot recoEfficiency_escan_requireHBEB.pdf
  //

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  //gStyle->SetOptFit();

  TCanvas canvas;

  Int_t nG300points = 5;
  Int_t nG600points = 10;
  Int_t nGBothpoints = 15;

  Double_t bothxG[nGBothpoints] = {49.7, 50.0, 74.7, 75.1, 91.7, 99.9, 100.1, 125.2, 125.2, 
				   133.3, 150.2, 200.2, 225.0, 250.0, 291.7};
  Double_t countBoth[nGBothpoints] = {0.0, 0.0, 0.0, 0.0, 2.0, 2.0, 1.0, 2.0, 3.0, 12.0, 27.0, 
				      701.0, 1123.0, 1205.0, 1411.0};
  Double_t totalBoth[nGBothpoints] = {3578.0, 3648.0, 3640.0, 3581.0, 3577.0, 3641.0, 3655.0, 
				      3652.0, 3634.0, 3564.0, 3640.0, 3642.0, 3637.0, 3429.0, 
				      3643.0};
  Double_t bothyG[nGBothpoints];
  Double_t bothyGplus1[nGBothpoints];
  Double_t bothyGminus1[nGBothpoints];
  Double_t bothErrG[nGBothpoints];
  for (int ib = 0; ib < nGBothpoints; ib++) {
    bothyG[ib] = countBoth[ib]/totalBoth[ib];
    bothErrG[ib] = bothyG[ib]*TMath::Sqrt(1./countBoth[ib]+1./totalBoth[ib]);

    bothyGplus1[ib] = bothyG[ib] ? bothyG[ib] + bothErrG[ib]: 0;
    bothyGminus1[ib] = bothyG[ib] ? bothyG[ib] - bothErrG[ib]: 0;
  }

  Double_t xaxisG300[nG300points] = {50.,  75.,  100., 125., 133.};
  Double_t countG300[nG300points] = {0.,   0.,   1.,   2.,   12.};
  Double_t totalG300[nG300points] = {3648.,3581.,3655.,3652.,3564.};
  Double_t yaxisG300[nG300points];
  Double_t errorG300[nG300points];
  for (int ig = 0; ig < nG300points; ig++) {
    yaxisG300[ig] = countG300[ig]/totalG300[ig];
    errorG300[ig] = yaxisG300[ig]*TMath::Sqrt(1./countG300[ig]+1./totalG300[ig]);
  }

  Double_t xaxisG600[nG600points] = {50.,  75.,  92.,  100., 125., 150., 200., 225., 250., 292.};
  Double_t countG600[nG600points] = {0.,   0.,   2.,   2.,   3.,   27.,  701., 1123.,1205.,1411.};
  Double_t totalG600[nG600points] = {3578.,3640.,3577.,3641.,3634.,3640.,3642.,3637.,3429.,3643.};
  Double_t yaxisG600[nG600points];
  Double_t errorG600[nG600points];
  for (int ig = 0; ig < nG600points; ig++) {
    yaxisG600[ig] = countG600[ig]/totalG600[ig];
    errorG600[ig] = yaxisG600[ig]*TMath::Sqrt(1./countG600[ig]+1./totalG600[ig]);
  }

  TGraphErrors *gluino300 = new TGraphErrors(nG300points, xaxisG300, 
					     yaxisG300, 0, errorG300);
  TGraphErrors *gluino600 = new TGraphErrors(nG600points, xaxisG600, 
					     yaxisG600, NULL, errorG600);
  TGraphErrors *gluino = new TGraphErrors(nGBothpoints, bothxG, 
					  bothyG, NULL, bothErrG);
  TGraphErrors *gluinoPlus = new TGraphErrors(nGBothpoints, bothxG, 
					      bothyGplus1, NULL, NULL);
  TGraphErrors *gluinoMinus = new TGraphErrors(nGBothpoints, bothxG, 
					       bothyGminus1, NULL, NULL);

  gluino->SetTitle("gluino300 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{det}");
  gluino300->SetTitle("gluino300 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{det}");
  gluino600->SetTitle("gluino600 stopping efficiency;E_{gluon}(E_{top}) [GeV];#varepsilon_{det}");

  gluino->SetMarkerSize(0.0);
  gluino->SetMarkerColor(kBlue);

  gluino300->SetLineColor(kRed);
  gluino300->SetMarkerColor(kRed);
  gluino300->SetMarkerStyle(20);
  gluino300->SetMarkerSize(1.15);
  gluino600->SetLineColor(kRed+2);
  gluino600->SetMarkerColor(kRed+2);
  gluino600->SetMarkerStyle(22);
  gluino600->SetMarkerSize(1.15);

  gluino300->SetLineWidth(2);
  gluino600->SetLineWidth(2);

  gluino600->Draw("AP");
  gluino300->Draw("P same");
  gluino->Draw("P same"); 
  gluinoPlus->Draw("P same"); //"p same"
  gluinoMinus->Draw("p same");
  
  TF1* gfit = new TF1("gfit","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  gfit->SetParameters(0.185,0.029,5.7,0.18);
  gfit->SetRange(50,320);
  gfit->SetLineColor(kBlack);

  TF1* gfitp = new TF1("gfitp","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  gfitp->SetParameters(0.18,0.028,5.7,0.18);
  gfitp->SetFillStyle(1001);
  gfitp->SetFillColor(kRed-10);
  gfitp->SetLineColor(kRed-10); //kRed-10
  gfitp->SetLineWidth(7);
  gfitp->SetRange(50,320);
  //gfitp->Draw("FC same");

  TF1* gfitm = new TF1("gfitm","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  gfitm->SetParameters(0.18,0.028,5.7,0.18);
  gfitm->SetFillStyle(1001);
  gfitm->SetFillColor(10);
  gfitm->SetLineColor(kRed-10); //kRed-10
  gfitm->SetLineWidth(7);
  gfitm->SetRange(50,320);
  gfitm->Draw("FC same");

  gluino600->Draw("P same");
  gluino300->Draw("P same");
  
  gluino->Fit(gfit);
  gluinoPlus->Fit(gfitp);
  gluinoMinus->Fit(gfitm);
  
  std::cout << "=================gluino max = "
	    << (gfitm->GetMaximum() +gfitp->GetMaximum() )/2.
	    <<"=================" << std::endl;


  /****** REPEAT FOR STOP ********/
  Int_t nS300points = 4;
  Int_t nS400points = 11;
  Int_t nS500points = 5;
  Int_t nS600points = 4;
  Int_t nSBothpoints = 24;

  Double_t countBothS[nSBothpoints] = {1.0, 0.0, 0.0, 1.0, 3.0, 2.0, 8.0, 20.0, 34.0, 101.0, 195.0, 
  				       273.0, 269.0, 346.0, 396.0, 530.0, 453.0, 486.0, 491.0, 572.0,
  				       595.0, 522.0, 627.0, 575.0};

  Double_t totalBothS[nSBothpoints] = {3406.0, 2327.0, 3881.0, 3484.0, 3882.0, 2687.0, 3696.0, 3700.0, 
				       3230.0, 3699.0, 3636.0, 3097.0, 2443.0, 2893.0, 3131.0, 3346.0, 
				       2568.0, 2586.0, 2343.0, 2634.0, 2670.0, 2445.0, 2462.0, 2509.0};
  Double_t bothxS[nSBothpoints] = {89.2, 98.0, 98.1, 110.8, 117.5, 141.4, 154.2, 172.4, 176.2, 188.5, 
				   199.9, 210.1, 218.1, 218.8, 225.8, 235.2, 240.6, 250.5, 258.1, 270.6, 
				   277.5, 278.1, 298.2, 298.3};
  Double_t bothxErrS[nSBothpoints] = {0.4, 0.9, 1.3, 2.0, 3.8, 5.2, 6.5, 4.7, 3.6, 2.3, 2.3, 2.4, 2.0, 
				      2.6, 2.8, 2.7, 2.5, 1.7, 2.2, 2.0, 1.8, 1.9, 0.3, 1.3};

  Double_t bothyS[nSBothpoints];
  Double_t bothErrS[nSBothpoints];
  Double_t bothySplus1[nSBothpoints];
  Double_t bothySminus1[nSBothpoints];
  for (int ib = 0; ib < nSBothpoints; ib++) {
    bothyS[ib] = countBothS[ib]/totalBothS[ib];
    bothErrS[ib] = bothyS[ib]*TMath::Sqrt(1./countBothS[ib]+1./totalBothS[ib]);

    bothySplus1[ib] = bothyS[ib]>0 ? bothyS[ib] + bothErrS[ib]: 0.;
    bothySminus1[ib] = bothyS[ib]>0 ? bothyS[ib] - bothErrS[ib]: 0.;
    std::cout <<bothySplus1[ib]<<"\t"<< bothyS[ib] <<"\t"<<bothySminus1[ib]<<std::endl;
  }

  //Double_t xaxisS300[nS300points] = {134.0, 149.0};
  Double_t xaxisS300[nS300points] = {89.2, 98.1, 117.5, 176.2};
  Double_t xerrorS300[nS300points] = {0.4, 1.3, 3.8, 3.6};
  Double_t countS300[nS300points] = {1., 0., 3., 34.};
  Double_t totalS300[nS300points] = {3406., 3881., 3882., 3230.};
  Double_t yaxisS300[nS300points];
  Double_t errorS300[nS300points];
  for (int is = 0; is < nS300points; is++) {
    yaxisS300[is] = countS300[is]/totalS300[is];
    errorS300[is] = yaxisS300[is]*TMath::Sqrt(1./countS300[is]+1./totalS300[is]);
  }

  //Double_t xaxisS400[nS400points] = {167.0, 174.0, 188.0, 199.0};
  Double_t xaxisS400[nS400points] = {98.0, 110.8, 141.4, 154.2, 172.4, 188.5, 199.8, 210.1, 218.8, 225.8, 235.2};
  Double_t xerrorS400[nS400points] = {0.9, 2.0, 5.2, 6.5, 4.7, 2.3, 2.3, 2.4, 2.6, 2.8, 2.7};
  Double_t countS400[nS400points] = {0., 1., 2., 8., 20., 101., 195., 273., 346., 396., 530.};
  Double_t totalS400[nS400points] = {2327., 3484., 2687., 3696., 3700., 3699., 3636., 3097., 2893., 3131., 3346.};
  Double_t yaxisS400[nS400points];
  Double_t errorS400[nS400points];
  for (int is = 0; is < nS400points; is++) {
    yaxisS400[is] = countS400[is]/totalS400[is];
    errorS400[is] = yaxisS400[is]*TMath::Sqrt(1./countS400[is]+1./totalS400[is]);
  }

  // STOP 500
  Double_t xaxisS500[nS500points] = {218.1, 240.6, 258.1, 270.6, 278.1};
  Double_t xerrorS500[nS500points] = {2.0, 2.5, 2.2, 2.0, 1.9};
  Double_t countS500[nS500points] = {269., 453., 491., 572., 522.};
  Double_t totalS500[nS500points] = {2443.,2568.,2343.,2634.,2445.};
  Double_t yaxisS500[nS500points];
  Double_t errorS500[nS500points];
  for (int is = 0; is < nS500points; is++) {
    yaxisS500[is] = countS500[is]/totalS500[is];
    errorS500[is] = yaxisS500[is]*TMath::Sqrt(1./countS500[is]+1./totalS500[is]);
  }
  
  // STOP 600
  Double_t xaxisS600[nS600points] = {250.5, 277.5, 298.3, 298.2};
  Double_t xerrorS600[nS600points] = {1.7, 1.8, 1.3, 0.3};
  Double_t countS600[nS600points] = {486., 595., 575., 627.};
  Double_t totalS600[nS600points] = {2586.,2670.,2509.,2462.};
  Double_t yaxisS600[nS600points];
  Double_t errorS600[nS600points];
  for (int is = 0; is < nS600points; is++) {
    yaxisS600[is] = countS600[is]/totalS600[is];
    errorS600[is] = yaxisS600[is]*TMath::Sqrt(1./countS600[is]+1./totalS600[is]);
  }

  TGraphErrors *stop300 = new TGraphErrors(nS300points, xaxisS300, 
					   yaxisS300, xerrorS300, errorS300);
  TGraphErrors *stop400 = new TGraphErrors(nS400points, xaxisS400, 
					   yaxisS400, xerrorS400, errorS400);
  TGraphErrors *stop500 = new TGraphErrors(nS500points, xaxisS500, 
					   yaxisS500, xerrorS500, errorS500);
  TGraphErrors *stop600 = new TGraphErrors(nS600points, xaxisS600, 
					   yaxisS600, xerrorS600, errorS600);
  TGraphErrors *stop = new TGraphErrors(nSBothpoints, bothxS, 
					bothyS, bothxErrS, bothErrS);
  TGraphErrors *stopPlus = new TGraphErrors(nSBothpoints, bothxS, 
					    bothySplus1, NULL, NULL);
  TGraphErrors *stopMinus = new TGraphErrors(nSBothpoints, bothxS, 
					     bothySminus1, NULL, NULL);

  stop300->SetTitle("stop300 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{det}");
  stop400->SetTitle("stop400 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{det}");
  stop500->SetTitle("stop500 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{det}");
  stop600->SetTitle("stop600 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{det}");
  stop->SetTitle("stop300 stopping efficiency;E_{gluon|top} [GeV];#varepsilon_{det}");

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
  stop500->SetLineColor(kBlue-2);
  stop500->SetMarkerColor(kBlue-2);// kBlue-2
  stop500->SetMarkerStyle(21);     // 21
  stop500->SetMarkerSize(1.15);
  stop600->SetLineColor(kBlue+3);
  stop600->SetMarkerColor(kBlue+3);// kBlue+3
  stop600->SetMarkerStyle(23);     // 23
  stop600->SetMarkerSize(1.15);

  stop300->SetLineWidth(2);
  stop400->SetLineWidth(2);
  
  stop->Draw("P same");  
  stopPlus->Draw("p same");
  stopMinus->Draw("p same");
  stop400->Draw("P same");
  stop300->Draw("P same");
  stop500->Draw("P same");
  stop600->Draw("P same");
  
  TF1* sfit = new TF1("sfit","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  sfit->SetParameters(0.09,0.029,5.7,0.19);
  sfit->SetLineColor(kBlack);
  sfit->SetRange(225,320);

  TF1* sfitp = new TF1("sfitp","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  sfitp->SetParameters(0.11,0.023,5.15,0.11);
  sfitp->SetRange(225,320);
  sfitp->SetFillStyle(1001);
  sfitp->SetFillColor(kBlue-10);
  sfitp->SetLineColor(kBlue-10);
  sfitp->SetLineWidth(7);
  sfitp->Draw("FC same");

  TF1* sfitm = new TF1("sfitm","[0]*TMath::Erf([1]*x-[2])+[3]",0,300);
  sfitm->SetParameters(0.09,0.029,5.7,0.19);
  sfitm->SetLineColor(kBlue-10);
  sfitm->SetLineWidth(7);
  sfitm->SetFillColor(10);
  sfitm->SetFillStyle(1001);
  sfitm->SetRange(50,320);
  sfitm->Draw("FC same");

  stop->Fit(sfit);
  stopPlus->Fit(sfitp);
  stopMinus->Fit(sfitm);

  std::cout << "=================stop max = "
	    << sfit->GetMaximum() 
	    <<"=================" << std::endl;


  stop400->Draw("P same");
  stop300->Draw("P same");
  stop500->Draw("P same");
  stop600->Draw("P same");
  
  /****** LEGEND ********/
  leg = new TLegend(0.2,0.55,0.5,0.85,NULL,"brNDC");
  leg->SetTextFont(42);
  leg->SetHeader("CMS Simulation, #sqrt{s} = 8 TeV");
  leg->AddEntry(gluino300,"m_{#tilde{g}} = 300 GeV","ep");
  leg->AddEntry(gluino600,"m_{#tilde{g}} = 600 GeV","ep");
  leg->AddEntry(stop300,"m_{#tilde{t}} = 300 GeV","ep");
  leg->AddEntry(stop400,"m_{#tilde{t}} = 400 GeV","ep");  
  leg->AddEntry(stop500,"m_{#tilde{t}} = 500 GeV","ep");
  leg->AddEntry(stop600,"m_{#tilde{t}} = 600 GeV","ep");

  leg->SetFillColor(kWhite);
  leg->SetBorderSize(0);
  leg->Draw();

  canvas->Print("summer12_8TeV_detectionEff_200GeV.pdf");
}
