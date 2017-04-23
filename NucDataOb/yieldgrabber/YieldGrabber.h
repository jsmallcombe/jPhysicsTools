//**********************************************************************************************************************//
// Author: Jack Henderson (TRIUMF) hacked by James
// jhenderson@triumf.ca
//
// YieldGrabber.cxx 
// Class to grab TRIUMF yield data from .dat files corresponding to the available targets. Then allows for the plotting
// of yields vs N and Z, and printing of yields for individual isotopes through inputting of N and Z values, or through
// point-and-click functionality on yield histograms via communication with the MouseAction subclass (MouseAction.h)
//
// For use with the ROOT framework
//
//**********************************************************************************************************************//

#ifndef YieldGrabber_h
#define YieldGrabber_h

#include "Declarations.h"
using namespace std;

	class YieldGrabber {	
		
	typedef struct _Isotope {// Data structure to define isotopes, only one required for each isotope
		vector<double> yield;			// Vector of isotope yields corresponding to:
		vector<int> proton_current;// The proton current on target
		vector<std::string> ion_source;							// The ion source used 
		vector<int>	state;				// The state of the isotope (e.g. ground state = 1, first metastable = 2)
		vector<std::string> tar_mat;								// The target material (SiC, TiC, etc.)
		double avg_yield;					// The mean yield for the isotope
		double max_yield;					// Maximum yield for the isotope
	} Isotope;				// The class itself
		
	private :	
		vector< vector< std::string > > data;	// Data, line-by-line
		vector< std::string > line_vec;		// Used for data input
		vector< string > target_mat;		// Used to retain information on target material

		bool data_grabbed;			// Flag: Is the data loaded?

		Isotope Nuclei[146][94];// Nuclear chart of isotopes [N][Z]

	public :
		
		YieldGrabber();					// Constructor
		virtual ~YieldGrabber(){;}// Destructor

	public :																										// Turn the data into Isotopes
		void CreateIntensityMatrix(int source = 0);
	
		int IonSourceComparison(std::string input);
		
		void Clear();						// Basic clear function, resets vectors, etc.
		void PrintIsotopeInfo(int z, int n);			// Print yields for the isotope given N and Z
		void GrabData(const char*); 							// Grab the data from the .dat files - put it in the data vector
		void ProcessData();			// Turn the data into Isotopes

		void Start();						// Initialises everything and starts the data grabbomg

		void PrintMeanIntensity(int, int);				// Prints the average intensity for a given isotope
};
#endif