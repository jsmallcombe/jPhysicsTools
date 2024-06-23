#include "j_LeeNucleusExtend.h"
#include "j_nuclear_data_ob.h"


// Returns 0 or level index + 1 (+1 so it can be used as an if)
// fJ -1 any J
// fParit 0 any Parity
int cNucleusInh::ENSDF_find_level(int fJ,int fParit,int fOrder,int fTent){
	cNucleusInh* nucleus=this;

	// If just asking for Nth level
	if(fJ<0 && fParit==0 && (unsigned)fOrder<=nucleus->nLevels.size())return abs(fOrder);
	
	int odd=nucleus->GetA()%2;
	
	int JpiN=0;//Counter
	
	for(unsigned int i=0;i<nucleus->nLevels.size();i++){//Iterate over all levels of this nucleus
// 		cout<<" "<<nucleus->nLevels[i][1]<<" ("<<nucleus->nLevels[i][4]<<")"<<flush;	
		
		// Load the confirmed and tentative data
		int lJ=round(nucleus->nLevels[i][1]*(1+odd));
		int lJt=round(nucleus->nLevels[i][3]*(1+odd));
		int lP=round(nucleus->nLevels[i][2]);
		int lPt=round(nucleus->nLevels[i][4]);
		
		//If the J is good
		if((fJ==lJ)||(fJ==lJt && fTent)||(fJ==-1)){

			//Is the parity good or tentative 0
			if(lP==fParit||fParit==0||(fTent && (lPt==fParit || lPt==0))){//count J(?) for both (J+) and (J-) in tentative counts
				//J and Pi "correct" so iterate counter
				JpiN++;
				
				// Is the order good
				if(JpiN>=fOrder)return i+1;
			}
		}	
	}
	return 0;
}


int cNucleusInh::ENSDFLevelN(unsigned int index){
	if(index>nLevels.size())return 0;
	int fJ=nLevels[index-1][3];
	int fParit=nLevels[index-1][4];
	
	int JpiN=1;//Counter
	
	for(unsigned int i=0;i<index-1;i++){//Iterate over all levels of this nucleus		
		// Load the confirmed and tentative data
		int lJt=round(nLevels[i][3]);
		int lPt=round(nLevels[i][4]);
		
		//If the J is good
		if(fJ==lJt){
			if(fParit==0||lPt==fParit||lPt==0){//count J(?) for both (J+) and (J-) in tentative counts
				JpiN++;
			}
		}	
	}

	return JpiN;
}

string cNucleusInh::ENSDFLevelString(unsigned int index){

	if(IsLevel(index)){
		int T=1;
		if(round(nLevels[index-1][1])>=0)T=0;
		int J=round(nLevels[index-1][3]);
		int P=round(nLevels[index-1][4]);
		int N=ENSDFLevelN(index);

		return LevelString(J,P,N,T);
	}
	return " ";
}

bool cNucleusInh::IsTrans(unsigned int i){
	return (i<nTransitions.size());
}

bool cNucleusInh::IsLevel(unsigned int index){
	return ((index-1)<nLevels.size());
}

bool cNucleusInh::GetLevelEnergy(double* datum,unsigned int index){
	if(!IsLevel(index))return 0;

		// Debugging code
		cout<<endl<<GetZ();
		cout<<" "<<GetA();
		cout<<" "<<nLevels[index-1][0];
		cout<<endl<<nLevels[index-1][1];
		cout<<" "<<nLevels[index-1][2];	
		cout<<endl<<nLevels[index-1][3];
		cout<<" "<<nLevels[index-1][4]<<flush;
		// End Debugging code

	datum[0]=GetLevelEnergy(index);
	if(datum[0]==0&&index==1)datum[0]=1E-9;
	return true;
}

double cNucleusInh::GetLevelEnergy(unsigned int index){
	if(IsLevel(index))return nLevels[index-1][0];
	return 0;
}
	
bool cNucleusInh::GetTransEnergy(double* datum,unsigned int i){
	if(!IsTrans(i))return 0;
	datum[0]=GetTransEnergy(i);
	return true;
}

