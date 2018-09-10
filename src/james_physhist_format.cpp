#include "james_physhist_format.h"


void AddElectronLabel(double Ey,string Z,bool exact,bool M,string text,TVirtualPad* pad,TH1* hist,TVirtualPad* pairpad){
	bool addtext=text.compare("NO");
		
	pad->cd();gPad->Update();
	if(!hist)hist=hist_capture(pad);
	if(!hist)return;
	
	//Find y
	int z=nuclear_data_ob::get_Z(Z);
	
	double BK=nuclear_data_ob::get_Kbinding(z);
	double BL=nuclear_data_ob::get_Lbinding(z);
	double BM=nuclear_data_ob::get_Mbinding(z);
	
	
	double EK=Ey-BK,EL,EM;
	double yK,yL,yM;
	if(exact)yK=hist->GetBinContent(hist->GetXaxis()->FindBin(EK));
	else yK=FindLocalMax(hist,EK);
	EL=EK+BK-BL;
	EM=EK+BK-BM;
	yL=hist->GetBinContent(hist->GetXaxis()->FindBin(EL));
	yM=hist->GetBinContent(hist->GetXaxis()->FindBin(EM));
	
	double yb=pad->GetUymin();
	double yt=pad->GetUymax();
	
	//Slight y offset
	double y5=0.05*(yt-yb);
	double yKt=yK+y5*1.2,yLt=yL+y5,yMt=yM+y5;
	if(yKt>yt)yKt=yt;
	if(yLt>yt)yLt=yt;
	if(yMt>yt)yMt=yt;
	
	//range of the drawn x-axis
	double xb=pad->GetUxmin();
	double xt=pad->GetUxmax();

	if(!(EK>xb&&EK<xt&&EL>xb&&EL<xt))return;
	if(!(EM>xb&&EM<xt))M=false;
	
	//If L is too far below X change cross bar
	double useraspect=abs(yt-yb)/abs(xt-xb);
	if((((yKt-yLt)/(EL-EK))/useraspect)>3){
		yLt=yKt-(EL-EK)*useraspect*3;
	}

	//Add M if M
	if(M){
		double gL=(yLt-yKt)/(BK-BL);
		double gM=(yMt-yKt)/(BK-BM);
		if(gL>gM)yMt=gL*(BK-BM)+yKt;
		else yLt=gM*(BK-BL)+yKt;
	}
	
	vector<double> x,y;
	x.push_back(EK);y.push_back(yK+y5*0.2);
	x.push_back(EK);y.push_back(yKt);
	x.push_back(EL);y.push_back(yLt);
	x.push_back(EL);y.push_back(yL+y5*0.2);
	
	if(M){
		x.push_back(EL);y.push_back(yLt);
		x.push_back(EM);y.push_back(yMt);
		x.push_back(EM);y.push_back(yM+y5*0.2);
	}
	
	if(pairpad){
		PadNDCtoUser(x,y,pad,true);
		PadNDCtoUser(x,y,pairpad);
	}
	
	
	TPolyLine* lines=new TPolyLine();
	for(unsigned int i=0;i<x.size()&&i<y.size();i++)lines->SetNextPoint(x[i],y[i]);
	lines->SetLineWidth(2);
	lines->Draw();
	 
	
// 	TGraph lines;
// 	for(unsigned int i=0;i<x.size()&&i<y.size();i++)lines.SetPoint(lines.GetN(),x[i],y[i]);
// 	
// 	lines.DrawClone("sameL");

	TLatex* latex=new TLatex();
	latex->SetTextSize(0.045);
	latex->SetTextFont(22);
	latex->SetTextAlign(11);
	
	
	//Slight x offset
	double xo=0.015*(pad->GetUxmax()-pad->GetUxmin());
	
	if(addtext){
		latex->DrawLatex(x[1],y[1]+y5,"K");
		latex->DrawLatex(x[2],y[2]+y5,"L");
		if(M)latex->DrawLatex(x[5]+xo,y[5]+y5*0.3,"M");
	
		double xTt=(x[2]-x[1])*0.5;
		double yTt=(y[2]-y[1])*0.5;
		double XTt=x[1]+xTt-0.2*yTt;
		double YTt=y[1]+yTt+0.2*xTt;
		
		latex->DrawLatex(XTt,YTt,text.c_str());
	}
}

void AddElectronGammaLabels(TCanvas* bisected,double E,string Z,bool exact,string text,bool M){
	AddPeakLabel(E,exact,text,bisected->cd(2));
	AddElectronLabel(E,Z,exact,M,"",bisected->cd(1));
}
void AddElectronGammaLabels(TCanvas* bisected,double UrangeL,double UrangeU,double E,string Z,string text){
	TH1* hist=hist_capture(bisected->cd(2));
	if(!hist)return;
	hist->GetXaxis()->SetRangeUser(UrangeL,UrangeU);
	AddPeakLabel(E,false,text,bisected->cd(2));
	AddElectronLabel(E,Z,false,true,"",bisected->cd(1),0,bisected->cd(2));
}


///////////// Level Scheme and Drawing /////////////////


void JamesLevelScheme::AddLevel(unsigned int band,double Energy,string Label,unsigned int col){
	while(Energies.size()<=band){
			Energies.push_back(std::vector< double >());
			LevelColor.push_back(std::vector< unsigned int >());
			SpinLabels.push_back(std::vector< string >());
	}
	if(MinE<0||MinE>Energy)MinE=Energy;
	if(MaxE<0||MaxE<Energy)MaxE=Energy;
	
	Energies[band].push_back(Energy);
	LevelColor[band].push_back(col);
	SpinLabels[band].push_back(Label);
}
	
	
	
