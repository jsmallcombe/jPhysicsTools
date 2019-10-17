#include "james_nuclear_data_gui.h"

	//////////////////////////////////////////////////
	///////////     Live Data Slicer        ///////////
	//////////////////////////////////////////////////
	
ClassImp(LiveDataSlicer);

LiveDataSlicer::LiveDataSlicer(double (*dataget)(int,int)) : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame),Controls(0),Format(0),Manual(0){	
	SetCleanup(kDeepCleanup);	
	SetWindowName("LiveDataSlicer");
	markline=0;
	needmagic=false;
	
	fCanvas1 = new TRootEmbeddedCanvas("Canvas1", this, 600, 400);
	fCanvas1->GetCanvas()->SetBorderMode(0);
	fCanvas1->GetCanvas()->SetMargin(0.1,0.03,0.1,0.03);	
	fCanvas1->GetCanvas()->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "LiveDataSlicer", this,"CanvasMouse(Int_t,Int_t,Int_t,TObject*)");
	fCanvas1->GetCanvas()->Connect("RangeChanged()", "LiveDataSlicer", this, "AskDrawMagic()");	

	TGHorizontalFrame* controlframe = new TGHorizontalFrame(this, 0, 0, 0); 

	TGTextButton* fTButton1 = new TGTextButton(controlframe,"Add");
	fTButton1->Connect("Clicked()","LiveDataSlicer",this,"ShowLiveDataAdder()");
	TGTextButton* fTButton2 = new TGTextButton(controlframe,"Fornat");
	fTButton2->Connect("Clicked()","LiveDataSlicer",this,"ShowLiveDataFormat()");
	TGTextButton* fTButton3 = new TGTextButton(controlframe,"Manual");
	fTButton3->Connect("Clicked()","LiveDataSlicer",this,"ShowLiveDataAdjust()");
	
	
	fBgroup1 = new TGButtonGroup(controlframe,"Isotope/Isotone/Isobar",kChildFrame);
		TGRadioButton* fRButton1 = new TGRadioButton(fBgroup1," Z ");
		fRButton1->SetState(kButtonDown);
		fRButton1 = new TGRadioButton(fBgroup1," N ");
		fRButton1 = new TGRadioButton(fBgroup1," A ");
	fBgroup1->Show();
	
	fCheck0 = new TGCheckButton(controlframe,"Magic");
	fCheck0->Connect("Clicked()", "LiveDataSlicer", this, "ReDrawMagic()");
	
	TGTextButton* fTButton4 = new TGTextButton(controlframe,"Clear");
	fTButton4->Connect("Clicked()","nuclear_data_ob",this,"Clear()");
	TGTextButton* fTButton5 = new TGTextButton(controlframe,"Save");
	fTButton5->Connect("Clicked()","nuclear_data_ob",0,"saveall_data_live()");
	
	TGLayoutHints* buttonlay=new TGLayoutHints(kLHintsCenterY, 5,5,5,5);
	AddFrame(fCanvas1,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	AddFrame(controlframe,new TGLayoutHints(kLHintsCenterX, 0, 0, 0, 0));
		controlframe->AddFrame(fTButton1,buttonlay);
		controlframe->AddFrame(fTButton2,buttonlay);
		controlframe->AddFrame(fTButton3,buttonlay);
		controlframe->AddFrame(fBgroup1);
		controlframe->AddFrame(fCheck0,buttonlay);
		controlframe->AddFrame(fTButton4,buttonlay);
		controlframe->AddFrame(fTButton5,buttonlay);

	
	TH2F* backdraw=0;
	if(dataget){
		nuclear_data_ob::add_data_live(dataget,"LiveDataSlicerBack",4);
		backdraw = nuclear_data_ob::hist_data_live(nuclear_data_ob::size_data_live()-1);
	}else{
		backdraw = nuclear_data_ob::lifetime_hist();
	}
	if(backdraw){
		fCanvas1->GetCanvas()->cd();
		backdraw->DrawCopy("col");	
		delete backdraw;
		gROOT->cd();
	}

	nuclear_data_ob::addmagic(fCanvas1->GetCanvas(),1);

	fTip = new TGToolTip(gClient->GetRoot(), fCanvas1, "", 50);
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
}

LiveDataSlicer::~LiveDataSlicer()
{
	if(Controls)delete Controls;
	if(Format)delete Format;
	if(Manual)delete Manual;
	fTip->Hide();
	delete fTip;
	// Clean up
	Cleanup();
}

void LiveDataSlicer::LiveChartClickExec(int Z, int A){
	if(!nuclear_data_ob::general_reader(Z,A))return;
	cout<<endl<<Z<<" "<<A<<endl;
}

