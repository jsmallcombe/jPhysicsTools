//
//
//	James Root Library
//	Object for storing, loading and viewing nuclear data
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef __NUCLEAR_DATA_OB_H_INCLUDED__   // if x.h hasn't been included yet...
#define __NUCLEAR_DATA_OB_H_INCLUDED__   //   #define this so the compiler knows it has been included

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TH2.h>
#include <TPad.h>
#include <TLine.h>
#include <TText.h>
#include <TCanvas.h>
#include <TGaxis.h>
#include <TF2.h>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TBox.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButtonGroup.h>
#include <TGButton.h>
#include <TGToolTip.h>
#include <TGComboBox.h>
#include <TGLabel.h>
#include <TColor.h>
#include <TGColorSelect.h>

#include "james_LeeNucleusExtend.h"

#include "james_hist_formatting.h"
#include "james_root_maths.h"

  //////////////////////////////////////
 ////////// Useful Constants ////////// 
//////////////////////////////////////

const double jam_phys_amu=931.4940954; // MeV/c^2   /A
const double jam_phys_amu_kg=1.66053904e-27; // kg   /A
const double jam_phys_511=0.510998928; // MeV/c^2  
const double jam_phys_np_mass=1.293367; // MeV/c^2   
const double jam_phys_speed_c=299792458; // m/s
const double jam_phys_speed_c_mm_ns=299.792458; // mm/ns
const double jam_phys_e4pieps=1.4399644895; // MeV fm  equivilant to finestruc*hbar*c
const double jam_phys_charge=1.60217657e-19; // C

using namespace std;

class LiveDataAdder;
class LiveDataAdderLevelSelect;


/////////////////////////////////////////////////////////////////////////////////////
/////////// "nuclear_data_ob" An object containing useful nuclear data    ///////////
///////////       For access function access and dynamic viewing data     ///////////
/////////// 	      Holds hard coded data added before compilation      ///////////
///////////            And dynamic data loaded during a session    	  ///////////  
///////////            Dynamic data can be read from a file or   	  /////////// 
///////////            Parsed from LeeEvitts ENSDF data parser   	  ///////////
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
/////////// FUNCTIONS ARE IN Z,A DATA&FILES ARE IN Z,N . ARRAYS [128][256] //////////
/////////////////////////////////////////////////////////////////////////////////////

class nuclear_data_ob
{
	friend class LiveDataSlicer;
	friend class cNucleusIterator;
	friend class LiveDataAdder;
	friend class PadScanData;
	friend class LiveDataGUIentry;
	friend class LiveDataGUIStyleControl;
	
	
	///////////////////////////////////////////////////
	/////////// Constructor & Destructor    ///////////
	//////////////////////////////////////////////////
	public:
	//Shouldn't ever actually need to call as operates as a static class
	nuclear_data_ob(){Clear();set_data();};
	~nuclear_data_ob(){};
	static void Clear();// Clears all dynamic session data and closes ENSDF data TFile
	
	
	//////////////////////////////////////////////////
	///////////  Admin  Methods & Members   //////////
	//////////////////////////////////////////////////
	private:
	// Called by all "getter" functions. Checks if inputs are within array range.
	static short general_reader(int z,int a);
	static short general_reader(int z){return general_reader(z,z);}	
	
	// Loads hard-coded data from disk to static array if not already done
	// Called by general_reader and hence all "getters" so never needs to be called manually
	static void set_data();
	static bool data_set;//Bool set when data loaded

	///////////////////////////////////////////
	//////// Hard Coded Data Members  ////////
	///////////////////////////////////////////
	private:		
	//manual lists
	static string elem_sym_list[128];	

	//auto generated (from .txt) hard coded data arrays  AND	
	//Auto generated list of data "getter" functions
	//A.txt -> get_A(Z,A)
	#include "NucDataHeaders.h"

	///////////////////////////////////////////
	//////// Hard coded Data Functions  //////
	///////////////////////////////////////////	
	public:
		
