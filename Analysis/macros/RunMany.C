
// run Toy MC for a bunch of different scenarios
{

  ToyStoppedHSCP* toy = new ToyStoppedHSCP("Results.root");
  
  // stable parameters
  double bxstruct = 2808;
  double lumi = 1e32;
  double bgrate = 0.0005;
  
  // changing params
  // for nice lifetime plots
//   double lifetime[6] = { 1.e-6, 
// 			 1.e-3, 
// 			 3600., 
// 			 43200., 
// 			 86400., 
// 			 604800. };

  // for lifetime coverage
  double lifetime[7] = { 1.e-6, 
			 1.e-3,
			 1.e-1,
			 1.,
			 1.e1,
			 1.e3,
			 1.e6 };
  
  double ndays[8] = { 1., 3., 7., 30., 90., 360., 1080. };
  
  // mass points
  double mass[7] = { 300., 400., 500., 600., 700., 800., 900. };
  double efficiency[7]   = { 
    0.175 * 0.16,  //selection efficiency * stopping efficiency
    0.180 * 0.082,
    0.185 * 0.056,
    0.190 * 0.056,
    0.195 * 0.056,
    0.200 * 0.056,
    0.200 * 0.056 
  };
  
  double xsection[7] = { 0.5e-33, 1.0e-34, 0.5e-34, 1.0e-35, 0.5e-35, 1.0e-36, 0.5e-36 };
  

  for (unsigned l=0; l<7; ++l) {  
    std::cout << "Lifetime " << l << " " << lifetime[l] << std::endl;
  }  
  
  // loop over running time
  for (unsigned nd=0; nd<7; ++nd) {
    
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