void LiveDataSlicer::CanvasMouse(Int_t event, Int_t px, Int_t py, TObject *select){
	if(needmagic)ReDrawMagic();
	if(event == kMouseLeave){fTip->Hide(); return;}

	TPad *Pad = fCanvas1->GetCanvas();
	int Z=Pad->AbsPixeltoY(py);//Get the selected nucleon number
	int N=Pad->AbsPixeltoX(px);	
	
	double y1=Pad->GetUymin(),y2=Pad->GetUymax();
	double x1=Pad->GetUxmin(),x2=Pad->GetUxmax();	
	
	if(!(Z>=y1&&Z<y2&&N>=x1&&N<x2))return;
	
	if(!nuclear_data_ob::general_reader(Z,Z+N))return;
	if(event == kButton1Double){LiveChartClickExec(Z,N+Z);return;}// If double click on a nucleus 	
	if(event!=51)return;//51=change position	
	
	int oldID = Pad->GetUniqueID();//Get the stored "ID"
	int newID = Z+N;
	
	if(oldID!=newID){
	//No point doing stuff for pixel change if no nucleon change
	//See if the stored pixel is different, meaning pointer has changed sufficiently to be on next nucleon
		Pad->SetUniqueID(newID);//Uses the canvas "ID" as a way of passing the selected line/pixel	
		Pad->cd();	

		//Delete old line draw new one
		Pad->GetListOfPrimitives()->Remove(markline);
		
		int type=fBgroup1->GetButton(1)->GetState()+fBgroup1->GetButton(2)->GetState()*2+fBgroup1->GetButton(3)->GetState()*3;
		
		//Draw new line
		TLine ll;
		ll.SetLineWidth(2);
		double l,u;
		if(type==1){
			markline=ll.DrawLine(x1,Z+0.5,x2,Z+0.5);
			l=x1;u=x2;
		}else if(type==2){
			markline=ll.DrawLine(N+0.5,y1,N+0.5,y2);
			l=y1;u=y2;
		}else{
			if(y2>Z+N-x1)y2=Z+N-x1;
			if(y2<Z+N)x1=Z+N-y2;
			if(x2>Z+N-y1)x2=Z+N-y1;
			if(x2<Z+N)y1=Z+N-x2;
			markline=ll.DrawLine(x1,y2,x2,y1);
			l=y1;u=y2;
		}
		
		Pad->Update();//Update the lines	
		
// 		Update the title
		stringstream SS;
		SS<<(Z+N)<<nuclear_data_ob::get_symb(Z);
		SetWindowName(SS.str().c_str());
		
		//Update the tooltip
		fTip->Hide();
		fTip->SetText(SS.str().c_str());
		fTip->SetPosition(px-5,py-5);
		fTip->Reset();
	
		gROOT->cd();

		DataWindow = (TCanvas*)gROOT->GetListOfCanvases()->FindObject("Nucleon_Number_Data");
		if(!DataWindow){
			DataWindow= new TCanvas("Nucleon_Number_Data","Nucleon_Number_Data",710,10,700,500);
			DataWindow->SetBottomMargin(0.18);
			DataWindow->SetTopMargin(0.08);
			DataWindow->SetRightMargin(0.08);
			DataWindow->SetLeftMargin(0.12);
					
		}
			
		//Tells the global static class to draw it magic graph
		nuclear_data_ob::LiveDynamicExec(DataWindow,Z,N+Z,type,l,u);
	}
	return;
}	


void LiveDataSlicer::AskDrawMagic(){
	fCanvas1->GetCanvas()->GetListOfPrimitives()->Remove(markline);markline=0;
	needmagic=true;
}

void LiveDataSlicer::ReDrawMagic(){//Remove any previous text labels and the lines
	needmagic=false;
	TPad *Pad = fCanvas1->GetCanvas();
	TObject *obj;TIter next(Pad->GetListOfPrimitives());
	while ((obj = next())){
	if(obj->InheritsFrom("TText")||obj->InheritsFrom("TLine"))
		Pad->GetListOfPrimitives()->Remove(obj);
	}
	if(fCheck0->GetState())nuclear_data_ob::addmagic(Pad,1);
	Pad->Update();//Update the lines	
	return;
}	

void LiveDataSlicer::ShowLiveDataAdder(){//Open the adder window
	if(!Controls){
		Controls=new LiveDataAdder;
		Controls->Connect("Destroyed()", "LiveDataSlicer", this,"DataAdderClosed()");
	}
	Controls->RaiseWindow();
}

void LiveDataSlicer::ShowLiveDataFormat(){//Open the adder window
	if(!Format){
		Format=new LiveDataGUIStyleControl;
		Format->Connect("Destroyed()", "LiveDataSlicer", this,"DataFormatClosed()");
	}
	Format->RaiseWindow();
}

