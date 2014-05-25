#include <sstream>

#include "TGraph.h"
#include "TGaxis.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include "ExtraLimitPlots.h"

void excludedRegionStop() {

  double stopMass = 173.0; // used for limit plots

  double data[32]  = { 70.,     470,    450,     30,   21,  60,   42,
		       100.,	530.,   480.,    38,   23,  70,   46,
		       150.,	550,    500.,    45,   25,  90,   50,
		       200.,	550,    510.,    36,   25,  72,   50};
	
  double e[4]           = { data[0], data[7], data[14], data[21] };
  double obs[4]         = { data[1], data[8], data[15], data[22]  };
  double exp[4]         = { data[2], data[9], data[16], data[23]  };
  double exp_1sig_hi[4] = { data[3], data[10], data[17], data[24]  };
  double exp_1sig_lo[4] = { data[4], data[11], data[18], data[25]  };
  double exp_2sig_hi[4] = { data[5], data[12], data[19], data[26]  };
  double exp_2sig_lo[4] = { data[6], data[13], data[20], data[27]  };
  
  double e_g[4]       = {175., 200., 300., 360. };
  
  cout << "Energy thresholds : " << e[0] << ", " << e[1] << ", " << e[2] << ", " << e[3] << std::endl;
  cout << "Obs limit         : " << obs[0] << ", " << obs[1] << ", " << obs[2] << ", " << obs[3] << std::endl;
  cout << "Exp limit         : " << exp[0] << ", " << exp[1] << ", " << exp[2] << ", " << exp[3] << std::endl;
  
  // plot as fn of E_cut
  TGraphAsymmErrors g_exp_1sig(4, &e[0], &exp[0], 0, 0, &exp_1sig_lo[0], &exp_1sig_hi[0]);
  TGraphAsymmErrors g_exp_2sig(4, &e[0], &exp[0], 0, 0, &exp_2sig_lo[0], &exp_2sig_hi[0]);
  TGraph g_exp(4, &e[0], &exp[0]); 
  TGraph g_obs(4, &e[0], &obs[0]); 
  // exclusion in m_stop, m_neutralino plane
	
  double m_chi0[100];
  double m_chi0sq[100];
  for (int i=0; i<100; i++) {
    m_chi0[i] = i*10;
    m_chi0sq[i] = (i*10)*(i*10);
  }
  
  
  // observed exclusion
  double obsExcl70[100];
  double obsExcl100[100];
  double obsExcl150[100];
  double obsExcl200[100];
  double obsExclFull[100];
  int npoints70=0;
  int npoints100=0;
  int npoints150=0;
  int npoints200=0;
  int npointsFull=0;

  int start70 = 0;
  int start100 = 0;
  int start150 = 0;
  int start200 = 0;
  int startFull = 0;

  for (int i=0; i<100; ++i) {
    double tmp = e_g[0] + sqrt(e_g[0]*e_g[0] + m_chi0sq[i]-stopMass*stopMass);
    if (isnan(tmp)) {
      start70 = i + 1;
      continue;
    }
    obsExcl70[i] = tmp;
   if (obsExcl70[i]>obs[0]) break;	
    npoints70++;
  }
  	
  for (int i=0; i<100; ++i) {
    double tmp = e_g[1] + sqrt(e_g[1]*e_g[1] + m_chi0sq[i]-stopMass*stopMass);
    if (isnan(tmp)) {
      start100 = i + 1;
      continue;
    }
    obsExcl100[i] = tmp;
    if (obsExcl100[i]>obs[1]) break;	
    npoints100++;
  }	
  
  // For small values of m_chi0, on-shell top mass is fine. 
  // But as m_chi0 increases, we need to decrease the top mass (take it off-shell)
  // Starting off-shell means that the calculated stop mass is larger than the limit
  for (int i=0; i<100; ++i) {
    double tmp = e_g[2] + sqrt(e_g[2]*e_g[2] + m_chi0sq[i]-stopMass*stopMass);
    if (isnan(tmp)) {
      start150 = i + 1;
      continue;
    }
    obsExcl150[i] = tmp;
    if (obsExcl150[i]>obs[2]) break;
    npoints150++;
  }
  
  for (int i=0; i<100; ++i) {
    double tmp = e_g[3] + sqrt(e_g[3]*e_g[3] + m_chi0sq[i]-stopMass*stopMass);
    if (isnan(tmp)) {
      start200 = i + 1;
      continue;
    }
    obsExcl200[i] = tmp;
    if (obsExcl200[i]>obs[2]) break;	
    npoints200++;	
  }

  for (int i=0; i<100; ++i) {
    double tmp = e_g[0] + sqrt(e_g[0]*e_g[0] + m_chi0sq[i]-stopMass*stopMass);
    if (isnan(tmp)) {
      startFull = i + 1;
      continue;
    }
    obsExclFull[i] = tmp;
    if (obsExclFull[i]>obs[1]) break;	
    npointsFull++;	
  }

	
	
  TGraph g_obsExcl70(npoints70+1, &m_chi0[start70], &obsExcl70[start70]);
  g_obsExcl70.SetPoint(npoints70, 0., obs[0]);
  TGraph g_obsExcl100(npoints100+1, &m_chi0[start100], &obsExcl100[start100]);
  g_obsExcl100.SetPoint(npoints100, 0., obs[1]);
  TGraph g_obsExcl150(npoints150+1, &m_chi0[start150], &obsExcl150[start150]);
  g_obsExcl150.SetPoint(npoints150, 0., obs[2]);
  TGraph g_obsExcl200(npoints200+1, &m_chi0[start200], &obsExcl200[start200]);
  g_obsExcl200.SetPoint(npoints200, 0., obs[3]);
  TGraph g_obsExclFull(npointsFull+1, &m_chi0[startFull], &obsExclFull[startFull]);
  g_obsExclFull.SetPoint(npointsFull, 0., obs[1]);


  TCanvas canvas3("excludedRegionStop", "");


  //-------------------------
  // MAKE ALL THE TEXT BLURBS
  //-------------------------
  TH1F h3("h3", "", 1, 0., 500.);
  h3.SetStats (0);
  h3.SetMinimum (0);
  h3.SetMaximum (600);
  h3.GetXaxis()->SetTitle("m_{#tilde{#chi}^{0}} [GeV]");
  h3.GetYaxis()->SetTitle("m_{#tilde{t}}   [GeV]  ");
  h3.Draw();

  TGraph disallowed(4);
  disallowed.SetPoint(0, 0., 0.);
  disallowed.SetPoint(1, 30000., 30000.);
  disallowed.SetPoint(2, 30000., 0.);
  //disallowed.SetPoint(3, 0., 0.);
  disallowed.SetFillColor(kGray);
  disallowed.SetFillStyle(3001);
  disallowed.Draw("FL");

  TText dislabel(0.65, 0.45, "Kinematically forbidden");
  dislabel.SetNDC(true);
  dislabel.SetTextFont(42);
  dislabel.SetTextSize(0.033);
  dislabel.SetTextAngle(30.2); //638 by 372
  dislabel.Draw();

  //	TPaveText blurb3(0.48, 0.15, 0.6, 0.37, "NDC");
  TPaveText blurb3(0.52, 0.15, 0.72, 0.37, "NDC");
  blurb3.AddText("CMS 2012");
  blurb3.AddText("#int L dt = 18.6 fb^{-1}");//,  #int L_{eff} dt = 935 pb^{-1}");
  //blurb3.AddText("L^{max}_{inst} = 3.5 #times 10^{33} cm^{-2}s^{-1}");
  blurb3.AddText("#sqrt{s} = 8 TeV");
  //blurb3.AddText("95% CL Exclusion contours");
  blurb3.SetTextFont(42);
  blurb3.SetBorderSize(0);
  blurb3.SetFillColor(kGray);
  blurb3.SetFillStyle(4001);
  blurb3.SetShadowColor(0);
  blurb3.SetTextAlign(12);
  blurb3.SetTextSize(0.033);
  blurb3.Draw();	
	
  TLegend leg3(0.72, 0.15, 0.92, 0.37,"95% CL Excluded","NDC");
  leg3.SetTextSize(0.033);
  leg3.SetBorderSize(0);
  leg3.SetTextFont(42);
  leg3.SetFillColor(kGray);
  leg3.SetFillStyle(4001);
  leg3.AddEntry(&g_obsExcl70, "E_{thresh} > 70 GeV", "lf");
  leg3.AddEntry(&g_obsExcl100, "E_{thresh} > 100 GeV", "lf");
  //leg3.AddEntry(&g_obsExcl150, "E_{thresh} > 150 GeV", "lf");
  //leg3.AddEntry(&g_obsExcl200, "E_{thresh} > 200 GeV", "lf");
  leg3.Draw();

  //----------------------
  //FORMAT AND DRAW GRAPHS
  //----------------------
  g_obsExclFull.SetLineWidth(302);
  g_obsExclFull.SetFillColor(kYellow);
  g_obsExclFull.SetLineColor(kYellow);
  //g_obsExclFull.Draw("f");

  TGraph* g_obs70y = (TGraph*)g_obsExcl70.Clone("70y");
  g_obs70y->SetFillColor(kYellow);
  g_obs70y->Draw("f");
  TGraph* g_obs100y = (TGraph*)g_obsExcl100.Clone("100y");
  g_obs100y->SetFillColor(kYellow);
  g_obs100y->Draw("f");
  
  g_obsExcl70.SetLineWidth(302);
  g_obsExcl70.SetFillStyle(3004);
  g_obsExcl70.SetFillColor(kGreen+2);
  g_obsExcl70.SetLineColor(kGreen+2);
  g_obsExcl70.Draw();
	
  g_obsExcl100.SetLineWidth(302);
  g_obsExcl100.SetFillStyle(3004);
  g_obsExcl100.SetFillColor(kBlue);
  g_obsExcl100.SetLineColor(kBlue);
  g_obsExcl100.Draw();
	
  g_obsExcl150.SetLineWidth(302);
  g_obsExcl150.SetFillStyle(3004);
  g_obsExcl150.SetFillColor(kBlack);
  g_obsExcl150.SetLineColor(kBlack);
  //g_obsExcl150.Draw();
	
  g_obsExcl200.SetLineWidth(302);
  g_obsExcl200.SetFillStyle(3005);
  g_obsExcl200.SetFillColor(kRed);
  g_obsExcl200.SetLineColor(kRed);
  //g_obsExcl200.Draw();
	
  TLatex t1(0.50, 0.44, "E_{thresh} > 70 GeV");
  t1.SetNDC(true);
  t1.SetTextFont(42);
  t1.SetTextSize(0.03);
  t1.SetTextAngle(25);
  t1.SetTextColor(kGreen+2);
  //t1.Draw();
	
  TLatex t2(0.36, 0.45, "E_{thresh} > 100 GeV");
  t2.SetNDC(true);
  t2.SetTextFont(42);
  t2.SetTextSize(0.03);
  t2.SetTextAngle(22);
  t2.SetTextColor(kBlue);
  //t2.Draw();
	
	
  TLatex t3(0.29, 0.55, "E_{thresh} > 150 GeV");
  t3.SetNDC(true);
  t3.SetTextFont(42);
  t3.SetTextSize(0.03);
  t3.SetTextAngle(14);
  t3.SetTextColor(kBlack);
  //t3.Draw();

  TLatex t4(0.2, 0.69, "E_{thresh} > 200 GeV");
  t4.SetNDC(true);
  t4.SetTextFont(42);
  t4.SetTextSize(0.03);
  t4.SetTextAngle(5);
  t4.SetTextColor(kRed);
  //t4.Draw();
			
  h3.Draw("sameaxis");
	
  canvas3.Print("excludedRegionStop.pdf");
	
}
