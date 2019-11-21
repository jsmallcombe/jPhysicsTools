//
//
//	jPhys Root Library
//	Relativistic Kinematics and other physics functions
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jROORgammarays_h
#define jROORgammarays_h

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include <TMath.h>
#include <TH1.h>


#include <TLorentzVector.h>
#include <TVector3.h>
#include <TRandom2.h>


#include "j_root_maths.h"
#include "j_effpeaks.h"

using namespace std;

double ComptonProb_dsig_dT(double KeV,double keV0,bool electron=true);//Note this formula is nor properly normalised
inline double ComptonProb_e(double KeV,double keV0){return ComptonProb_dsig_dT(KeV,keV0,true);}
inline double ComptonProb_Y(double KeV,double keV0){return ComptonProb_dsig_dT(KeV,keV0,false);}
double MyKeVNorm(double keV0);

//Response without resolution
Double_t GenGeResponseA(Double_t *x, Double_t *p);

TF1* GenGeResponseA(double keV0,double frakpeak,double fraccomp,double contshap,double cont);

TH1* GenGeResponse(double keV0,TH1* hist=0,int N=10000000,double reskeV=1.25,double frakpeak=0.6,double fraccomp=0.07,double contshap=0.04,double cont=0.15);

void ApplyGeEff(TH1* hist);


#endif