void LiveDataSlicer::ShowLiveDataAdjust(){//Open the adder window
	if(!Manual){
		Manual=new LiveDataAdjuster;
		Manual->Connect("Destroyed()", "LiveDataSlicer", this,"DataAdjustClosed()");
	}
	Manual->RaiseWindow();
}



	////////////////////////////////////////////////////////////////
	///////////     Live Data Slicer Add Controls        ///////////
	///////////////////////////////////////////////////////////////


LiveDataAdder::LiveDataAdder() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame){
	NDS.cColour=1;
	SetCleanup(kDeepCleanup);	
	SetWindowName("LiveDataAdder");

	TGHorizontalFrame* nucleusselect = new TGHorizontalFrame(this, 0, 0, 0); 

	fBgroupZodd = new TGButtonGroup(nucleusselect,"Z",kVerticalFrame);
		TGRadioButton* fRButton1 = new TGRadioButton(fBgroupZodd,"All");
		fRButton1->SetState(kButtonDown);
		fRButton1 = new TGRadioButton(fBgroupZodd,"Even");
		fRButton1 = new TGRadioButton(fBgroupZodd,"Odd");
	fBgroupZodd->Show();
	
	fBgroupNodd = new TGButtonGroup(nucleusselect,"N",kVerticalFrame);
		fRButton1 = new TGRadioButton(fBgroupNodd,"All");
		fRButton1->SetState(kButtonDown);
		fRButton1 = new TGRadioButton(fBgroupNodd,"Even");
		fRButton1 = new TGRadioButton(fBgroupNodd,"Odd");
	fBgroupNodd->Show();
	
	TGVerticalFrame* nucleusadd = new TGVerticalFrame(nucleusselect, 0, 0, 0); 
	NuclesuProp=new TGComboBox(nucleusadd);
		NuclesuProp->AddEntry("Lifetime (s)",1);
		NuclesuProp->AddEntry("Lifetime w/errors (ps)",2);
		NuclesuProp->AddEntry("Sp",3);
		NuclesuProp->AddEntry("Sn",4);
		NuclesuProp->AddEntry("S2p",5);
		NuclesuProp->AddEntry("S2n",6);
		NuclesuProp->AddEntry("nn",7);
		NuclesuProp->AddEntry("pp",8);
		NuclesuProp->AddEntry("np",9);
		NuclesuProp->AddEntry("BE/A",10);
		NuclesuProp->Resize(150,20);
		NuclesuProp->Select(1);

	TGTextButton* fTButton3 = new TGTextButton(nucleusadd,"Add Nucleus Prop.");
		fTButton3->Connect("Clicked()","LiveDataAdder",this,"NucPropAdd()");	

	TGLabel *TitleA = new TGLabel(this," Level/Parent");
	LParent= new LiveDataAdderLevelSelect(this);
	LParent->Connect("UpdatedClicked()","LiveDataAdder",this,"UpdateSelection()");
	LParent->Connect("AddClicked()","LiveDataAdder",this,"LevelAdd()");
	TGLabel *TitleB = new TGLabel(this," Daughter");
	LDaughter= new LiveDataAdderLevelSelect(this);
	LDaughter->Connect("UpdatedClicked()","LiveDataAdder",this,"UpdateSelection()");
	LDaughter->fTButton0->SetEnabled(0);

	
	TGLabel *TitleC = new TGLabel(this," Format");
	TGHorizontalFrame* styleselect = new TGHorizontalFrame(this, 0, 0, 0); 
	
	col=new TGColorSelect(styleselect);
	col->Connect("ColorSelected(Pixel_t)","LiveDataAdder",this,"UpdateCol(Pixel_t)");
	
	Marker=TGComboBoxMarkerSelect(styleselect);
		
	fBgroupDrawType = new TGButtonGroup(styleselect,1,2);
	fRButton1 = new TGRadioButton(fBgroupDrawType,"Axis");
	fRButton1->SetState(kButtonDown);
	fRButton1 = new TGRadioButton(fBgroupDrawType,"Free");
	fBgroupDrawType->Show();
	
	TGLabel *TitleD = new TGLabel(this," Add");	
	TGHorizontalFrame* addselect = new TGHorizontalFrame(this, 0, 0, 0); 
	
	TGTextButton* fTButton2 = new TGTextButton(addselect,"Transition");
	
	info = new TGLabel(this,"                       ");
	
	TGLayoutHints* littlegap=new TGLayoutHints(kLHintsCenterY, 3,3,3,3);
	
	AddFrame(nucleusselect);
		nucleusselect->AddFrame(fBgroupZodd);
		nucleusselect->AddFrame(fBgroupNodd);
		nucleusselect->AddFrame(nucleusadd);
			nucleusadd->AddFrame(NuclesuProp,littlegap);
			nucleusadd->AddFrame(fTButton3,littlegap);
	AddFrame(TitleA);
	AddFrame(LParent);
	AddFrame(TitleB);
	AddFrame(LDaughter);
	AddFrame(TitleC);
	AddFrame(styleselect,littlegap);
		styleselect->AddFrame(col);
		styleselect->AddFrame(Marker);	
		styleselect->AddFrame(fBgroupDrawType,littlegap);	
		fBgroupDrawType->SetLayoutHints(littlegap,0);
	AddFrame(TitleD);
	AddFrame(addselect);
	addselect->AddFrame(fTButton2);
	AddFrame(info,littlegap);

	MapSubwindows();
	Resize(GetDefaultSize());
	LDaughter->HideFrame(LDaughter->fTButton0);

	MapWindow();
	UpdateSelection();
}


