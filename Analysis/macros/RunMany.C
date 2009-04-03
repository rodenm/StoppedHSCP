
// run Toy MC for a bunch of different scenarios
{

  ToyStoppedHSCP* toy = new ToyStoppedHSCP("Results.root");
  
  // stable parameters
  double bxstruct = 156;
  double lumi = 1e32;
  double bgrate = 0.00039;
  
  // changing params
  // for nice lifetime plots
  double lifetime[6] = { 1.e-6, 
			 1.e-3, 
			 3600., 
			 43200., 
			 86400., 
			 604800. };

  double ndays[8] = { 1., 3., 7., 30., 90., 360., 1080. };
  
  // mass points
  double mass[7] = { 300.,
		     400.,
		     500.,
		     600.,
		     700.,
		     800.,
		     900. };
  
  double efficiency[7]   = {  0.158 * 0.162,  //selection eff * stopping eff
			      0.171 * 0.160,
			      0.184 * 0.158,
			      0.186 * 0.164,
			      0.188 * 0.171,
			      0.190 * 0.171,
			      0.192 * 0.171 
  };
  
  double xsection[7] = { 5.e-34,
			 1.5e-34,
			 5.e-35,
			 1.5e-35,
			 5.e-36,
			 2.5e-36,
			 1.e-36 };
  

  for (unsigned l=0; l<7; ++l) {  
    std::cout << "Lifetime " << l << " " << lifetime[l] << std::endl;
  }  
  
  // loop over running time
  for (unsigned nd=0; nd<5; ++nd) {
    
    // loop over liftime
    for (unsigned l=0; l<7; ++l) {

      // loop over masses
      for (unsigned m=0; m<7; ++m) {
	//      unsigned m=0;

	Experiment e;
	e.lumi = lumi;
	e.bxStruct = bxstruct;
	e.bgRate = bgrate;
	e.runningTime = ndays[nd];
	e.lifetime = lifetime[l];
	e.mass = mass[m];
	e.crossSection = xsection[m];
	e.signalEff = efficiency[m];
	toy->run(e);
	
      }
      
    }
    
  }
  
  
}