	/////BASIC ACCESS/////	
	static double get_mass_excess(int z,int a);//Returns mass excess in MeV or zero if undefined [Inputs(Z,A)]
	static double get_mass_MeV(int z,int a);	//Returns mass in MeV [Inputs(Z,A)]
	static double get_mass(int z,int a);	//Returns mass in amu [Inputs(Z,A)]
	static double get_nom_density(int z);//Returns nominal density g_cm3 at stp, or 1.0 [Inputs(Z)]   
	static int get_Z(string symbol);//Convert symbol to atomic number [Inputs("Chemical symbol")]
	static string get_symb(int z);//Convert atomic number to Chemical symbol[Inputs(Z)]
	static bool is_mass(int z,int a);//Returns TRUE if mass excess defined [Inputs(Z,A)]
	
	static double Sn(int z,int a);//Returns separation energy in MeV [Inputs(Z,A)] 
	static double Sp(int z,int a);
	static double S2n(int z,int a);
	static double S2p(int z,int a);
	//Internal calculation of the above
	static double SepCal(int z,int a,int p,int n);
    
	static double nn(int z,int a);
	static double pp(int z,int a);
	static double np(int z,int a);
	
	static double Qalpha(int z,int a);
	
	static double Qbeta_p(int z,int a);
	static double Qbeta_EC(int z,int a);
	static double Qbeta_m(int z,int a);
	
	static double BE(int z,int a);
	static double BE_A(int z,int a);
	
	///// Formatted outpus //////
	
	static string channelname(int z,int a=0);//Returns a channel name for nuclei and other nuclear particles based on charge and mass
	static TH2F* lifetime_hist();	//Returns a pretty histogram that doesnt give clear values 
	static TGraph* get_isobar_excess(int A);//x-axis=Z & y-axis=mass excess in MeV [Inputs(A)]   //Creates a TGraph and return pointer	   
	static TGraph* get_znratio_excess(int z,int a);//x-axis=A & y-axis=mass excess in MeV [Inputs(Z,N)]  //Creates a TGraph and return pointer	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////
	///////// Dynamic Data Members  ///////////
	///////////////////////////////////////////	
	
 	//Store live session data not saved to the class
	//They are static and shared across all instances of the class for dynamic access reasons
	//They are cleared when initialising a new instance of the class
	
	private:
	// These store data, 1 item of data across the nuclear chart
	// And control parameters for drawing etc
	// They are private with public methods for filling
	static unsigned int livedatapick;
	static vector< vector< vector< double > > > live_data;
	static vector< vector< vector< double > > > live_data_upper_error;
	static vector< vector< vector< double > > > live_data_lower_error;
	static vector< string > live_data_names;
	static vector< unsigned int > live_data_color;
	static vector< unsigned int > live_data_marker;
	static vector< unsigned int > live_data_type;	// Types 0=level 1=axis data 2=non-axis data 3+ hidden
	//Push back a blank element of the correct size to all of the above
	static void push_data_live(string name,unsigned int type=0,unsigned int col=1,unsigned int mark=0);
    

	
	// Pointer to ENSDF data tree. Function loads from disk if not already open
	static TTree* LeeData();
	static TFile* LeeFile;
	static TTree* LeeTree;
	
	/////////////////////////////////////////////////
	//////// Dynamic Data Access Functions  /////////
	/////////////////////////////////////////////////
	
	public:	
	// Manually add data to the in session dynamic data lists
	// Types 0=level 1=axis data 2=non-axis data 3+ hidden
		
	//"path/name.txt" Format should be "Z N data"
	static void add_data_live(string filename,unsigned int type=0,unsigned int col=1,unsigned int mark=0);
	//Vector[z,n]
	static void add_data_live(vector< vector < double > >& data,string name,unsigned int type=0,unsigned int col=1,unsigned int mark=0);
	//Use to copy hard-coded data to dynamic member list e.g.add_data_live(nuclear_data_ob::S2n,"S2n");
	static void add_data_live(double (*)(int,int),string,unsigned int type=0,unsigned int col=1,unsigned int mark=0);

