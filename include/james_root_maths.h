//
//
//	James Root Library
//	Personal Maths Function Definition
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesrootmath_h
#define jamesrootmath_h

#include <cmath>
#include <TMath.h>
#include <TVector3.h>
using namespace std;


void higher_jd(double &low,double &high);
void swap_jd(double &,double &);


double jsigfig(double,int);

/////////////////////////////////////////////////////
/////////// Trig functions for lazy typing   ////////
/////////////////////////////////////////////////////

// ALL ANGLES IN RADIANS

double Acos(double);
double cos2(double);

double Asin(double);
double sin2(double);

double Atan(double);
double tan2(double);

const double pi=TMath::Pi();

inline double deg2rad(double deg){return deg*pi/180.0;}
inline double rad2deg(double rad){return rad*180.0/pi;}

  /////////////////////////////////////////////
 /////////// Angle Difference calcs   ////////
/////////////////////////////////////////////

// Give the difference between two angles in a consistent way
// Avoids +- problems and going over 2PI
// [Inputs (Angle 1(radians),Angle 2(radians))]

// Return abs angle magnitude
double angledifference(double,double);
// Return signed angle
double angledifference_signed(double,double);

double happy_phi(double);
double happy_phi(TVector3&);

#endif