//______________________________________________________________________________
LiveDataAdder::~LiveDataAdder(){
	Cleanup();
}

void LiveDataAdder::UpdateCol(Pixel_t i){
	NDS.cColour=TColor::GetColor(i);
	stringstream ss;
	ss<<" Color "<<NDS.cColour;
	info->SetText(ss.str().c_str());
}

void LiveDataAdder::UpdateSelection(){
	NDS.cDatumType=-1;
	NDS.cDrawType=fBgroupDrawType->GetButton(2)->GetState()+1;
	NDS.cMarker=Marker->GetSelected();
	NDS.cPJ=LParent->LSpin->GetSelected();
	NDS.cPP=LParent->LParity->GetSelected();
	NDS.cPN=LParent->LOrder->GetSelected();
	NDS.cPT=LParent->fCheck0->GetState();
	NDS.cDJ=LDaughter->LSpin->GetSelected();
	NDS.cDP=LDaughter->LParity->GetSelected();
	NDS.cDN=LDaughter->LOrder->GetSelected();
	NDS.cDT=LDaughter->fCheck0->GetState();
	NDS.oddZ=oddZ();
	NDS.oddN=oddN();
}

int LiveDataAdder::oddZ(){
	return fBgroupZodd->GetButton(2)->GetState()+fBgroupZodd->GetButton(3)->GetState()*2;
}

int LiveDataAdder::oddN(){
	return fBgroupNodd->GetButton(2)->GetState()+fBgroupNodd->GetButton(3)->GetState()*2;
}

void LiveDataAdder::NucPropAdd(){
	
	//Update graphical style selection
	UpdateSelection();
	int cType=NDS.cDrawType,cColour=NDS.cColour,cMarker=NDS.cMarker;
	
	//Add a datum set from the hard code nuclear_data_ob list;
	switch(NuclesuProp->GetSelected()){
		case 1: nuclear_data_ob::add_data_live(nuclear_data_ob::get_lifetime,"lifetimes",cType,cColour,cMarker);
			break;
		case 2: NDS.cDatumType=2;nuclear_data_ob::AddENSDFdatum(&NDS);
			break;
		case 3: nuclear_data_ob::add_data_live(nuclear_data_ob::Sp,"S_{p}",cType,cColour,cMarker);
			break;
		case 4: nuclear_data_ob::add_data_live(nuclear_data_ob::Sn,"S_{n}",cType,cColour,cMarker);
			break;
		case 5: nuclear_data_ob::add_data_live(nuclear_data_ob::S2p,"S_{2p}",cType,cColour,cMarker);
			break;
		case 6: nuclear_data_ob::add_data_live(nuclear_data_ob::S2n,"S_{2n}",cType,cColour,cMarker);
			break;
		case 7: nuclear_data_ob::add_data_live(nuclear_data_ob::nn,"nn",cType,cColour,cMarker);
			break;
		case 8: nuclear_data_ob::add_data_live(nuclear_data_ob::pp,"pp",cType,cColour,cMarker);
			break;
		case 9: nuclear_data_ob::add_data_live(nuclear_data_ob::np,"np",cType,cColour,cMarker);
			break;
		case 10: nuclear_data_ob::add_data_live(nuclear_data_ob::BE_A,"BE/A",cType,cColour,cMarker);
			break;
		default: break;
	}
	
	//Adjust for odd even selection
	nuclear_data_ob::data_live_odd_even(nuclear_data_ob::size_data_live()-1,oddZ(),oddN());
}

void LiveDataAdder::LevelAdd(){
	UpdateSelection();
	NDS.cDrawType=0;
	NDS.cDatumType=0;
	nuclear_data_ob::AddENSDFdatum(&NDS);
}

	/////////////////////////////////////////////////////////////////
	///////////     Live Data Level Select toolbar        ///////////
	////////////////////////////////////////////////////////////////