	//Overide one single value
	static double modify_data_live(unsigned int i,int z,int a,double v);

	//Save all live data and formatting 
	static void saveall_data_live(string filename="Data.txt");
	static void readall_data_live(string filename="Data.txt");
	
	
	//Get a single datum of a single nucleus
	static double get_data_live(unsigned int i,int z,int a);//Live data access function (idiot proof) dataset,Z,A
	static void get_data_live_errors(unsigned int i,int z,int a,double& yu,double& yl);		
	static void set_data_live(unsigned int i);//Set dataset for the bellow
	static double data_live(int z,int a);//Live data access function (idiot proof) Z,A
		
	//Current number of dynamic datum lists
	static unsigned int size_data_live(){return live_data_names.size();};
	
	// Return the stored name of a live data set
	static string get_name_data_live(unsigned int);
	static unsigned int get_type_data_live(unsigned int);
	static unsigned int get_colour_data_live(unsigned int);
	static unsigned int get_marker_data_live(unsigned int);

	/////////////////////////////////////////////////
	////////  Dynamic Data Other Functions  /////////
	/////////////////////////////////////////////////
	public:	
	
	//Print the current settings of the dynamic data to terminal
	static void print_data_live();	

	//Return a histogram of one dynamic datum list
	static TH2F* hist_data_live(unsigned int i);	
	
	// Change the graphical formatting of existing data set
	static void format_data_live(unsigned int i,unsigned int type=0,unsigned int col=1,unsigned int mark=0);
	
	// zero (remove) all but desired odd/even/both Z/N values of one dynamic data set (0=all,1=even,2=odd)
	static void data_live_odd_even(unsigned int i,int oddZ,int oddN);
	
	
	private://internal method
	static bool odd_even(int z,int n,int oddZ,int oddN){return ((!oddZ||(z+oddZ)%2)&&(!oddN||(n+oddN)%2));}

  
	//////////////////////////////////////////////
	////// Dynamic Data Draw & PENS parser  //////
	//////////////////////////////////////////////

	private: 	
	//Draw all the live dynamic data
	static void LiveDynamicExec(TVirtualPad*,Int_t,Int_t,Int_t,TObject*);  
	static void LiveDynamicExec(TVirtualPad*,int,int,int,double=0.,double=256.);

	public:
	static void AddENSDFdatum(NucDatumSpecifier* NDS);
	
 	//////////////////////////////////
	//////// Graphical Stuff   ///////
	//////////////////////////////////

	public:
	static double level_width;// Width of drawn levels, can be set at any time, default 0.4
	static void addmagic(TVirtualPad* =gPad,bool=0);//Draw basic magic numbers, double lines bool
	static void addmagic(TH2* hist);
	static void chart_format(TH2*);	
			
	/////////////////////////////////////
	////// 1D Dynamic Energy Data  //////
	/////////////////////////////////////	
	
	// Dynamic session list for 1D data for energy searches
	private:
	static vector< string > ScanTransString;
	static vector< double > ScanTransEnergy;

	public:	
	/// Transition lists for pad scanner
	static int AddElectronListLee(string sym,int A=0,int format=0,double cut=-1);
	static int AddElectronListLee(int Z,int A=0,int format=0,double cut=-1);
	static int AddEnergyListLee(string sym,int A=0,int format=0,double cut=-1);
	static int AddEnergyListLee(int Z,int A=0,int format=0,double cut=-1,double subtraction=0,string note="");//Z,A,format,Emax,subtraction,note
	static int LoadEnergyListFile(string);// path/file.txt

};




class cNucleusIterator{
private:
	long iter_i;
	cNucleus* nucpoint;
public:
	cNucleusIterator();
	virtual ~cNucleusIterator();
	cNucleusInh* operator() ();
}; 

#endif 
