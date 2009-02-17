{
  unsigned int bxs = 3564;
  unsigned int bxs_on = 0, bxs_off = 0;
  unsigned char beam[bxs];

  int i, j, k, l, counter = 0;

  // beam consists of 3564 bunches

  // 2808 of which are ON, 756 off (78.78% producing, 21.21% triggerable)

  for (i = 1; i <= 4; i++) {

    for (j = 1; j <= 3; j++) {

      for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
	for (l = 1; l <= 72; l++) {
	  beam[counter++] = 1;
	  bxs_on++;
	}
	for (l = 1; l <= 8; l++) {
	  beam[counter++] = 0;
	  bxs_off++;
	}
      }

      for (k = 1; k <= 30; k++) {
	beam[counter++] = 0;
	bxs_off++;
      }

    }

    beam[counter++] = 0;
    bxs_off++;
  }

  for (i = 1; i <= 8 + 72; i++) {
    beam[counter++] = 0;
    bxs_off++;
  }

  cout << bxs_on << " on " << bxs_off << " off " << bxs << "/" << counter << " total" << endl;

double lifetime = 604800;
int days = 30;
 double bg_per_day = //130*2; // ben cites his rates as per 12h
   //   216*2; // 0.02 Hz =864, 216 for cosmic cut (0.005 Hz)
   129.6*2; //.003 Hz

 // increase these parameters to increase precision
 // at the cost of running time.  100 or 1000 are good numbers to try
 double scale = 100; 
 double bgscale = 1; 

 bool signal_on = true;
 bool background_on = true;

//double totalsec = days*24*3600;

 double bctime = 25e-9;

 double cycle = bctime*bxs;

//unsigned long nOrbits = 473000000;
//unsigned long nOrbitsOff = 473000000;
double nOrbits = 473000000;
double nOrbitsOff = 473000000;

double lumi = 1.e32;
double xsection = 1 * 1.e-33;

 double efficiency = 0.16 // stopping
   //* 0.5 // in HCAL
   //* 0.54; // filter eff
   //* 0.171; // stop in hcal, trigger, and filter eff
   * .092; //trigger and cut, trigger includes stopping in HCAL

double tstep = bctime; //0.1 / (lumi * xsection * efficiency);
double nDecays = lumi * tstep * xsection * efficiency;

std::cout << "using tstep = " << tstep << ", nDecays = " << nDecays 
	  << std::endl;