ClassImp(LiveDataAdderLevelSelect);
LiveDataAdderLevelSelect::LiveDataAdderLevelSelect(const TGWindow *p) : TGHorizontalFrame(p){	
	SetCleanup(kDeepCleanup);	

	char tmp[20];
	
	TGLabel *LSpinlabel = new TGLabel(this, " J");
	LSpin=new TGComboBox(this);
		LSpin->AddEntry("ANY",-1);
		for(int i = 0; i <= 20; i++) {
			sprintf(tmp, "%i", i);
			LSpin->AddEntry(tmp, i);
		}
		LSpin->Resize(50,20);
		LSpin->Select(2);
	LSpin->Connect("Selected(Int_t,Int_t)","LiveDataAdderLevelSelect",this,"UpdatedClicked()");
		
	TGLabel *LParitylabel = new TGLabel(this, " +/-");
	LParity=new TGComboBox(this);
		LParity->AddEntry("ANY",0);
		LParity->AddEntry("+",1);
		LParity->AddEntry("-",-1);
		LParity->Resize(50,20);
		LParity->Select(1);
	LParity->Connect("Selected(Int_t,Int_t)","LiveDataAdderLevelSelect",this,"UpdatedClicked()");
		
	TGLabel *LOrderlabel = new TGLabel(this, " N");
	LOrder=new TGComboBox(this);
		for(int i = 0; i < 10; i++) {
			sprintf(tmp, "%i", i+1);
			LOrder->AddEntry(tmp, i+1);
		}
		LOrder->Resize(35,20);
		LOrder->Select(1);
	LOrder->Connect("Selected(Int_t,Int_t)","LiveDataAdderLevelSelect",this,"UpdatedClicked()");
	
	fCheck0 = new TGCheckButton(this,"Inc.Tentative");
	fCheck0->Connect("Clicked()","LiveDataAdderLevelSelect",this,"UpdatedClicked()");
	fCheck0->SetDown();
	
	fTButton0 = new TGTextButton(this,"Add Levels");
	fTButton0->Connect("Clicked()","LiveDataAdderLevelSelect",this,"AddClicked()");
	
	TGLayoutHints* littlegap=new TGLayoutHints(kLHintsCenterY, 3,3,3,3);
	AddFrame(LSpinlabel,littlegap);
	AddFrame(LSpin,littlegap);
	AddFrame(LParitylabel,littlegap);
	AddFrame(LParity,littlegap);
	AddFrame(LOrderlabel,littlegap);
	AddFrame(LOrder,littlegap);
	AddFrame(fCheck0,littlegap);
	AddFrame(fTButton0,littlegap);
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
}

void LiveDataAdderLevelSelect::UpdatedClicked(){
	Emit("UpdatedClicked()");
}

void LiveDataAdderLevelSelect::AddClicked(){
	Emit("AddClicked()");
}



	/////////////////////////////////////////////////////////////////
	///////////     Energy Pad View Scanner        ///////////
	////////////////////////////////////////////////////////////////



unsigned int PadScanData::numbertodisplay=5;

int PadScanData::LoadFile(string s){return nuclear_data_ob::LoadEnergyListFile(s);}
int PadScanData::AddData(string sym,int A,int format,double cut){return nuclear_data_ob::AddEnergyListLee(sym,A,format,cut);}
int PadScanData::AddData(int Z,int A,int format,double cut){return nuclear_data_ob::AddEnergyListLee(Z,A,format,cut);}
int PadScanData::AddElectronData(string sym,int A,int format,double cut){return nuclear_data_ob::AddElectronListLee(sym,A,format,cut);}
int PadScanData::AddElectronData(int Z,int A,int format,double cut){return nuclear_data_ob::AddElectronListLee(Z,A,format,cut);}
void PadScanData::Clear(){nuclear_data_ob::Clear();}



//connect the pad to the update function
int PadScanData::Draw(TVirtualPad* pad){
	gStyle->SetOptStat(0);	
	if(pad){
		pad->cd();
		if(gStyle->GetCanvasPreferGL()){//If openGL enabled draw a translucent box for ease of vision
			TBox background;
			background.SetLineWidth(0);
			background.SetFillColorAlpha(0,0.6);
// 			background.SetFillStyle(4040);
			double ymax=pad->GetUymax();
			double ymin=ymax-2*numbertodisplay*(ymax-pad->GetUymin())*0.05;
			double xmax=pad->GetUxmax();
			double xmin=xmax-(xmax-pad->GetUxmin())*0.4;
			background.DrawBox(xmin,ymin,xmax,ymax);
		}
		pad->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)", "PadScanData", 0,"Update(Int_t,Int_t,Int_t,TObject*)");
		pad->Connect("Selected(TVirtualPad*,TObject*,Int_t)", "PadScanData", 0,"CanvasSelected(TVirtualPad*,TObject*,Int_t)");
		CurrentDraw=pad;
		return 1;
	}
	return 0;
}

