//
//
//	James Root Library
//	Target Object and related functions
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesnar_h
#define jamesnar_h

#include <iostream>
#include <cmath>
#include <vector>
#include <sstream>

#include <TMath.h>
#include <TH2.h>
#include <TVector3.h>
#include <TRotation.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TFile.h>
#include <TRandom2.h>
#include <TLorentzVector.h>

// #include <TCanvas.h>
// #include <TPad.h>



// extern "C" {
// #include <dedx.h>
// }
// class target
// { 
// 	private:
//     
// 		dedx_workspace *ws;
// 		dedx_config *cfg;
// 		
// 	public:
// 	target(){
// 		int err;
// 		int datasets=1;
// 		cfg = (dedx_config *)calloc(1,sizeof(dedx_config));
// 		ws = dedx_allocate_workspace(datasets, &err);
// 	};
// 	~target(){
// 		int err;
// 		dedx_free_workspace(ws, &err);
// 		dedx_free_config(cfg, &err);
// 	};
// };

#include "james_root_maths.h"
#include "james_physics.h"


using namespace std;

class StoppingRange;


///////////////////////////////////////////////
/////////// Conversion functions    ///////////
///////////////////////////////////////////////

// Returns effective thickness for arbitrary trajectory
// Beam direction = (0,0,1)
// Axis of rotation = (0,1,0), clockwise from "above"
// [Inputs(Trajectory (Tvector3),Rotation (degrees),Nominal thickness (arb.))]
double target_effective(TVector3,double,double);

// Returns effective thickness for arbitrary trajectory
// Beam direction = (0,0,1)
// [Inputs(Trajectory (Tvector3),Target Normal (Tvector3),Nominal thickness (arb.))]
double target_effective(TVector3,TVector3,double);

// Returns thickness in (um)
// [Inputs(Density (g/cm3),Arial density (mg/cm2))]
double giveme_um(double g_cm3,double mg_cm2,bool print=false);

// Returns arial density in (mg/cm2)
// [Inputs(Density (g/cm3),Thickness (um))]
double giveme_areal(double g_cm3,double um,bool print=false);


class target
{ 
	private:
	////////////////////////////////////////
	/////////// Data members    ///////////
	///////////////////////////////////////

	vector< StoppingRange > rangelist;
	vector< StoppingRange > rangelist_back;
	
	vector< int > compZ,compA,bompZ,bompA;
	vector< double > compR,bompR;

	int targ_Z;
	int targ_A;
	double target_thickness;//mg/cm^2
	bool targ_compound;

	double backing_thickness;//mg/cm^2
	int backing_Z;
	int backing_A;
	bool backing_compound;
	
	bool downstream_back;	

	TVector3 targ_norm; //should point away from backing (either beam or -beam)
	TVector3 targ_fornmal; //either norm or anti norm, point beamward
	
		
	////////////////////////////////////////
	///////////    Member Fn    ///////////
	///////////////////////////////////////
	    
	
	StoppingRange* GetRangeD(int z,int a);
	StoppingRange* GetRangeDBack(int z,int a);
	// Calculate energy change in a target
	// Start and end fraction should match trajectort orientation
	// If reverse, E is the energy AFTER and you will get energy BEFORE
	// [Inputs(particle_Z, particle_A, E (MeV), Trajctory, start frac, end frac, reverse?)]
	
	double traverse(int,int,double,TVector3,double,double,bool=false);
	
	void SetNormal();
	
    public:
	


		
	////////////////////////////////////////
	/////////// Data members    ///////////
	///////////////////////////////////////
	    
	    
	////////////////////////////////////////
	/////////// Constructors    ///////////
	///////////////////////////////////////

	
	// Backing is defined as UPstream
	// For a downstream "backing" set Target targnorm = (0,0,-1)
	// Beam direction = (0,0,1)
	    
	// REMEMBER to use compounds && adjust arial density for enrichment!
	
	target(int targZ=6, int targA=12, double targmgcm=1.0, TVector3 targnorm=TVector3(0.0,0.0,1.0), int nul=0, double backmgcm=0, int backZ=0, int backA=0, int null=0);
	
	//Target Normal (TVector3) -> Rotation (degrees)
	// Axis of rotation = (0,1,0), clockwise from "above"
	target(int targZ, int targA, double targmgcm, double degrees, int nul=0, double backmgcm=0, int backZ=0, int backA=0, int null=0);
	
	//input of thickness is in mg/cm2. Historically it was ug!!
	
	//targcomp & backcomp do nothing
	
	
	//WOULD ALSO NEED AN ASSIGNMENT OPPERATOR
	target( const target &obj);//copy constructor
	