TH1D::SetDefaultSumw2 (true);
TH1D* hdecays = new TH1D("hdecays","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//days*24,0,days);

 TH1D* hdecaysReg = new TH1D("hdecaysReg","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//cycle);//days*24,0,days);
 TH1D* hperday = new TH1D("hperday","Number of Reconstructed Stopped Gluinos", days,0,days);
 TH1D* hinday = new TH1D("hinday", "Number of Reconstructed Stopped Gluinos", 100, 0, 24*3600);
// hperday->SetMinimum(0);
TRandom rndm;


 int n;
 double t;

 double total_counts = 0, beam_counts = 0, cosmic_counts = 0;
 double s_total_counts = 0, s_beam_counts = 0, s_cosmic_counts = 0;
 double b_total_counts = 0, b_beam_counts = 0, b_cosmic_counts = 0;

 if (signal_on)
 for (t = 0, n = 0; n < bxs && signal_on; t += tstep, n++) {
  if (beam[n]) {
    int nRandomDecays = scale*nDecays*nOrbits*days; //rndm.Poisson;
    for (int ig = 0; ig < nRandomDecays ; ig++) {

      double tau = rndm.Exp (lifetime);
      double tdecay = t + tau;
      double cycletime = tdecay/cycle - floor (tdecay/cycle);
      double cycles = tdecay/cycle;
      
      unsigned long orbit = rndm.Integer(nOrbits);
      int day = rndm.Integer(days);

      hdecays->Fill (cycletime*bxs, 1./scale);

      //      if (cycletime > dutycycle) {
      // at t==0, counter == 0, so rounding is correct:

      //      cout << "cycles " << cycles << endl;

      // Hope this is precise enough...
      double quotient = (cycles + orbit)/(nOrbits+nOrbitsOff);
      double remainder = (cycles + orbit) - floor(quotient)*(nOrbits+nOrbitsOff);
      if (quotient+day >= days) continue;
      if (remainder < nOrbits && !beam[ int(cycletime * bxs) ]) {
	s_beam_counts+= 1./scale;

	hdecaysReg->Fill (cycletime*bxs, 1./scale);
	hperday->Fill (quotient+day, 1./scale); 
	hinday->Fill(remainder*bxs*bctime, 1./scale);
      }
      else if (remainder > nOrbits ) {
	s_cosmic_counts+= 1./scale;

	hperday->Fill (quotient+day, 1./scale);
	hinday->Fill(remainder*bxs*bctime, 1./scale);
      }
    }
  }
 }


 // BACKGROUND
 if (background_on)
 for (int i = 0; i < days; i++) {
   
   int todays_rate = bg_per_day*bgscale;//rndm.Poisson(bg_per_day);

   for (int j = 0; j < todays_rate; j++) {

   // pick an orbit

     unsigned long orbit = rndm.Integer(nOrbits+nOrbitsOff);

   // pick a bin

     unsigned int bunch = rndm.Integer(bxs);

   // fill

     hdecays->Fill(bunch, 1./bgscale);
     if (orbit <= nOrbits && !beam[ bunch ]) {
	b_beam_counts+=1./bgscale;

	hdecaysReg->Fill (bunch, 1./bgscale);
	hperday->Fill (i, 1./bgscale); 
	hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
      }
      else if (orbit > nOrbits ) {
	b_cosmic_counts+=1./bgscale;

	hperday->Fill (i, 1./bgscale);
	hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
      }
   }
 }

 beam_counts = s_beam_counts + b_beam_counts;
 cosmic_counts = s_cosmic_counts + b_cosmic_counts;
 s_total_counts = s_beam_counts + s_cosmic_counts;
 b_total_counts = b_beam_counts + b_cosmic_counts;
 total_counts = beam_counts + cosmic_counts;

 cout << "Signal timing efficiency: " << s_total_counts 
      << " / " << bxs_on * nRandomDecays / scale
      << " = " << (double)(s_total_counts) * scale / (bxs_on * nRandomDecays)
      << endl << endl;

 cout << "Total counts: " << total_counts << endl;
 double expected_total = bg_per_day * (nOrbits*bxs_off/bxs + nOrbitsOff)/(nOrbits+nOrbitsOff)*days;
 cout << "Expected total background: " << expected_total << endl
      << " sigma:   " << sqrt(expected_total) << endl
      << " 3 sigma: " << 3*sqrt(expected_total)+expected_total << endl
      << " 5 sigma: " << 5*sqrt(expected_total)+expected_total << endl << endl;

 cout << "Total Experiment Outcome: " << (total_counts - expected_total)/sqrt(expected_total) << endl;
 cout << "Total Expected   Outcome: " << (s_total_counts)/sqrt(expected_total) << endl << endl;

 cout << "Beam counts : " << beam_counts << endl;
 double expected_beam = bg_per_day * (nOrbits*bxs_off/bxs)/(nOrbits+nOrbitsOff)*days;
 cout << "Expected beam background: " << expected_beam << endl
      << " sigma:   " << sqrt(expected_beam) << endl
      << " 3 sigma: " << 3*sqrt(expected_beam)+expected_beam << endl
      << " 5 sigma: " << 5*sqrt(expected_beam)+expected_beam << endl << endl;
 
 cout << "Beam Experiment Outcome: " << (beam_counts - expected_beam)/sqrt(expected_beam) << endl;
 cout << "Beam Expected   Outcome: " << (s_beam_counts)/sqrt(expected_beam) << endl << endl;

 cout << "Cosmic counts: " << cosmic_counts << endl;
 double expected_cosmic = bg_per_day * (nOrbitsOff)/(nOrbits+nOrbitsOff)*days;
 cout << "Expected total background: " << expected_cosmic << endl
      << " sigma:   " << sqrt(expected_cosmic) << endl
      << " 3 sigma: " << 3*sqrt(expected_cosmic)+expected_cosmic << endl
      << " 5 sigma: " << 5*sqrt(expected_cosmic)+expected_cosmic << endl << endl;

 cout << "Cosmic Experiment Outcome: " << (cosmic_counts - expected_cosmic)/sqrt(expected_cosmic) << endl;
 cout << "Cosmic Expected   Outcome: " << (s_cosmic_counts)/sqrt(expected_cosmic) << endl << endl;


}
