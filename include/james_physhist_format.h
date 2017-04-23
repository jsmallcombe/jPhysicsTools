//
//
//	James Root Library
//	Formatting tools for TH1/2/3
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesphyshistfor_h
#define jamesphyshistfor_h

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TVirtualPad.h>
#include <TBox.h>
#include <TLatex.h>
#include <TLine.h>
#include <TMarker.h>
#include <TROOT.h>
#include <TPolyLine.h>

#include "james_gpad_tools.h"
#include "james_fitting.h"
#include "james_nuclear_data_ob.h"
#include "james_hist_formatting.h"

using namespace std;

//Draw a marker arrow and text
//pairpad can be used in the case of layered pads e.g from preapre_canvas 
void AddElectronLabel(double Ey,string Z,bool exact=false,bool M=true,string text="",TVirtualPad* pad=gPad,TH1* hist=0,TVirtualPad* pairpad=0);

//For use with draw_electron_gamma
// The first option draws label to respective pad so they will scale
// The second option draws sets the range and draws all labels to the top pad
void AddElectronGammaLabels(TCanvas* bisected,double E,string Z,bool exact=false,string text="",bool M=true);
void AddElectronGammaLabels(TCanvas* bisected,double UrangeL,double UrangeU,double E,string Z,string text="");

#endif // #ifdef jameshistfor_h
