//
//
//	jPhys Root Library
//	Formatting tools for TH1/2/3
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jROORphyshistfor_h
#define jROORphyshistfor_h

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
#include <TArrow.h>
#include <TMarker.h>
#include <TROOT.h>
#include <TPolyLine.h>

#include "j_gpad_tools.h"
#include "j_fitting.h"
#include "j_nuclear_data_ob.h"
#include "j_hist_formatting.h"

using namespace std;


//Draw a marker arrow and text
//pairpad can be used in the case of layered pads e.g from preapre_canvas 
void AddElectronLabel(double Ey,string Z,bool exact=false,bool M=true,string text="",TVirtualPad* pad=gPad,TH1* hist=0,TVirtualPad* pairpad=0);

//For use with draw_electron_gamma
// The first option draws label to respective pad so they will scale
// The second option draws sets the range and draws all labels to the top pad
void AddElectronGammaLabels(TCanvas* bisected,double E,string Z,bool exact=false,string text="",bool M=true);
void AddElectronGammaLabels(TCanvas* bisected,double UrangeL,double UrangeU,double E,string Z,string text="");

class jPhysLevelScheme
{ 
    public:
	typedef struct LevelLabS{
		unsigned int Band;
		unsigned int Level;
		string Text;
		int Col;
		LevelLabS(unsigned int b=0,unsigned int l=0,string t=0,int c=-1):
		Band(b),Level(l),Text(t),Col(c){}// default Constructor
	} LevelLabS;


    private:
	std::vector< std::vector< double > > Energies;
	std::vector< std::vector< unsigned int > > LevelColor;
	std::vector< std::vector< string > > SpinLabels;
	std::vector< LevelLabS > ExtraLabels;
	
	std::vector< std::vector< int > > Transitions;
	
	unsigned int LineWidth;
	double StateWidth;
	double MaxE,MinE;
	double VertScale,VertOff;
	bool KeVLabel,DefaultIntra;
	double TextSize,LabelYOffset,BandXGap,ArrowSize;
	double gX0;
	
	double BandX(unsigned int b){return gX0+b*StateWidth*(1+BandXGap);}
	double EY(double E){return (E-VertOff)*VertScale;}
	
	void CalcVert(double Y0,double YRange);
	void DrawLevels();
	void DrawTransitions();
	void DrawExtraLabels();

	void DrawLevel(unsigned int band,unsigned int level);
	void DrawVerticalArrowPad(double X1,double Y1,double Y2,unsigned int col=1);
	void DrawBand(unsigned int b);
	void DrawInterBandExtension(unsigned int band1,unsigned int level1,unsigned int band2,double Xoffset);
	
    public:
	
	jPhysLevelScheme():LineWidth(2),StateWidth(0.1),MaxE(-1),MinE(-1),VertScale(1),VertOff(0),KeVLabel(0),DefaultIntra(0),
	TextSize(0.05),LabelYOffset(0.005),BandXGap(0.2),ArrowSize(0.3),gX0(0.2){};
	~jPhysLevelScheme(){};
	void AddLevel(unsigned int band,double Energy,string Label=" ",unsigned int col=1);
	void AddTransition(unsigned int band1,unsigned int level1,unsigned int band2,unsigned int level2,int col=1,double Xoffset=0){
		Transitions.push_back(std::vector< int >{(signed)band1,(signed)level1,(signed)band2,(signed)level2,col,(int)(Xoffset*1000)});
	}
	void SetArrowSize(double size){ArrowSize=size;}
	void SetLineWidth(unsigned int width){LineWidth=width;};
	void SetStateWidth(double width){StateWidth=width;};
	void SetOpt(double text,double yloff=0.005,double gap=0.2,bool kev=0){
		TextSize=text;
		LabelYOffset=yloff;
		BandXGap=gap;
		KeVLabel=kev;
	};
	void SetDefaultIntraband(){DefaultIntra=(!DefaultIntra);}
	
	void DrawScheme(double X0,double Y0,double YRange);

	void AddExtraLabels(unsigned int b,unsigned int l,string t,int c=-1){
		if(b<Energies.size()){
			if(l<Energies[b].size()){
				if(c<0)c=LevelColor[b][l];
				ExtraLabels.push_back(LevelLabS(b,l,t,c));
			}
		}
	}
	
};





#endif // #ifdef jROORhistfor_h
