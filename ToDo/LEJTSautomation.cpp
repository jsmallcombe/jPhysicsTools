#include "LEJTSautomation.h"


vector<double> FindOrderedPeaks(TH1* fHistIn){
	TH1* fHist=SmoothOffBack(fHistIn);
	
	vector<double> fReturn,fIntegrated;
	TSpectrum fSpectrum(500,1);
	
	//Find peaks
// 	int fN=fSpectrum.Search(fHist,10,"nobackground",0.001);
	int fN=fSpectrum.Search(fHistIn,8,"BackSmoothing9goff",0.001);
	Double_t *fPeaks = fSpectrum.GetPositionX();
	//for(int j=0;j<fN;j++){cout<<endl<<fPeaks[j];}
	
	//get a rough idea of the size of each peak
	for(int j=0;j<fN;j++){
		int sX=fHist->GetXaxis()->FindBin(fPeaks[j]);
		FindLocalMax(fHist,sX,10,10);
		fIntegrated.push_back(0);
		for(int k=-3;k<4;k++){
			fIntegrated[j]+=fHist->GetBinContent(sX+k);
		}
	}
	
	vector< int > fOrder=vector_order_gen(fIntegrated, false);
	for(int j=0;j<fN;j++)fReturn.push_back(fPeaks[fOrder[j]]);

	delete fHist;
	return fReturn;	
}

	
	
vector< FullFitHolder* > FitElectronList(TH1* fHist,vector<double> fPeaks,double fSep,double fLeft,double fRight){
	vector< FullFitHolder* > fReturn;
	TH1* fBack=SmoothOffBack(fHist);
	int fNpeaks =fPeaks.size();
	
	for(int i=0;i<fNpeaks;i++){
		int fPos=fHist->GetXaxis()->FindBin(fPeaks[i]);
		int fLeftS=fLeft/fHist->GetBinWidth(1);
		int fRightS=fRight/fHist->GetBinWidth(1);
		FitPositionOptimisation(fBack,fPos,fLeftS,fRightS);
		FullFitHolder* fHold=FitKLElectronPeak(fHist,fPos,fLeftS,fRightS,fSep);
				
		if(fHold!=0)fReturn.push_back(fHold);	
	}
	delete fBack;
	return fReturn;	
}


vector< FullFitHolder* > FitCheckElectronList(TH1* fHist,vector<double> fPeaks,double fSep,double fLeft,double fRight){
	vector< FullFitHolder* > fReturn;
	vector< FullFitHolder* > fPass=FitElectronList(fHist,fPeaks,fSep,fLeft,fRight);
	int fNpeaks =fPass.size();
	
	for(int i=0;i<fNpeaks;i++){
		DrawKLElectronPeak(fHist,fPass[i],false);
		char yn='n';
		cout<<endl<<"Do you like that? :"<<flush;
		cin>>yn;
		if(yn=='y'||yn=='Y'){
			fReturn.push_back(fPass[i]);
			DrawKLElectronPeak(fHist,fPass[i],true);//this one actually adds it
		}else{
			if(yn=='q'||yn=='Q'){
				while(i<fNpeaks){delete fPass[i];i++;}
			}else{
				delete fPass[i];
			}
		}
	}
	return fReturn;	
}



TGraph AutoCal(vector<double>& fEnergy,vector<double>& fPeak){
	int fNE=fEnergy.size();
	int fNP=fPeak.size();
	
	TRandom2 fRand;
	double fMin=1E9;
	double fGstore=0,fIstore=0;
	TF1 fStraight("straight","[0]*x+[1]",0,100000);
	
	for(int z=0;z<10000;z++){
		double sGrad=fRand.Uniform(0.2,5);
		double sInter=fRand.Uniform(-100,100);
		fStraight.SetParameters(sGrad,sInter);
		double sSum=0;
		for(int j=0;j<fNP;j++){
			if(fPeak[j]>0){
				double sTargE=fStraight.Eval(fPeak[j]);
				double sDist=sTargE;
				for(int k=0;k<fNE;k++){
					if(abs(fEnergy[k]-sTargE)<sDist){
						sDist=abs(fEnergy[k]-sTargE);
					}
				}
				sSum+=(sDist*sDist);
			}
		}	
		
		if(sSum<fMin){
			fMin=sSum;
			fGstore=sGrad;
			fIstore=sInter;
		}
	}
	
	fStraight.SetParameters(fGstore,fIstore);

	TGraph fReturn;
	for(int j=0;j<fNP;j++){
		if(fPeak[j]>0){
			double sTargE=fStraight.Eval(fPeak[j]);
			double sDist=sTargE;
			double sClosest=0;
			for(int k=0;k<fNE;k++){
				if(abs(fEnergy[k]-sTargE)<sDist){
					sDist=abs(fEnergy[k]-sTargE);
					sClosest=fEnergy[k];
				}
			}
			fReturn.SetPoint(fReturn.GetN(),fPeak[j],sClosest);
		}
	}	
	
	fReturn.SetMarkerStyle(20);
	fReturn.SetMarkerSize(0.7);
	return fReturn;
}