int PadScanData::UnDraw(TVirtualPad* pad){
	if(pad){
		//Disconnect draw method if connected
// 		pad->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");//Disconnects all not just desired 1 
		pad->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,"Update(Int_t,Int_t,Int_t,TObject*)");
		pad->Disconnect("Selected(TVirtualPad*,TObject*,Int_t)", 0,"CanvasSelected(TVirtualPad*,TObject*,Int_t)");
		
		//Remove any previous text labels and the box
		TObject *obj;TIter next(pad->GetListOfPrimitives());
		while ((obj = next())){
			if(obj->InheritsFrom("TLatex")||(gStyle->GetCanvasPreferGL()&&obj->InheritsFrom("TBox")))
				pad->GetListOfPrimitives()->Remove(obj);
		}

		// Update the draw
		pad->Modified();
		pad->Update();
		CurrentDraw=0;
		
		return 1;
	}
	return 0;	
}

TVirtualPad* PadScanData::CurrentDraw=0;


void PadScanData::CanvasSelected(TVirtualPad *pad, TObject *obj, Int_t event){
	if(pad&&pad!=CurrentDraw)CurrentDraw=pad;
}

void PadScanData::Update(Int_t event, Int_t px, Int_t py, TObject *selected)
{
	if(!gROOT->GetListOfCanvases()->FindObject(CurrentDraw))return;
	TVirtualPad* pad=gPad;
	CurrentDraw->cd();
	
	if(event!=51)return;//51=change position

	//Get the current pointer position
	double x=CurrentDraw->PadtoX(CurrentDraw->AbsPixeltoX(px));
	double y=CurrentDraw->PadtoY(CurrentDraw->AbsPixeltoY(py));
	
	double y1=CurrentDraw->GetUymin(),y2=CurrentDraw->GetUymax();
	double x1=CurrentDraw->GetUxmin(),x2=CurrentDraw->GetUxmax();
	
	//Must be inside the pad, also the a small offset to allow access to the axis
	if(!(x<x2-(x2-x1)*0.03&&x>x1+(x2-x1)*0.03&&y<y2-(y2-y1)*0.03&&y>y1+(y2-y1)*0.03))return;
	
	double E=x;
		
	//Determine the distance of the levels from X
	vector< double > closeness;
	for(unsigned int i=0;i<nuclear_data_ob::ScanTransEnergy.size();i++)closeness.push_back(abs(E-nuclear_data_ob::ScanTransEnergy[i]));
	vector_ddd_sort<double,string>(closeness,nuclear_data_ob::ScanTransEnergy,nuclear_data_ob::ScanTransString,true);
	
	//Save the data for the closest 5 into some local vectors
	vector< string > transferstrings;
	vector< double > transferenergies;
	for(unsigned int j=0;j<numbertodisplay;j++){
		if(j>=nuclear_data_ob::ScanTransEnergy.size())break;
		transferenergies.push_back(nuclear_data_ob::ScanTransEnergy[j]);
		transferstrings.push_back(nuclear_data_ob::ScanTransString[j]);
	}
	
	//resort them by energy 
	vector_dd_sort<string>(transferenergies,transferstrings,true,true);

	//And store which one is the absolute closest
	unsigned int minindex=0;
	double mindif=E;
	for(unsigned int j=0;j<transferenergies.size();j++){
		if(abs(transferenergies[j]-E)<mindif){
			minindex=j;
			mindif=abs(transferenergies[j]-E);
		}
	}
	
	//Remove any previous text labels
	TObject *obj;TIter next(CurrentDraw->GetListOfPrimitives());
	while ((obj = next())){
		if(obj->InheritsFrom("TLatex"))CurrentDraw->GetListOfPrimitives()->Remove(obj);
	}
		
	//Create a text middle+right justified
	TLatex peaknum;
	peaknum.SetTextAlign(32);
	
	// Scale for the pad
	double ystep=(y2-y1)*0.05;
	double xx=x2-(x2-x1)*0.01;
	
	// Write each of the stored text down the right hand side
	for(unsigned int j=0;j<transferenergies.size();j++){
		//Adjust the offset so the closest energy is stationary independent of position in list
		double yy=y2-ystep*(j+numbertodisplay-minindex);
		
		//Larger font for closer matches
		if(minindex==j)peaknum.SetTextSize(0.04);
		else if(abs((signed)minindex-(signed)j)==1)peaknum.SetTextSize(0.035);
		else peaknum.SetTextSize(0.03);
		
		//Add text
		peaknum.DrawLatex(xx,yy,transferstrings[j].c_str());
	}
		
	// Update the draw
	CurrentDraw->Modified();
	CurrentDraw->Update();
	pad->cd();
}


	/////////////////////////////////////////////////////////////////
	///////////     Entry for changing GUI draw options    ///////////
	////////////////////////////////////////////////////////////////

