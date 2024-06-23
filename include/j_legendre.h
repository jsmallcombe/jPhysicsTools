//
//
//	jPhys Root Library
//	Manual calculation of legendre polynomials and gamma ray distributions
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jROORlegend_h
#define jROORlegend_h

#include <iostream>
#include <cmath>
#include <vector>
#include "j_root_maths.h"

#if !defined (__CINT__) || ROOT_VERSION_CODE > 336418

#include "wignerSymbols.h"
#include "gsl/gsl_sf_legendre.h"

using namespace std;

long j_int_fac(long);


class legendre_polynomials
{ 
	//http://mathworld.wolfram.com/AssociatedLegendrePolynomial.html
    public:
	legendre_polynomials(int=1);
	legendre_polynomials( const legendre_polynomials &obj);//copy constructor
	legendre_polynomials& operator=(const legendre_polynomials&);//assignment operator
	legendre_polynomials(legendre_polynomials&&) = default;                    // Move constructor
	legendre_polynomials& operator=(legendre_polynomials&&) & = default;       // Move assignment operator
	~legendre_polynomials(){}
	
	double eval(double);
	double eval_associated(int,double);
	
	
	private:
	int l;
	double tfac;
	std::vector< int > poly_hold;
	std::vector< std::vector< int > > poly;
	
	void legen_internal(int rev);
	void int_poly_diff();
	
};

class spherical_harmonic
{ 
	//http://mathworld.wolfram.com/SphericalHarmonic.html
    public:
	
	spherical_harmonic(int=1);

	spherical_harmonic( const spherical_harmonic &obj)= default;//copy constructor
	spherical_harmonic& operator=(const spherical_harmonic&)= default;//assignment operator
	spherical_harmonic(spherical_harmonic&&) = default;                    // Move constructor
	spherical_harmonic& operator=(spherical_harmonic&&) & = default;       // Move assignment operator
	~spherical_harmonic(){}
	
	double real(int,double,double);
	double imaginary(int,double,double);
	double modsq(int,double,double=0);
	
	double gamma_Z(int,double);
	
	int get_l(){return l;}
	
	private:
	int l;
	std::vector< double > tfac;
	legendre_polynomials poly;
	
	double core(int&,double&);
	
};


class gamma_dist
{ 
	//http://mathworld.wolfram.com/SphericalHarmonic.html
    public:
	
	gamma_dist(int=0);

	gamma_dist( const gamma_dist &obj)= default;//copy constructor
	gamma_dist& operator=(const gamma_dist&)= default;//assignment operator
	gamma_dist(gamma_dist&&) = default;                    // Move constructor
	gamma_dist& operator=(gamma_dist&&) & = default;       // Move assignment operator
	~gamma_dist(){if(sphe)delete sphe;}
	
	void set_gamma_L(int);
	void set_alignment(double,double);
	double simplified_gamma_dist(double,double);//ignores nuclear matrix elements
	
	private:
	double J1,J2;
	std::vector< double > alighnment;
	spherical_harmonic* sphe;
		
};


double clebschgordancoefficients(double,double,double,double,double,double);
bool jhic(double);
double clebsch_print(double,double,double,double,double,double);

#endif 

#endif 
