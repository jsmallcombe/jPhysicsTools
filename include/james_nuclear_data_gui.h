//
//
//	James Root Library
//	Object for storing, loading and viewing nuclear data
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef __NUCLEAR_DATA_GUI_INCLUDED__   // if x.h hasn't been included yet...
#define __NUCLEAR_DATA_GUI_INCLUDED__   //   #define this so the compiler knows it has been included

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include <TBrowser.h>
#include <TCanvas.h>
#include <TText.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TBox.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TH2.h>
#include <TPad.h>
#include <TLine.h>
#include <TGaxis.h>
#include <TF2.h>
#include <TROOT.h>
#include <TTree.h>
#include <TFile.h>
#include <TRootEmbeddedCanvas.h>
#include <TGButtonGroup.h>
#include <TGButton.h>
#include <TGToolTip.h>
#include <TGComboBox.h>
#include <TGLabel.h>
#include <TColor.h>
#include <TGColorSelect.h>
#include <TGNumberEntry.h>





#include "james_nuclear_data_ob.h"
#include "james_utility.h"

class LiveDataGUIStyleControl;
class LiveDataAdder;
class LiveDataAdjuster;


class LiveDataSlicer : public TGMainFrame {
private:
	TRootEmbeddedCanvas* fCanvas1;
	TGButtonGroup* fBgroup1;
	TLine* markline;
	TGToolTip *fTip;
	bool needmagic;
	TGCheckButton* fCheck0;
	TCanvas *DataWindow;
	LiveDataAdder* Controls;
	LiveDataGUIStyleControl* Format;
	LiveDataAdjuster* Manual;
	
public:
	LiveDataSlicer(double(*)(int,int)=0);
	virtual ~LiveDataSlicer();

	void CanvasMouse(Int_t,Int_t,Int_t,TObject*);
	void AskDrawMagic();
	void ReDrawMagic();
	
	static void LiveChartClickExec(int,int);  
	
	void ShowLiveDataAdder();
	void ShowLiveDataFormat();
	void ShowLiveDataAdjust();
	
	void DataAdderClosed(){Controls=0;};
	void DataFormatClosed(){Format=0;};
	void DataAdjustClosed(){Manual=0;};
	
	ClassDef(LiveDataSlicer, 1)
};

//////////////////////////////////////////////////////////////////////

class LiveDataAdder : public TGMainFrame {
	friend class nuclear_data_ob;
private:
	TGButtonGroup *fBgroupZodd,*fBgroupNodd,*fBgroupDrawType;
	LiveDataAdderLevelSelect *LParent, *LDaughter;
	TGComboBox *Marker,*NuclesuProp;
	TGLabel* info;
	TGColorSelect* col;
	NucDatumSpecifier NDS;
public:
	LiveDataAdder();
	virtual ~LiveDataAdder();

	void UpdateCol(Pixel_t);
	void UpdateSelection();
	int oddZ();
	int oddN();
	void NucPropAdd();
	void LevelAdd();


	ClassDef(LiveDataAdder, 1)
};

////////////////////////////////////////////////////////////////////

class LiveDataAdderLevelSelect : public TGHorizontalFrame {
public:
	LiveDataAdderLevelSelect(const TGWindow *p=0);
	virtual ~LiveDataAdderLevelSelect(){Cleanup();};
	TGComboBox *LSpin,*LParity,*LOrder;
	TGCheckButton* fCheck0;
	TGTextButton* fTButton0;

	void UpdatedClicked();
	void AddClicked();

	ClassDef(LiveDataAdderLevelSelect, 1)
};


/////////////////////////////////////////////////////////////////////////////////////
/////////// Class for holding some data for pad drawing so isnt floating loose    ///
/////////////////////////////////////////////////////////////////////////////////////

class PadScanData
{
	public:
	// Constructor & Destructor
	PadScanData(){};
	~PadScanData(){};
	
	// Data
	public:
	static unsigned int numbertodisplay;//Set this manually to increase the list display size
	
	// Functions
	public:
	static int LoadFile(string);//string should be the absolute path to a text data file
	static int Draw(TVirtualPad* pad=gPad);//Draw/Connect in the currently selected pad
	static int UnDraw(TVirtualPad* pad=gPad);//Disconnect from the currently selected pad
	static void Clear();//Delete all stored data (Still drawn so  can just load new data)
	
	//Loads data from Lee Evitts ENSDF parser
	// cut is the parent energy
	// Format 0=energy only 1=nucleus 2=Jpi->Jpi
	static int AddData(string sym,int A=0,int format=0,double cut=-1);
	static int AddData(int Z,int A=0,int format=0,double cut=-1);
	static int AddElectronData(string sym,int A=0,int format=0,double cut=-1);
	static int AddElectronData(int Z,int A=0,int format=0,double cut=-1);

	
	//Example
	//PadScanData::Add_Data("Cd",111); //Load all 111Cd data
	//PadScanData::Add_Data(46,110,1); //Load all 110Pd data with level J(pi)s
	//PadScanData::Draw(); //Make visible on the current pad
	//PadScanData::Clear(); //Erase the previously 111Cd and 110Pd data, still drawn, but nothing to see
	//PadScanData::LoadFile("path/info.txt); //Load all data from info.txt, now something to see again
	//PadScanData::UnDraw();//Clears the screen but the info.txt data is still there if one calls PadScanData::Draw() again
	
	//signal slot connection for pad drawing
	static void Update(Int_t,Int_t,Int_t,TObject*);
	static void CanvasSelected(TVirtualPad*, TObject*, Int_t);
	static TVirtualPad* CurrentDraw;
	
};


////////////////////////////////////////////////////////////////////

class LiveDataGUIentry : public TGHorizontalFrame {
public:
	LiveDataGUIentry(const TGWindow *p=0,unsigned int in=0);
	virtual ~LiveDataGUIentry(){Cleanup();};
	
	private:
	unsigned int index;
	TGLabel *Tlabel;
	TGColorSelect* col;
	TGComboBox *Marker,*Type;

	public:
	void Modified();
	void Update();

	ClassDef(LiveDataGUIentry, 1)
};

////////////////////////////////////////////////////////////////////

class LiveDataGUIStyleControl : public TGMainFrame {
public:
	LiveDataGUIStyleControl();
	virtual ~LiveDataGUIStyleControl(){Cleanup();};
	
private:
	vector< LiveDataGUIentry* > Entries;
	
public:
	void Update();	
	ClassDef(LiveDataGUIStyleControl, 1)
};

////////////////////////////////////////////////////////////////////


class LiveDataAdjuster : public TGMainFrame {
public:
	LiveDataAdjuster();
	virtual ~LiveDataAdjuster(){Cleanup();};
	
private:
	TGNumberEntry *index,*mass,*value;
	TGLabel *Tlabel;
	TGTextEntry* fTeh1;
	
public:
	void ChangedIndex();	
	void ChangedSelection();	
	void Set();	
	ClassDef(LiveDataAdjuster, 1)
};

	
////////////////////////////////////////////////////////////////////
TGComboBox* TGComboBoxMarkerSelect(const TGWindow *p);

#endif 