ClassImp(LiveDataGUIentry);
LiveDataGUIentry::LiveDataGUIentry(const TGWindow *p,unsigned int in) : TGHorizontalFrame(p),index(in){	
	SetCleanup(kDeepCleanup);	
	
	
	col=new TGColorSelect(this);
	
	Tlabel = new TGLabel(this, "");
		
	Type=new TGComboBox(this);
	Type->AddEntry("Level",0);
	Type->AddEntry("Axis",1);
	Type->AddEntry("Free",2);
	Type->AddEntry("Hide",3);
	Type->Resize(120,20);
		
	Marker=TGComboBoxMarkerSelect(this);
	
	TGLayoutHints* littlegap=new TGLayoutHints(kLHintsCenterY, 3,3,3,3);	
	AddFrame(col,littlegap);
	AddFrame(Tlabel,littlegap);
	AddFrame(Type,littlegap);
	AddFrame(Marker,littlegap);
	
	Update();
	
	col->Connect("ColorSelected(Pixel_t)","LiveDataGUIentry",this,"Modified()");
	Type->Connect("Selected(Int_t,Int_t)","LiveDataGUIentry",this,"Modified()");
	Marker->Connect("Selected(Int_t,Int_t)","LiveDataGUIentry",this,"Modified()");
	
	MapSubwindows();
	Resize(GetDefaultSize());
	MapWindow();
}

void LiveDataGUIentry::Update(){
	col->SetColor(TColor::Number2Pixel(nuclear_data_ob::get_colour_data_live(index)),kFALSE);
	Marker->Select(nuclear_data_ob::get_marker_data_live(index),kFALSE);
	Type->Select(nuclear_data_ob::get_type_data_live(index),kFALSE);
	Tlabel->SetText(nuclear_data_ob::get_name_data_live(index).c_str());
}	

void LiveDataGUIentry::Modified(){
	Emit("Modified()");
	nuclear_data_ob::format_data_live(index,Type->GetSelected(),TColor::GetColor(col->GetColor()),Marker->GetSelected());
	Update();
}


	////////////////////////////////////////////////////////////////////
	///////     Manual Adjust Box for single live data points    ///////////
	////////////////////////////////////////////////////////////////////
	
	
	
LiveDataGUIStyleControl::LiveDataGUIStyleControl() : TGMainFrame(gClient->GetRoot(), 100, 100,kVerticalFrame){
	SetCleanup(kDeepCleanup);	
	SetWindowName("LiveDataGUIStyleControl");
	MapWindow();
	Update();
}

void LiveDataGUIStyleControl::Update(){
	for(unsigned int i=0;i<nuclear_data_ob::size_data_live();i++){
		if(Entries.size()<=i){
			Entries.push_back(new LiveDataGUIentry(this,i));
			Entries[i]->Connect("Modified()", "LiveDataGUIStyleControl", this, "Update()");
			this->AddFrame(Entries[i]);
			this->MapSubwindows();
		}else{
			this->ShowFrame(Entries[i]);
		}
	}

	for(unsigned int i=nuclear_data_ob::size_data_live();i<Entries.size();i++){
		this->HideFrame(Entries[i]);
	}
	
	this->Resize(this->GetDefaultSize());
	gClient->NeedRedraw(this);
}


	////////////////////////////////////////////////////////////////////
	///////     Control Box for changing GUI draw options    ///////////
	////////////////////////////////////////////////////////////////////
	
	
	
