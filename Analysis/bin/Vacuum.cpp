#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>

#include "TROOT.h"
#include "TH1D.h"
#include "TCanvas.h"

int readFile(std::string filename, TH1D* hist, TH1D* hFine, TH1D* hPeak, TH1D* hcount, TH1D* hFineCount) {

  std::vector<double> peakValue(0);

  std::ifstream file(filename.c_str(), std::ifstream::in);

  std::string line;
  if (!file.fail()) {

    // skip header lines
    getline(file, line);
    getline(file, line);
    getline(file, line);
    getline(file, line);

    // read remainder of file
    while (!file.eof()) {

      getline(file, line);

      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of("\t\v\f\r "));

      //      std::cout << strs.at(0) << "," << strs.at(1) << "," << strs.at(2) << "," << strs.at(3) << "," << strs.at(4) << "," << strs.at(5) << std::endl;

      if (strs.size()>6) {
	const time_t t = atol(strs.at(4).c_str());
	tm* tm1  = localtime(&t);

	int day = (tm1->tm_mon-8)*30 + tm1->tm_mday;
	int hour = (day * 24) + tm1->tm_hour;
	double vac = atof(strs.at(6).c_str());

	//	std::cout << day << " " << vac << std::endl;

	hist->Fill(day, vac);
	hcount->Fill(day);

	hFine->Fill(hour, vac);
	hFineCount->Fill(hour);

	if ((int)peakValue.size()<=day) peakValue.resize(day+1);
	if (peakValue.at(day) < vac) peakValue.at(day) = vac;

      }
      
    }

    for (unsigned i=0; i<peakValue.size(); ++i) hPeak->Fill(i, peakValue.at(i));

    return 0;

  }
  else {
    std::cout << "Failed to open file!" << std::endl;
    return 1;
  }

}

int main() {

  TH1::SetDefaultSumw2();

  gROOT->ProcessLine(".X StoppedHSCP/Analysis/macros/finalPlotStyle.C");

  TH1D* hVacuum    = new TH1D("hVacuum", "Vacuum", 60, 0., 60.);
  TH1D* hVacPeak   = new TH1D("hVacPeak", "Peak Vacuum", 60, 0., 60.);
  TH1D* hCount     = new TH1D("hCount", "Entries", 60, 0., 60.);
  TH1D* hVacFine   = new TH1D("hVacFine", "Vacuum", 1440, 0., 1440.);
  TH1D* hCountFine = new TH1D("hCountFine", "Entries", 1440, 0., 1440.);

  readFile("Vacuum_2011_09_07_2011_09_30.txt", hVacuum, hVacFine, hVacPeak, hCount, hCountFine);
  readFile("Vacuum_2011_10_01_2011_10_14.txt", hVacuum, hVacFine, hVacPeak, hCount, hCountFine);
  readFile("Vacuum_2011_10_15_2011_10_30.txt", hVacuum, hVacFine, hVacPeak, hCount, hCountFine);

  hVacuum->Divide(hCount);

  hVacFine->Divide(hCountFine);

  TCanvas c1;
  c1.SetLogy();

  hVacuum->SetMaximum(1.E-5);
  hVacuum->SetMinimum(1.E-11);
  hVacuum->GetXaxis()->SetTitle("Days");
  hVacuum->GetYaxis()->SetTitle("Ave vacuum");
  hVacuum->SetLineColor(2);
  hVacuum->Draw("HIST");
  hVacuum->SetStats(false);
  c1.Print("Vacuum.pdf");

  hVacFine->SetMaximum(1.E-5);
  hVacFine->SetMinimum(1.E-11);
  hVacFine->GetXaxis()->SetTitle("Hours");
  hVacFine->GetYaxis()->SetTitle("Ave vacuum");
  hVacFine->SetLineColor(2);
  hVacFine->Draw("HIST");
  hVacFine->SetStats(false);
  c1.Print("VacFine.pdf");

  hVacPeak->SetMaximum(1.E-5);
  hVacPeak->SetMinimum(1.E-11);
  hVacPeak->GetXaxis()->SetTitle("Days");
  hVacPeak->GetYaxis()->SetTitle("Ave vacuum");
  hVacPeak->SetLineColor(2);
  hVacPeak->Draw("HIST");
  hVacPeak->SetStats(false);
  c1.Print("VacuumPeak.pdf");


  hCount->Draw();
  c1.Print("Count.pdf");

}