void JamesLevelScheme::CalcVert(double Y0,double YRange){
	VertScale=YRange/(MaxE-MinE);
	VertOff=MinE -Y0/VertScale;
}


void JamesLevelScheme::DrawScheme(double X0,double Y0,double YRange){
	gX0=X0;
	gPad->Update();
	CalcVert(Y0,YRange);
	DrawLevels();
	DrawTransitions();
	DrawExtraLabels();
}

void JamesLevelScheme::DrawLevels(){
	gPad->Update();
	for(unsigned int b=0;b<Energies.size();b++){
		DrawBand(b);
	}
}

void JamesLevelScheme::DrawTransitions(){
	gPad->Update();
	for(unsigned int t=0;t<Transitions.size();t++){
		if((unsigned)Transitions[t][0]<Energies.size()&&(unsigned)Transitions[t][2]<Energies.size()){
			if((unsigned)Transitions[t][1]<Energies[Transitions[t][0]].size()&&(unsigned)Transitions[t][3]<Energies[Transitions[t][2]].size()){
				double E1=Energies[Transitions[t][0]][Transitions[t][1]];
				double E2=Energies[Transitions[t][2]][Transitions[t][3]];
				
				double XT=BandX(Transitions[t][0])+Transitions[t][5]/1000.0;

				DrawVerticalArrowPad(XT,EY(E1),EY(E2),Transitions[t][4]);
				
				if(Transitions[t][0]!=Transitions[t][2]){
					DrawInterBandExtension(Transitions[t][2],Transitions[t][3],Transitions[t][0],Transitions[t][5]/1000.0);
				}
			}
		}
	}
}


void JamesLevelScheme::DrawExtraLabels(){
	for(unsigned int i=0;i<ExtraLabels.size();i++){
		
		double X=BandX(ExtraLabels[i].Band);
		double E=Energies[ExtraLabels[i].Band][ExtraLabels[i].Level];
		double Y=EY(E);

		TLatex latex;
		latex.SetTextSize(TextSize);
		latex.SetTextColor(ExtraLabels[i].Col);
		latex.SetTextFont(22);
		latex.SetTextAlign(11);
		latex.DrawLatexNDC(X+StateWidth*0.5,Y+LabelYOffset,ExtraLabels[i].Text.c_str());
	}
}





void JamesLevelScheme::DrawLevel(unsigned int band,unsigned int level){

	double X=BandX(band);
	double E=Energies[band][level];
	double Y=EY(E);
	
	TLine line;
	line.SetLineWidth(LineWidth);
	line.SetLineColor(LevelColor[band][level]);
	line.DrawLineNDC(X-StateWidth*0.5,Y,X+StateWidth*0.5,Y);

	TLatex latex;
	latex.SetTextSize(TextSize);
	latex.SetTextColor(LevelColor[band][level]);
	latex.SetTextFont(22);
	
	latex.SetTextAlign(11);
	latex.DrawLatexNDC(X-StateWidth*0.5,Y+LabelYOffset,SpinLabels[band][level].c_str());
	
	stringstream elab;
	elab<<E;
	if(KeVLabel)elab<<" keV";
	
	latex.SetTextAlign(31);
	latex.DrawLatexNDC(X+StateWidth*0.5,Y+LabelYOffset,elab.str().c_str());
}

void JamesLevelScheme::DrawVerticalArrowPad(double X1,double Y1,double Y2,unsigned int col){
	double X2=X1;
	gPad->Update();
	PadNDCtoUser(X1,Y1,gPad);
	PadNDCtoUser(X2,Y2,gPad);
	TArrow arrow;
	arrow.SetLineColor(col);
	arrow.SetFillColor(col);
	arrow.SetLineWidth(LineWidth);
	arrow.DrawArrow(X1,Y1,X2,Y2,TextSize*ArrowSize,"|>");
}

void JamesLevelScheme::DrawBand(unsigned int b){
	if(b>=Energies.size())return;
	double X=BandX(b);
	vector< int > ordered=vector_order_gen(Energies[b],true);

	double PrevY=0;
	for(unsigned int i=0;i<Energies[b].size();i++){
		DrawLevel(b,ordered[i]);

		double E=Energies[b][ordered[i]];
		double Y=EY(E);
		if(i>0&&DefaultIntra){
			DrawVerticalArrowPad(X,Y,PrevY,LevelColor[b][ordered[i]]);
		}
		PrevY=Y;
	}
	
}


void JamesLevelScheme::DrawInterBandExtension(unsigned int band1,unsigned int level1,unsigned int band2,double Xoffset){
	if(band1>=Energies.size())return;
	if(level1>=Energies[band1].size())return;
	if(band1==band2)return;
	
	
	TLine line;
	line.SetLineWidth(LineWidth);
	line.SetLineColor(LevelColor[band1][level1]);
	line.SetLineStyle(2);
	
	double X1=BandX(band1)+StateWidth*0.5;
	if(band1>band2)X1-=StateWidth;
	double X2=BandX(band2)+Xoffset;
	double Y=EY(Energies[band1][level1]);
	
	line.DrawLineNDC(X1,Y,X2,Y);
	
}


