
// run Toy MC for a bunch of different scenarios
{

  ToyStoppedHSCP* toy = new ToyStoppedHSCP("Results.root", "NeutralinoScan.log");
  
  // stable parameters
  double bxstruct = 2808;
  double lumi = 1e32;
  double bgrate = 0.00039;
  
  // changing params
  // for nice lifetime plots
  double lifetime[6] = { 1.e-6, 
			 1.e-3, 
			 3600., 
			 43200., 
			 86400., 
			 604800.
  };

  double ndays[6] = { 1.,
		      3., 
		      7., 
		      30.,
		      90.,
		      360.
  };
  
  // mass points
  // mass here is neutralino mass, not gluino!
  double mass[3] = { 50.,
		     100.,
		     200.
  };
  
  double efficiency[3]   = {  0.164 * 0.162,  //selection eff * stopping eff
			      0.158 * 0.162,
			      0.104 * 0.162
  };
  
  double xsection[3] = { 5.e-34,
			 5.e-34,
			 5.e-34
  };

  

  for (unsigned l=0; l<6; ++l) {  
    std::cout << "Lifetime " << l << " " << lifetime[l] << std::endl;
  }  
  
  // loop over running time
  for (unsigned nd=0; nd<5; ++nd) {
    
    // loop over liftime
    for (unsigned l=0; l<6; ++l) {

      // loop over masses
      for (unsigned m=0; m<3; ++m) {
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