double cNucleusInh::GetTransEnergy(unsigned int i){
	if(IsTrans(i))return GetLevelEnergy(GetTransP(i))-GetLevelEnergy(GetTransD(i));
	return 0;
}

int cNucleusInh::GetTransP(unsigned int i){
	if(IsTrans(i))return nTransitions[i][0]+1;	
	return 0;
}

int cNucleusInh::GetTransD(unsigned int i){
	if(IsTrans(i))return nTransitions[i][1]+1;	
	return 0;
}

bool cNucleusInh::GetLevelLifetime(double *datum,unsigned int index){
	if(!IsLevel(index))return 0;
	datum[0]=nLevels[index-1][5];
	datum[1]=nLevels[index-1][7];//Lee did his errors a stupid way around
	datum[2]=nLevels[index-1][6];
	return true;
}


string cNucleusInh::ENSDFTransitionString(unsigned int i){
	if(IsTrans(i))return ENSDFTransitionString(GetTransP(i),GetTransD(i));
	return "";
}

string cNucleusInh::ENSDFTransitionString(unsigned int index_p,unsigned int index_d){
	stringstream ss;
	ss<< ENSDFLevelString(index_p)<<"#rightarrow"<<ENSDFLevelString(index_d);
	return ss.str();
}

string cNucleusInh::ENSDFNucleusString(){
	stringstream ss;
	ss<<"^{"<<GetA()<<"}"<<nuclear_data_ob::get_symb(GetZ());
	return ss.str();
}


// string cNucleusInh::FormatTransitionText(vector<double> &T,int f,int Z, int A){
// 	stringstream ss;
// 	if(f==0||f==1){//Energy and nucleus
// 		ss<<T[6];
// 		ss<<" ^{"<<A<<"}"<<nuclear_data_ob::get_symb(Z);
// 	}
// 	if(f==1){//Level Spins
// 		if(T[2]>=1)ss<<" "<<T[0]<<"_{"<<T[1]<<"}";else ss<<" ?";
// 		ss<<"^{"<<PM(T[1])<<"}#rightarrow";
// 		if(T[5]>=1)ss<<T[3]<<"_{"<<T[5]<<"}";else ss<<"?";
// 		ss<<"^{"<<PM(T[4])<<"}";
// 	}  
// 	return ss.str();
// }


string cNucleusInh::PM(int pm){
	if(pm==1)return "+";
	if(pm==-1)return "-";
	return "?";		   
}


string cNucleusInh::LevelString(int J,int P,int N,int T){
	stringstream ss;
	if(T)ss<<"(";
	if(J>=0)ss<<J;else ss<<"?";
	ss<<"^{"<<PM(P)<<"}";
	if(P)ss<<"_{"<<N<<"}";
	if(T)ss<<")";
	return ss.str();
}


string NucDatumSpecifier::ParentString(){return cNucleusInh::LevelString(cPJ,cPP,cPN,cPT);}
string NucDatumSpecifier::DaughterString(){return cNucleusInh::LevelString(cDJ,cDP,cDN,cDT);}
int NucDatumSpecifier::GetParentLeveli(cNucleusInh* nucleus){return nucleus->ENSDF_find_level(cPJ,cPP,cPN,cPT);}
int NucDatumSpecifier::GetDaughterLeveli(cNucleusInh* nucleus){return nucleus->ENSDF_find_level(cPJ,cPP,cPN,cPT);}


bool NucDatumSpecifier::GetDatum(double *datum,cNucleusInh* nucleus){
	switch(cDatumType) {
		case 0: return nucleus->GetLevelEnergy(datum,GetParentLeveli(nucleus));break;
		case 1: return nucleus->GetLevelLifetime(datum,1);break;
		case 2: return nucleus->GetLevelLifetime(datum,GetParentLeveli(nucleus));break;
		default: break;
	}
	return false;
}


string NucDatumSpecifier::AdderName(){
	string name="name";
	switch(cDatumType) {
		case 0: name=ParentString();break;
		case 1: name="Lifetime w/errors";break;
		case 2: name=ParentString()+" Lifetime";break;
		default: break;
	}
	return name;
}
