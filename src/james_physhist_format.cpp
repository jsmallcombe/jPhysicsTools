#include "james_physhist_format.h"


void AddElectronLabel(double Ey,string Z,bool exact,bool M,string text,TVirtualPad* pad,TH1* hist,TVirtualPad* pairpad){
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
	
	text="K "+text;
	latex->DrawLatex(x[1],y[1]+y5*0.1,text.c_str());
	latex->DrawLatex(x[2],y[2]+y5*0.1,"L");
	if(M)latex->DrawLatex(x[5],y[5]+y5*0.1,"M");
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