LiveDataAdjuster::LiveDataAdjuster() : TGMainFrame(gClient->GetRoot(), 100, 100,kHorizontalFrame){
	SetCleanup(kDeepCleanup);	
	SetWindowName("LiveDataAdjuster");

	
	index = new TGNumberEntry(this,0, 2,-1,TGNumberFormat::kNESInteger,TGNumberFormat::kNEANonNegative);
	index->Connect("ValueSet(Long_t))", "LiveDataAdjuster", this, "ChangedIndex()");
	Tlabel = new TGLabel(this,"");
		
	fTeh1 = new TGTextEntry(this,new TGTextBuffer(2));//Create some text entry boxes 
	fTeh1->SetDefaultSize(30,25);
	fTeh1->SetText ("Sn",kFALSE);
	fTeh1->Connect("ReturnPressed()", "LiveDataAdjuster", this,"ChangedSelection()");
	fTeh1->Connect("TabPressed()", "LiveDataAdjuster", this,"ChangedSelection()");
    
    
    TGLayoutHints* expy =new TGLayoutHints(kLHintsExpandY);
	TGVerticalFrame* zbutf = new TGVerticalFrame(this, 0, 0, 0); 
    TGPictureButton* fButtonUp = new TGPictureButton(zbutf, fClient->GetPicture("arrow_up.xpm"), 1);
	fButtonUp->Connect("Clicked()", "LiveDataAdjuster", this, "ChangeZ(int=1)");
    zbutf->AddFrame(fButtonUp,expy);
    TGPictureButton* fButtonDown = new TGPictureButton(zbutf, fClient->GetPicture("arrow_down.xpm"), 2);
    zbutf->AddFrame(fButtonDown, expy);
	fButtonDown->Connect("Clicked()", "LiveDataAdjuster", this, "ChangeZ(int=0)");
     
	
	mass = new TGNumberEntry(this,100, 3,-1,TGNumberFormat::kNESInteger,TGNumberFormat::kNEAPositive);
	mass->Connect("ValueSet(Long_t))", "LiveDataAdjuster", this, "ChangedSelection()");
	
	value = new TGNumberEntry(this,0.0, 5,-1);
	
	TGTextButton* fTButton1 = new TGTextButton(this,"Set");
	fTButton1->Connect("Clicked())", "LiveDataAdjuster", this, "Set()");
	
	this->AddFrame(index);
	this->AddFrame(Tlabel);
	this->AddFrame(fTeh1);
	this->AddFrame(zbutf,expy);
	this->AddFrame(mass);
	this->AddFrame(value);
	this->AddFrame(fTButton1);

	
	MapSubwindows();
	MapWindow();
	ChangedIndex();
}

void LiveDataAdjuster::ChangedIndex(){
	Tlabel->SetText(nuclear_data_ob::get_name_data_live(index->GetIntNumber()).c_str());
	ChangedSelection();
	
}

void LiveDataAdjuster::ChangeZ(int up){
    int Z=nuclear_data_ob::get_Z((string)fTeh1->GetText());
    if(up)Z++;else Z--;
	fTeh1->SetText (nuclear_data_ob::get_symb(Z).c_str(),kFALSE);
    ChangedSelection();
}

void LiveDataAdjuster::ChangedSelection(){
	double v=nuclear_data_ob::get_data_live(index->GetIntNumber(),nuclear_data_ob::get_Z((string)fTeh1->GetText()),mass->GetIntNumber());
	value->SetNumber(v);
	Resize(GetDefaultSize());
	gClient->NeedRedraw(this);
}

void LiveDataAdjuster::Set(){
	double V=nuclear_data_ob::modify_data_live(index->GetIntNumber(),nuclear_data_ob::get_Z((string)fTeh1->GetText()),mass->GetIntNumber(),value->GetNumber());
	
	cout<<endl<<"Setting "<<fTeh1->GetText()<<mass->GetIntNumber()<<" "<<nuclear_data_ob::get_name_data_live(index->GetIntNumber())<<"  ";
	cout<<V<<" -> "<<value->GetNumber()<<endl;
}

/////////////////////////////////////////////////////////////////

TGComboBox* TGComboBoxMarkerSelect(const TGWindow *p){
	
	TGComboBox* Marker=new TGComboBox(p);
		Marker->AddEntry("kDot",1);
		Marker->AddEntry("kPlus",2);
		Marker->AddEntry("kStar",3);
		Marker->AddEntry("kCircle",4);
		Marker->AddEntry("kMultiply",5);
		Marker->AddEntry("kFullDotSmall",6);
		Marker->AddEntry("kFullDotMedium",7);
		Marker->AddEntry("kFullDotLarge",8);
		Marker->AddEntry("kFullCircle",20);
		Marker->AddEntry("kFullSquare",21);
		Marker->AddEntry("kFullTriangleUp",22);
		Marker->AddEntry("kFullTriangleDow",23);
		Marker->AddEntry("kOpenCircle",24);
		Marker->AddEntry("kOpenSquare",25);
		Marker->AddEntry("kOpenTriangleUp",26);
		Marker->AddEntry("kOpenDiamond",27);
		Marker->AddEntry("kOpenCross",28);
		Marker->AddEntry("kFullStar",29);
		Marker->AddEntry("kOpenStar",30);
		Marker->AddEntry("kOpenTriangleDow",32);
		Marker->AddEntry("kFullDiamond",33);
		Marker->AddEntry("kFullCross",34);
		Marker->Resize(120,20);
		Marker->Select(7);
	
	return Marker;
}
