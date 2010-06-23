#ifndef PLOTTER_H
#define PLOTTER_H

#include <TCanvas.h>
#include <TGraph.h>

class Plotter
{
public:
    Plotter();

    TCanvas *getEfficiencyPlot(TGraph *, TGraph * = NULL);
    TCanvas *getVetoesPlot(TGraph *);
    TCanvas *getZbPlot(TGraph *, TGraph *, TGraph *,
		       TGraph *, TGraph *, TGraph *);
    TCanvas *getExclusionPlot(TGraph *, TGraph *, TGraph *, TGraph *);
    TCanvas *getCSExclusionPlot(TGraph *, TGraph *);

protected:
    void Style();
};

#endif // PLOTTER_H