	//assignment operator
	target& operator=(const target&);
	
	//returns another target with backing and target material definitions flipped
	//geometrical orientation remains the same
	target inverse();
	
	~target(){};
	
		
	////////////////////////////////////////
	///////////    Member Fn    ///////////
	///////////////////////////////////////
	        
	    
	void SetNormal(TVector3 vec);
	TVector3 GetNormal(){return targ_norm;};
	TVector3 GetFormal(){return targ_fornmal;};
	double GetThickness(){return target_thickness;};//mg/cm2
	double GetBackThickness(){return backing_thickness;};//mg/cm2
	int Z(){return targ_Z;};
	int A(){return targ_A;};
	int bZ(){return backing_Z;};
	int bA(){return backing_A;};
	   
	
	void addcomp(int Z,int A,double R){
		targ_compound=true;compZ.push_back(Z);compA.push_back(A);compR.push_back(R);
		if(!(compZ[0]==targ_Z&&compA[0]==targ_A))cout<<endl<<endl<<"YOU SHOULD ENTER THE TARGET ISOTOPE FIRST IN THE COMPOUND"<<endl<<endl;
	}
	void addbackcomp(int Z,int A,double R){backing_compound=true;bompZ.push_back(Z);bompA.push_back(A);bompR.push_back(R);}

	// Returns particles / mb
	// based on target compound and A.
	double number_density();

	
	//////  Functions for fraction of whole target ////// 
		//// pos from -1 to 2  ////
	

	// Returns energy in MeV of beam AT centre of target
	double beam_e_centre(int beam_Z,int beam_A,double MeV,TVector3 vec=TVector3(0.0,0.0,1.0),double pos=0.5);
	
	// Returns energy in MeV of beam BEFORE target
	double beam_e_centre_reverse(int beam_Z,int beam_A,double MeV,TVector3 vec=TVector3(0.0,0.0,1.0),double pos=0.5);
	
	// Returns energy in MeV of paricle AFTER exit from centre
	double particle_e_exit(int z,int a,double MeV,TVector3 vec, double pos=0.5);
	
	// Returns energy in MeV of paricle BEFORE target exit
	double particle_e_reverse(int z,int a,double MeV,TVector3 vec, double pos=0.5);

	
	//////  Functions in mg/cm2 ////// 
	
	//Return dedx in MeV/(mg/cm2) slow function, not for loops
	double dedx(int z,int a,double MeV);
	
	//Return the energy of beam before target, given energy after
	double egap(int z,int a,double mg,double MeV);
	
	//Return the energy of beam after target
	double pass(int z,int a,double mg,double MeV);
	
	//Return range in mg/cm of particle
	double GetRange(int z,int a,double MeV);
	
	//Return MeV to required to travel range
	double GetEnergyTrav(int z,int a,double mg);
	
	//As above but for backing material
	double egapB(int z,int a,double mg,double MeV);
	double passB(int z,int a,double mg,double MeV);
	double GetRangeBack(int z,int a,double MeV);
	double GetEnergyTravBack(int z,int a,double mg);
	
	/////// FISSION STUFF  ////////////
	
	TH2F eloss_frag_graph_targ; //fission fragment energy graphs
	TH2F eloss_frag_graph_back;
	
// 	// Create a fission fragment energy lookup table in the target object
// 	// Slow initial process, attempts to load and save a local file.
// 	// [Inputs(Compound_Z, Compound_A)]	
	void fragment_set(double Z,double A);
// 	
// 	// Lookup fission fragment energy loss if table has been generated
// 	// [Inputs(Fragment_mass (amu), Fragment Energy (MeV), Trajctory)]		
	double fragment_e_exit(double,double,TVector3,double=0.5);//Z,a,MeV,vector
// 		

};


class StoppingRange
{ 

    private:
	int BeamZ,BeamA;
	void Build(vector<int> &TargZ,vector<int> &TargA,vector<double> &TargRatio);

    public:
	TGraph Range;
	TGraph Energy;
	StoppingRange(){};    
	StoppingRange(int bz,int ba,int tz,int ta);
	StoppingRange(int bz,int ba,vector<int> &tz,vector<int> &ta,vector<double> &tf);
	~StoppingRange(){};
	
	bool IsThis(int Z, int A);
	
	static double dEdXComp(double MeV, int zp, int ap, vector<int> &TargZ,vector<int> &TargA,vector<double> &TargRatio);// MeV/(mg/cm2)
	static double dEdX(double MeV, int zp, int ap, int zt, int at);// MeV/(mg/cm2)

};




#endif