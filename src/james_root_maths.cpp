//
//
//	James Physics version 1.3
// 	26/8/12		12/8/2014
//	james.smallcombe@outlook.com
//
//

#include "james_root_maths.h"

/////////////////////////////////////////////////////
/////////// Trig functions for lazy typing   ////////
/////////////////////////////////////////////////////

double Acos(double in){
	return acos(in);
}
double cos2(double in){
	return cos(in)*cos(in);
}

double Asin(double in){
	return asin(in);
}
double sin2(double in){
	return sin(in)*sin(in);
}

double Atan(double in){
	return atan(in);
}
double tan2(double in){
	return tan(in)*tan(in);
}



  /////////////////////////////////////////////
 /////////// Angle Difference calcs   ////////
/////////////////////////////////////////////

double angledifference(double A,double B){ //Angles in Radians
	while(A<0)A+=(2*TMath::Pi());
	while(B<0)B+=(2*TMath::Pi());
	while(A>(2*TMath::Pi()))A-=(2*TMath::Pi());
	while(B>(2*TMath::Pi()))B-=(2*TMath::Pi());
	
	double dphi=TMath::Abs(A-B);
	if(dphi>TMath::Pi())dphi=(2*TMath::Pi())-dphi;
	
	return dphi;
}

double angledifference_signed(double A,double B){ //Angles in Radians
	while(A<0)A+=(2*TMath::Pi());
	while(B<0)B+=(2*TMath::Pi());
	while(A>(2*TMath::Pi()))A-=(2*TMath::Pi());
	while(B>(2*TMath::Pi()))B-=(2*TMath::Pi());

	double dphi=A-B;
	if(dphi>TMath::Pi())dphi=(2*TMath::Pi())-dphi;
	if(dphi<-TMath::Pi())dphi=-((2*TMath::Pi())+dphi);
	
	return dphi;
}


double happy_phi(double phi)
{
	phi+=pi/2;
	while(phi<0)phi+=2*pi;
	return phi;
}

double happy_phi(TVector3 &vec)
{
	return happy_phi(vec.Phi());
}