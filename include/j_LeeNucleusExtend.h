//
//
//	jPhys Root Library
//	Classes to automate interact with Lees ENSDF parsed data file
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef lee_nuc_ext
#define lee_nuc_ext

#include <TMath.h>

#include "LeeNucleus.h"

//datum = double[3]

using namespace std;

	// An inherited class from Lees ENSDF parser cNucleus
	// Written to give additional functions but contains no members to enable static_cast

	// Level "index" starts from 1 not 0

	class cNucleusInh : public cNucleus{
	public:
		cNucleusInh():cNucleus(){};
		~cNucleusInh(){};
		
		int GetZ(){return nProton;};
		int GetA(){return nMass;};
		int GetN(){return nNeutron;};
		
		int GetNTrans(){return nTransitions.size();}
		vector < double > GetTrans(unsigned int i){if(i<nTransitions.size())return nTransitions[i];return vector<double>();}

		int ENSDF_find_level(int fJ,int fParit,int fOrder,int fTent);
		int ENSDFLevelN(unsigned int index);//pure tentative
		string ENSDFLevelString(unsigned int index);
		string ENSDFTransitionString(unsigned int index_p,unsigned int index_d);
		string ENSDFTransitionString(unsigned int i);
		string ENSDFNucleusString();
		
		bool IsTrans(unsigned int i);
		bool GetTransEnergy(double* datum,unsigned int i);
		double GetTransEnergy(unsigned int i);
		int GetTransP(unsigned int i);
		int GetTransD(unsigned int i);
		
		bool IsLevel(unsigned int index);
		double GetLevelEnergy(unsigned int index);
		bool GetLevelEnergy(double* datum,unsigned int index);
		bool GetLevelLifetime(double* datum,unsigned int index);
	
		
		static string LevelString(int,int,int,int);
 		//static string FormatTransitionText(vector<double> &T,int f,int Z, int A);
		static string PM(int pm);

	};
 

	class NucDatumSpecifier{
	public:
		NucDatumSpecifier():cColour(1){};
		~NucDatumSpecifier(){};
		
		int cDatumType;//Datum Level=0/Lifetime=1/Statelifetime=2
		int cDrawType;//Level=0/axisdata=1/data=2
		int cMarker;//Marker Style
		int cColour;//Marker Colour
		int cPJ;//Parent Level J, -1 for any (i.e. order only)
		int cPP;//Parent Level Pi -1,0,1
		int cPN;//Parent Level Order
		int cPT;//Parent Level Tentative 0/1 allow tentative
		int cDJ,cDP,cDN,cDT;//Daughter Level
		int oddZ,oddN;//0=all 1=even 2=odd
		
		string ParentString();
		string DaughterString();
		int GetParentLeveli(cNucleusInh* nucleus);
		int GetDaughterLeveli(cNucleusInh* nucleus);

		bool GetDatum(double *datum,cNucleusInh* nucleus);
		string AdderName();
	};
	
		
	
#endif
