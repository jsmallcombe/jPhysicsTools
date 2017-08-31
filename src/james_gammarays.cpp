//
//
//	James Sperhical harmonics and stuff
// 	30/03/2016
//	james.smallcombe@outlook.com
//
//

#include "james_gammarays.h"


double ComptonProb_dsig_dT(double KeV,double keV0,bool electron){
	if(KeV<=0||keV0<=0||KeV>=keV0)return 0;
	double T,Y;
	if(electron){//If KeV is electron energy
		T=KeV;Y=keV0-KeV;
	}else{//If KeV  gamma energy
		Y=KeV;T=keV0-KeV;
	}
	double eminY=keV0/(1+(keV0/511)*2);
	double emaxT=keV0-eminY;	
	if(T>=emaxT)return 0;
	double costheta=1-(((keV0/Y)-1)/(keV0/511));
	double sinthetwo=sin(acos(costheta)/2.);
	double eps=keV0/511;
	double a=1+pow(costheta,2);
	double b=1+2*eps*pow(sinthetwo,2);
	double c=4*eps*eps*pow(sinthetwo,4);
	double d=a*b;
	double diffcross=(a/pow(b,2))*(1+(c/d));
	double sig_T=diffcross*2*pi/pow(eps-T/511,2);
	if(sig_T>0&&sig_T<1E99)	return sig_T;
	return 0;	
	//Note this formula is nor properly normalised
}

double MyKeVNorm(double keV0){
	double eps=keV0/511;
	double integral=((1+eps)/(eps*eps));
	integral*=(((2+2*eps)/(1+2*eps))-(log(1+2*eps)/eps));
	integral+=(log(1+2*eps)/(2*eps));
	integral-=((1+3*eps)/pow(1+2*eps,2));
	integral*=6421.42;
	return integral;
}

//Response without resolution
Double_t GenGeResponseA(Double_t *x, Double_t *p)
{
	double sum=p[1]+p[2]+p[3]+p[4];
	
	double peak=TMath::Gaus(x[0],p[0],0.001,kTRUE);
	double elecscat=ComptonProb_e(x[0],p[0])/MyKeVNorm(p[0]);
	double gamscat=ComptonProb_Y(x[0],p[0])/MyKeVNorm(p[0]);
	double contium=1./p[0];
	if(x[0]>p[0])contium=0;
	//All above normalised to 1;

	double ret=peak*p[1]/sum;
	ret+=elecscat*p[2]/sum;
	ret+=gamscat*p[3]/sum;
	ret+=contium*p[4]/sum;
	
	return ret;
}


TF1* GenGeResponseA(double keV0,double frakpeak,double fraccomp,double contshap,double cont){
	TF1* GeResponse= new TF1("GeResponse",GenGeResponseA,0,4000,5);
	GeResponse->SetParameters(keV0,frakpeak,fraccomp,contshap,cont);
	GeResponse->SetParName(0,"Energy_0 keV");
	GeResponse->SetParName(1,"Peak Fraction");
	GeResponse->SetParName(2,"Compton Fraction");
	GeResponse->SetParName(3,"Continuum Scatter Fraction");
	GeResponse->SetParName(4,"Continuum Flat Fraction");
	GeResponse->SetNpx(10000);
	return GeResponse;
}

	
TH1* GenGeResponse(double keV0,TH1* hist,int N,double reskeV,double frakpeak,double fraccomp,double contshap,double cont){
	TF1* GeResponse=GenGeResponseA(keV0,frakpeak,fraccomp,contshap,cont);
	TH1* response=hist;
	if(!response)response=new TH1D("GeResponse","GeResponse",8000,0,2000);
	
	double RES=reskeV*sqrt(keV0)/sqrt(500);//define res as res at 500keV
	
	TRandom2 rand;rand.SetSeed();
	for(int i=0;i<N;i++){
		double E=GeResponse->GetRandom();
		
		//Res at peak is normal, everything below photopeak = very messy
		double res=pow(E/keV0,4);if(res>1)res=1;
		res=(3-(res*2))*RES;
		
		E+=rand.Gaus(0,res);
		response->Fill(E);
	}	
	delete GeResponse;
	return response;	
}

void ApplyGeEff(TH1* hist){
	TF1 stefeffer("stefeff",stefeff,10,3000,4);
	stefeffer.SetParameters(-0.2193,-0.03569,-2434,5.802);
	for(int i=1;i<=hist->GetNbinsX();i++)
		hist->SetBinContent(i,hist->GetBinContent(i)*stefeffer.Eval(hist->GetBinCenter(i)));
}