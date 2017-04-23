#ifndef calibration_automation
#define calibration_automation

// Prefix:
//  gGlobal - Defined globally such as functions
//  fFunction - Defined within a function
//  sScope - Defined in a smaller scope e.g. while loop

#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TF1.h>
#include <TAxis.h>
#include <TMath.h>
#include <TGraph.h>
#include <TSpectrum.h>
#include <TRandom2.h>


// C++
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

#include "LEJTSfitting.h"

using namespace std;

//
// Returns a list of peaks positions (in user coordinates not bin) using TSpectrum (not optimised)
// Orders the peaks based a quick, first order, integral of counts.
//
vector<double> FindOrderedPeaks(TH1*);

//
// Does a KL fit to a histogram for a list of peak positions
// Optional L_sep, Fit range down, Fit range up (in user coordinates not bin)
//
vector< FullFitHolder* > FitElectronList(TH1*,vector<double>,double=-1,double=40,double=30);

//
// As above but asks for user confirmation of each fit.
// Responses for user in put "y" accept and add to list + histogram, "q" end (reject all remaining fits) 
// 
vector< FullFitHolder* > FitCheckElectronList(TH1*,vector<double>,double=-1,double=40,double=30);


//
// Fills a TGraph with the optimum pairing of two sets of numbers
// First list is known energies Second peaks
// First list must be >= second list and must contain a matching value for every entry in second list
//
TGraph AutoCal(vector<double>&,vector<double>&);

#endif