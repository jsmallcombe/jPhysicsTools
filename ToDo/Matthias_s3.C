#include <fstream>
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TSpectrum.h"

void fit_s3()
{
	TH1::SetDefaultSumw2();
	TH2F *h;
	TH1D* hp[70];
	TSpectrum* sp[70];
	TF1* fpeak[70][3];
	TF1* ftot[70];
	Float_t mean0[70][3] = {{0.}};
	Float_t rlow[70][3] = {{0.}};
	Float_t rhigh[70][3] = {{0.}};
	Float_t par[70][12];
	Float_t err[70][12];
	Float_t Sgm[70][3];
	Float_t DltSgm[70][3];
	TH1F* hres[70];
	TF1* fres[70];
	Double_t sigma[70];
	Double_t e0[70];
	const Float_t E_MeV[3]= {5.8048,5.4856,5.1566}; 

	TFile file("/home/iris/mholl/1mm_LLNL_S3.root");
	h = (TH2F*)file.Get("h");
	h->SetDirectory(0);
	char histname[256];
	TCanvas * C0 = new TCanvas("C0","C0",1280,720);
	TCanvas * CS1 = new TCanvas("CS1","CS1",1280,720); CS1->Divide(4,2);
	TCanvas * CS2 = new TCanvas("CS2","CS2",1280,720); CS2->Divide(4,2);
	TCanvas * CS3 = new TCanvas("CS3","CS3",1280,720); CS3->Divide(4,2);
	TCanvas * CS4 = new TCanvas("CS4","CS4",1280,720); CS4->Divide(4,2);
	TCanvas * CS5 = new TCanvas("CS5","CS5",1280,720); CS5->Divide(4,2);
	TCanvas * CS6 = new TCanvas("CS6","CS6",1280,720); CS6->Divide(4,2);
	TCanvas * CS7 = new TCanvas("CS7","CS7",1280,720); CS7->Divide(4,2);
	TCanvas * CR1 = new TCanvas("CR1","CR1",1280,720); CR1->Divide(4,2);
	TCanvas * CR2 = new TCanvas("CR2","CR2",1280,720); CR2->Divide(4,2);
	TCanvas * CR3 = new TCanvas("CR3","CR3",1280,720); CR3->Divide(4,2);
	TCanvas * CR4 = new TCanvas("CR4","CR4",1280,720); CR4->Divide(4,2);
	TCanvas * CR5 = new TCanvas("CR5","CR5",1280,720); CR5->Divide(4,2);
	TCanvas * CR6 = new TCanvas("CR6","CR6",1280,720); CR6->Divide(4,2);
	TCanvas * CR7 = new TCanvas("CR7","CR7",1280,720); CR7->Divide(4,2);
	

	C0->cd();
	h->Draw("colz");
	
	for(Int_t i=1; i<69; i++)
	{
		sprintf(histname,"hp%d",i);
		hp[i-1] = (TH1D*) h->ProjectionY(histname,i,i);
		hp[i-1]->SetDirectory(0);
		if(i<9)	CS1->cd(i);
		else if(i>8&&i<17) CS2->cd(i-8);
		else if(i>16&&i<24) CS3->cd(i-16);
		else if(i>24&&i<32) CS4->cd(i-24);
		else if(i>40&&i<49) CS5->cd(i-40);
		else if(i>50&&i<59) CS6->cd(i-50);
		else if(i>60&&i<69) CS7->cd(i-60);
		else continue;
		hp[i-1]->Draw();
		sp[i-1] = new TSpectrum(3);
		// Int_t peaksno = sp[i-1]->Search(hp[i-1],3,"",0.7);
		sp[i-1]->Search(hp[i-1],3,"",0.7);
		Double_t *peak_pos = sp[i-1]->GetPositionX();
		Float_t sort_pos[3] = {0.};
		for(Int_t is=0; is<3; is++)
		{
			if(peak_pos[is]>sort_pos[0])
			{
				sort_pos[2]=sort_pos[1];
				sort_pos[1]=sort_pos[0];
				sort_pos[0]=peak_pos[is];
			}
			else if(peak_pos[is]>sort_pos[1])
			{
				sort_pos[2]=sort_pos[1];
				sort_pos[1]=peak_pos[is];
			}
			else sort_pos[2]=peak_pos[is];
		}
		Double_t par_buff[12];
		printf("\nChannel %d\n",i);
		for(Int_t ip=0; ip<3; ip++)
		{
			printf("\nPeak %d found at %f\n",ip+1,sort_pos[ip]);
			mean0[i-1][ip] = sort_pos[ip];
			rlow[i-1][ip] = 0.97*sort_pos[ip];
			rhigh[i-1][ip] = 1.03*sort_pos[ip];
			fpeak[i-1][ip] = new TF1(Form("ch%dpk%d",i,ip+1),"[0]*exp(-0.5*pow((x-[1])/([2]+(x-[1])*[3]*(x-[1])),2))",rlow[i-1][ip],rhigh[i-1][ip]);
			//fpeak[i-1][ip]->SetDirectory(0);
			fpeak[i-1][ip]->SetParameter(1,mean0[i-1][ip]);
			//fpeak[i-1][ip]->SetParLimits(1,0.98*mean0[i-1][ip],1.01*mean0[i-1][ip]);
			fpeak[i-1][ip]->SetParameter(2,0.01*mean0[i-1][ip]);
			hp[i-1]->Fit(fpeak[i-1][ip],"R+");
			fpeak[i-1][ip]->GetParameters(&par_buff[ip*4]);
		}
		ftot[i-1] = new TF1(Form("ch%dtot",i),"[0]*exp(-0.5*pow((x-[1])/([2]+(x<[1])*[3]*(x-[1])),2))+[4]*exp(-0.5*pow((x-[5])/([6]+(x<[5])*[7]*(x-[5])),2))+[8]*exp(-0.5*pow((x-[9])/([10]+(x<[9])*[11]*(x-[9])),2))",rlow[i-1][2],rhigh[i-1][0]);
		//ftot[i-1]->SetDirectory(0);
		ftot[i-1]->SetParameters(par_buff);
		ftot[i-1]->SetLineColor(4);
		hp[i-1]->Fit(ftot[i-1],"R+");
		//ftot[i-1]->GetParameters(&par_buff[0]);
		//ftot[i-1]->GetParErrors(&err_buff[0]);
		for(Int_t j=0; j<12; j++)
		{
			par[i-1][j] = ftot[i-1]->GetParameter(j);
			err[i-1][j] = ftot[i-1]->GetParError(j);
		}
		if(i<9)	CR1->cd(i);
		else if(i>8&&i<17) CR2->cd(i-8);
		else if(i>16&&i<24) CR3->cd(i-16);
		else if(i>24&&i<32) CR4->cd(i-24);
		else if(i>40&&i<49) CR5->cd(i-40);
		else if(i>50&&i<59) CR6->cd(i-50);
		else if(i>60&&i<69) CR7->cd(i-60);
		else continue;
		
		hres[i-1] = new TH1F(Form("hres_%d",i),Form("res_ch%d",i),1000,5,6);
		hres[i-1]->SetDirectory(0);
		for(Int_t j=0; j<3; j++)
		{
			Int_t bin = (Int_t)( (E_MeV[j]-5.)*1000.);
			Sgm[i-1][j] = par[i-1][4*j+2]/par[i-1][4*j+1];
			DltSgm[i-1][j] = err[i-1][4*j+2]/par[i-1][4*j+1];
			printf("Channel: %d\t%f\t%d\t%f\t%f\n",i,E_MeV[j],bin,Sgm[i-1][j],DltSgm[i-1][j]);
			hres[i-1]->SetBinContent(bin,Sgm[i-1][j]);
			hres[i-1]->SetBinError(bin,DltSgm[i-1][j]);
		}
		hres[i-1]->Draw();
		fres[i-1] = new TF1(Form("ch%dres",i),"[0]*TMath::Sqrt([1]/x)",5,6);
		fres[i-1]->SetParameter(0,0.004);
		fres[i-1]->SetParameter(1,5.);
		hres[i-1]->Fit(fres[i-1],"R+");
		sigma[i-1]=fres[i-1]->GetParameter(0);
		e0[i-1]=fres[i-1]->GetParameter(1);
	}
	ofstream output;
	output.open("s3_triple_a.out");
	output << "Ch\tsigma_0\t\tE_0\n";
	for(Int_t iout=0; iout<70; iout++)
	{
		if(sigma[iout]>1e-4) output << iout+1 <<"\t" << sigma[iout] << "\t" << e0[iout] << "\n";
	}
	output.close();
}
