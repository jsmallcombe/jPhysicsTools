#include "james_nuclear_data_ob.h"

////////////////////////////////////////
/////////// Static Members   /////////// 
////////////////////////////////////////

#include "NucDataOb/autohead/data_init.h"
string nuclear_data_ob::elem_sym_list[128]={""};

vector< vector< vector< double > > > nuclear_data_ob::live_data;
vector< vector< vector< double > > > nuclear_data_ob::live_data_upper_error;
vector< vector< vector< double > > > nuclear_data_ob::live_data_lower_error;
vector< string > nuclear_data_ob::live_data_names;
vector< unsigned int > nuclear_data_ob::live_data_color;
vector< unsigned int > nuclear_data_ob::live_data_marker;
vector< unsigned int > nuclear_data_ob::live_data_type;
double nuclear_data_ob::level_width=0.4;

vector< string > nuclear_data_ob::ScanTransString;
vector< double > nuclear_data_ob::ScanTransEnergy;

bool nuclear_data_ob::data_set=false;

unsigned int nuclear_data_ob::livedatapick=0;

TFile* nuclear_data_ob::LeeFile=0;
TTree* nuclear_data_ob::LeeTree=0;


//////////////////////////////////////////////
/////////// Loading and Clearing   /////////// 
//////////////////////////////////////////////

void nuclear_data_ob::set_data(){
	if(!data_set){
		#include "NucDataOb/autohead/data_data.h"
		LeeTree=LeeData();
		data_set=true;
	}
}

void nuclear_data_ob::Clear(){
	live_data.clear();
	live_data_upper_error.clear();
	live_data_lower_error.clear();
	live_data_names.clear();
	live_data_color.clear();
	live_data_marker.clear();
	live_data_type.clear();
	ScanTransString.clear();
	ScanTransEnergy.clear();
	LeeTree=0;
	if(LeeFile)LeeFile->Close();
	LeeFile=0;
}

TTree* nuclear_data_ob::LeeData(){
	if(LeeTree)return LeeTree;
	const char * val = std::getenv("JAMESPHYS");
	if ( val == 0 ) {
		cout<<endl<<"System Enviromental Value JAMESPHYS not set."<<endl;
		return 0;
	}
	string LeeFileName=(string)val+"/NucDataOb/pensExtract.root";
// 	cout<<endl<<"System Enviromental Value JAMESPHYS = "<<path<<endl;
	TFile* LeeFile=new TFile(LeeFileName.c_str(),"READ");
	if(!LeeFile->IsOpen()){
		cout<<endl<<"Data file "<<LeeFileName<<" not found."<<endl;
		LeeFile=0;
		return 0;
	}
	
	LeeFile->GetObject("NS",LeeTree);

	if(!LeeTree){
		cout<<endl<<"Tree NS missing from file."<<endl;
		return 0;
	}

	return LeeTree;
}

short nuclear_data_ob::general_reader(int z,int a){
	set_data();
	int n=a-z;
	if(z>=0&&z<128&&n>=0&&n<256)return 1;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// Non-dynamic Data Functions  //////
	///////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////
	////////    BASIC ACCESS   //////
	////////////////////////////////////

#include "NucDataOb/autohead/function_definitions.h"

TH2F* nuclear_data_ob::lifetime_hist(){
	TH2F *lth  = new TH2F("lifetime_hist","Nuclear Lifetimes",180,0,180,116,0,116);
	lth->SetStats(0);
	for (Int_t n = 0; n < 180; n++) {
		for (Int_t z = 0; z < 116; z++) {
			double t=get_lifetime(z,n+z);
			if(t>1)t=log(t)+1;
			if(t>2)t=log(t)+2-log(2);
			if(t==0)t=-0.2;
			lth->SetBinContent(n+1,z+1,t);
		}
	}
	chart_format(lth);
	return lth;
}	

// For some historic reason the thing I store is mass_excess not mass or binding energy
// For ages I forgot mass excess omc;ides electrons
// Now in mass_table it is the mass excess of the proton NOT hydrogen 1
double nuclear_data_ob::get_mass_excess(int z,int a){
	if(general_reader(z,a)){
		if(a-z>0 && z>0)	return mass_table[z][a-z];
		else	return (mass_table[0][1]*(a-z))+(mass_table[1][0]*z);
	}	
	return 0;
}

double nuclear_data_ob::get_mass_MeV(int z,int a){
	double ex=get_mass_excess(z,a);
	double mass=(a)*jam_phys_amu;
	return mass+ex;
}

double nuclear_data_ob::BE(int z,int a){
	double P=get_mass_excess(z,a);
	if(P&&a>z)return get_mass_excess(1,1)*z+get_mass_excess(0,1)*(a-z)+jam_phys_511*(z)-P;
	return 0;
}

double nuclear_data_ob::get_mass(int z,int a){
	return get_mass_MeV(z,a)/jam_phys_amu;
}

bool nuclear_data_ob::is_mass(int z,int a){
	if(get_mass_excess(z,a)!=0 || (z==6&&a==12))return true;
	return false;	
}
int nuclear_data_ob::get_Z(string sym){
	set_data();
	string copystr=sym;
	copystr[0]=toupper(copystr[0]);
	for(int i=1;(unsigned)i<copystr.length();i++)copystr[i]=tolower(copystr[i]);
 	for(int i=0;i<128;i++)if(copystr==elem_sym_list[i])return i;
	return 0;
}

string nuclear_data_ob::get_symb(int z){
	if(general_reader(z))return elem_sym_list[z];
	return " ";
}

double nuclear_data_ob::get_nom_density(int z){
	set_data();
	double x=0;
	if(general_reader(z))x= density_gcm3[z];
	if(x==0)return 1.0;
	return x;
}

double nuclear_data_ob::Sn(int z,int a){return SepCal(z,a,0,1);}
double nuclear_data_ob::Sp(int z,int a){return SepCal(z,a,1,0);}
double nuclear_data_ob::S2n(int z,int a){return SepCal(z,a,0,2);}
double nuclear_data_ob::S2p(int z,int a){return SepCal(z,a,2,0);}

double nuclear_data_ob::nn(int z,int a){
	if(z%2||a%2)return 0;
	return 0.5*(Sn(z,a)-Sn(z,a+1));
}

double nuclear_data_ob::pp(int z,int a){
	if(z%2||a%2)return 0;
	return 0.5*(Sp(z,a)-Sp(z+1,a+1));
}

double nuclear_data_ob::np(int z,int a){
	if(a%2)return 0;
	if(!z%2)return 0;
	return -0.25*(BE(z+1,a)+BE(z-1,a)+BE(z,a-1)+BE(z,a+1)-4*BE(a,z));//just made this up
}

double nuclear_data_ob::Qalpha(int z,int a){double pd=SepCal(z,a,2,2);if(pd)return BE(2,4)-pd;return 0;}
double nuclear_data_ob::Qbeta_p(int z,int a){return -jam_phys_np_mass-SepCal(z,a,1,-1)-jam_phys_511;}
double nuclear_data_ob::Qbeta_EC(int z,int a){return -jam_phys_np_mass-SepCal(z,a,1,-1)+jam_phys_511;}
double nuclear_data_ob::Qbeta_m(int z,int a){return jam_phys_np_mass-SepCal(z,a,-1,1)-jam_phys_511;}

double nuclear_data_ob::SepCal(int z,int a,int p,int n){
	double P=BE(z,a);
	double D=BE(z-p,a-(p+n));
	if(P&&D)return P-D;
	return 0;
}

double nuclear_data_ob::BE_A(int z,int a){
	double B=BE(z,a);
	if(B&&a)return B/a;
	return 0;
}

	////////////////////////////////////
	////////    Formated outpus   //////
	////////////////////////////////////
	
string nuclear_data_ob::channelname(int Z,int A){
    string retstr="";
	if(A>1){
		stringstream ss;
		ss << A;
		retstr = ss.str();
	}
	if(Z==0&&A>0){retstr+="n";return retstr;}
	if(Z==A&&A>0){retstr+="p";return retstr;}
	if(Z==1&&A==2){retstr="d";return retstr;}
	if(Z==1&&A==3){retstr="t";return retstr;}
	if(Z==0&&A==0){retstr="Y";return retstr;}
	if(Z==1&&A==0){retstr="e+";return retstr;}
	if(Z==-1&&A==0){retstr="e-";return retstr;}
	if(Z==2&&A==4){retstr="a";return retstr;}
	retstr+=get_symb(Z);return retstr;
}


TGraph* nuclear_data_ob::get_isobar_excess(int A){
	TGraph* graph = new TGraph();
	
	for(int Z=0;Z<200;Z++){
		if(is_mass(Z,A))graph->SetPoint(graph->GetN(),Z,get_mass_excess(Z,A));
	}
	
	return graph;
}

TGraph* nuclear_data_ob::get_znratio_excess(int z,int a){
	double ratio=(double)(a-z)/(double)(a);
	TGraph* graph = new TGraph();
	
	for(int A=0;A<200;A++){
		int N=ratio*A;
		int Z=A-N;
		if(is_mass(Z,A))graph->SetPoint(graph->GetN(),A,get_mass_excess(Z,A));
	}
	
	return graph;
}


//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// OTHER FUNCTIONS  //////
	///////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////////

void nuclear_data_ob::chart_format(TH2* h){if(!h)return;
	hformat(h);
	axislab(h,"N","Z","Nuclear Lifetimes");
	h->GetXaxis()->SetNdivisions(1014);
	h->GetYaxis()->SetNdivisions(1014); 
}

//box bottom left, box top right, point 1, point 2. Is any part of the perpendicular line in the box
bool badcodingboxcheck(double& x1,double& y1,double& x2,double& y2,double& a1,double& b1,double& a2,double& b2){
	
	bool ret =false;
	if(x1<a1&&a1<x2&&y1<b1&&b1<y2) ret=true;
	if(x1<a2&&a2<x2&&y1<b2&&b2<y2) ret=true;
	if(x1>a1&&a2>x2&&y1<b2&&b2<y2) ret=true;
	if(x1>a2&&a1>x2&&y1<b2&&b2<y2) ret=true;
	if(y1>b1&&b2>y2&&x1<a2&&a2<x2) ret=true;
	if(y1>b2&&b1>y2&&x1<a2&&a2<x2) ret=true;
	
	if(x1>a1)a1=x1;
	if(x1>a2)a2=x1;
	if(x2<a1)a1=x2;
	if(x2<a2)a2=x2;
	if(y1>b1)b1=y1;
	if(y1>b2)b2=y1;
	if(y2<b1)b1=y2;
	if(y2<b2)b2=y2;	
	
	return ret;
}



void nuclear_data_ob::addmagic(TVirtualPad* pad,bool twolines){
	pad->cd();
	pad->Update();
	double x1,y1,x2,y2;
	pad->GetRangeAxis(x1,y1,x2,y2);	
	
	vector< double > magic{8,20,50,82,126,184};
	vector< double > hori{0,30,14,60,42,140,74,160, 0, 0, 0, 0};//y
	vector< double > vert{0,14, 5,26,15, 58,25, 90,40,90,60,90};//x
		
	int lines=twolines;
	TLine line;
	line.SetLineWidth(2-lines);
	
	TText tex;
	tex.SetTextAlign(22);
	tex.SetTextFont(22);
	tex.SetTextSize(0.04);
	double ytoff=(y2-y1)*(3./117.);
	double xtoff=(x2-x1)*(5./240.);

	
	
	for(unsigned int i=0;i<magic.size();i++){
		magic[i]+=0.5;
		stringstream M;
		M<<(int)magic[i];
		
		double m=magic[i];
		double y=vert[i*2]-ytoff-1;
		if(badcodingboxcheck(x1,y1,x2,y2,m,y,m,y))
			tex.DrawText(m,y+1,M.str().c_str());
		y=vert[i*2+1]+ytoff+1;
		if(badcodingboxcheck(x1,y1,x2,y2,m,y,m,y))
			tex.DrawText(m,y-1,M.str().c_str());
		
		
		m=magic[i];
		double x=hori[i*2]-xtoff-1;
		if(badcodingboxcheck(x1,y1,x2,y2,x,m,x,m))
			tex.DrawText(x+1,m,M.str().c_str());
		x=hori[i*2+1]+xtoff+1;
		if(badcodingboxcheck(x1,y1,x2,y2,x,m,x,m))
			tex.DrawText(x-1,m,M.str().c_str());
	}
	
	for(int l=0;l<=lines;l++){
		for(unsigned int i=0;i<magic.size();i++){
			double m=magic[i]-0.5*lines+l;
			if(badcodingboxcheck(x1,y1,x2,y2,m,vert[i*2],m,vert[i*2+1]))
			line.DrawLine(m,vert[i*2],m,vert[i*2+1]);
			m=magic[i]-0.5*lines+l;
			if(badcodingboxcheck(x1,y1,x2,y2,hori[i*2],m,hori[i*2+1],m))
			line.DrawLine(hori[i*2],m,hori[i*2+1],m);
		}
		
	}
}

void nuclear_data_ob::addmagic(TH2* hist){
	double minfill=1E-9;

	
	vector< int > magic{8,20,50,82,126,184};
	for(unsigned int i=0;i<magic.size();i++){
		int mag=magic[i];
		for(int j=1;j<=hist->GetNbinsX();j++){
			if(hist->GetBinContent(j,mag+1)==0){
				hist->SetBinContent(j,mag+1,minfill);
			}
		}
		for(int j=1;j<=hist->GetNbinsY();j++){
			if(hist->GetBinContent(mag+1,j)==0){
				hist->SetBinContent(mag+1,j,minfill);
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// Dynamic Data Functions  //////
	///////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////
	//////// Basic Add Data Functions  //////
	/////////////////////////////////////////
    
    
void nuclear_data_ob::add_data_live(string filename,unsigned int type,unsigned int col,unsigned int mark){

    if(filename.find(".txt")==filename.size()-4){
        ifstream infile;
        infile.open((filename).c_str());
        if(infile.is_open()){
            string name=filename.substr(0,filename.find(".txt"));
            while(name.find("/")<name.size())name=name.substr(name.find("/")+1);
	    
	    push_data_live(name,type,col,mark);

            int z,n;
            double v;
            
            while(infile>>z>>n>>v){
                if(general_reader(z,z+n))
                    live_data[live_data.size()-1][z][n]=v;                
            }
        }
    }
}

void nuclear_data_ob::add_data_live(double (*dataget)(int,int),string name,unsigned int type,unsigned int col,unsigned int mark){
	push_data_live(name,type,col,mark);

	for(int xx=0;xx<128;xx++){
		for(int yy=0;yy<256;yy++){
			live_data[live_data.size()-1][xx][yy]=dataget(xx,yy+xx);                
		}	
	}
}

void nuclear_data_ob::add_data_live(vector< vector < double > > &data,string name,unsigned int type,unsigned int col,unsigned int mark){
	push_data_live(name,type,col,mark);
	while(data.size()<128)data.push_back(vector<double>(256,0));
	for(int xx=0;xx<128;xx++)while(data[xx].size()<256)data[xx].push_back(0);
	live_data[live_data.size()-1]=data;
}

void nuclear_data_ob::push_data_live(string name,unsigned int type,unsigned int col,unsigned int mark){
	live_data.push_back(vector<vector<double>>(128,vector<double>(256,0))); 
	live_data_upper_error.push_back(vector<vector<double>>(128,vector<double>(256,0)));  
	live_data_lower_error.push_back(vector<vector<double>>(128,vector<double>(256,0)));  
	live_data_names.push_back(name);
	live_data_type.push_back(type);
	live_data_color.push_back(col);
	live_data_marker.push_back(mark);	
}


double nuclear_data_ob::modify_data_live(unsigned int i,int z,int a,double v){
	if(i<live_data.size()&&general_reader(z,a)){
		double V=live_data[i][z][a-z];
		live_data[i][z][a-z]=v;
		return V;
	}
	return 0;
}

	/////////////////////////////////////////
	//////// Data Save/Load Function  //////
	/////////////////////////////////////////
	
void nuclear_data_ob::saveall_data_live(string filename){

        ofstream outfile(filename);
        if(!outfile.is_open())return;
	
	int I=live_data.size();
	outfile<<I<<endl;
	
	for(int i=0;i<I;i++){
		outfile<<live_data_names[i]<<endl;
		outfile<<live_data_type[i]<<" ";
		outfile<<live_data_color[i]<<" ";
		outfile<<live_data_marker[i]<<endl;
	}
	
	for(int j=0;j<128;j++){	
	for(int k=0;k<256;k++){	
	for(int i=0;i<I;i++){
		double v=live_data[i][j][k];
		if(v){
			outfile<<i<<" ";
			outfile<<j<<" ";
			outfile<<k<<" ";
			outfile<<live_data[i][j][k]<<" ";
			outfile<<live_data_upper_error[i][j][k]<<" ";
			outfile<<live_data_lower_error[i][j][k]<<" ";
		}
	}}}
	
	outfile.close();
}
	
void nuclear_data_ob::readall_data_live(string filename){
	Clear();
	
        ifstream infile(filename);
        if(!infile.is_open())return;
	
	unsigned int I;
	infile>>I;
	if(I>100)return;
	string d;
	std::getline(infile,d);//just here to clear the last of that line could also have used .ignore('/n')
	
	for(unsigned int i=0;i<I;i++){
		string name,data;
		std::getline(infile,name);
		std::getline(infile,data);
		stringstream ss;
		ss<<data;
		int type,colour,marker;
		ss>>type>>colour>>marker;
	
		push_data_live(name,type,colour,marker);
	}
	
	print_data_live();
	
	unsigned int i,j,k;
	double y,yu,yd;
	
	while(infile>>i>>j>>k>>y>>yu>>yd){
		if(i<I&&general_reader(j,j+k)){
			live_data[i][j][k]=y;
			live_data_upper_error[i][j][k]=yu;
			live_data_lower_error[i][j][k]=yd;
		}		   
	}	
}
		
	
	/////////////////////////////////////////
	//////// Data Access Functions  //////
	/////////////////////////////////////////


double nuclear_data_ob::get_data_live(unsigned int i,int z, int a){	
    if(general_reader(z,a)&&i<live_data.size())
        return live_data[i][z][a-z];
    return 0;
}

double nuclear_data_ob::data_live(int z, int a){	
	return get_data_live(livedatapick,z,a);
}
void nuclear_data_ob::set_data_live(unsigned int i){	
	livedatapick=i;
}


void nuclear_data_ob::get_data_live_errors(unsigned int i,int z, int a,double& yu,double &yl){
	yu=0;yl=0;
	
	if(general_reader(z,a)&&i<live_data.size()){
		yu=live_data_upper_error[i][z][a-z];
		yl=live_data_lower_error[i][z][a-z];
	}	
}

string nuclear_data_ob::get_name_data_live(unsigned int i){
	if(i<live_data_names.size()){
		return live_data_names[i];	
	}
	return "";
}

unsigned int nuclear_data_ob::get_type_data_live(unsigned int i){
	if(i<live_data_type.size()){
		return live_data_type[i];	
	}
	return 0;
}

unsigned int nuclear_data_ob::get_colour_data_live(unsigned int i){
	if(i<live_data_color.size()){
		return live_data_color[i];	
	}
	return 0;
}

unsigned int nuclear_data_ob::get_marker_data_live(unsigned int i){
	if(i<live_data_marker.size()){
		return live_data_marker[i];	
	}
	return 0;
}

void nuclear_data_ob::print_data_live(){
	cout<<endl<<"                    Type     Colour Marker";
	for(unsigned int i=0;i<live_data.size();i++){
		cout<<endl<<std::left<<setw(20)<<live_data_names[i];
		string out="Hidden";
		if(live_data_type[i]==0)out="Level";
		if(live_data_type[i]==1)out="Axis Data";
		if(live_data_type[i]==2)out="Data";
		
		cout<<setw(11)<<out;
		cout<<setw(6)<<live_data_color[i]<<live_data_marker[i];
	}
	cout<<endl;
}

TH2F* nuclear_data_ob::hist_data_live(unsigned int i){
	
	if(i<live_data.size()){
		TH2F *ret  = new TH2F(live_data_names[i].c_str(),live_data_names[i].c_str(),180,0,180,117,0,117);
		for (Int_t n = 0; n < 180; n++) {
			for (Int_t z = 0; z < 117; z++) {
				ret->SetBinContent(n+1,z+1,get_data_live(i,z,n+z));
			}
		}
		chart_format(ret);
		return ret;
	}
	
	return new TH2F();
}

	/////////////////////////////////////////////
	//////// Data Modify/format Functions  //////
	/////////////////////////////////////////////

void nuclear_data_ob::format_data_live(unsigned int i,unsigned int type,unsigned int col,unsigned int mark){
	if(i<live_data.size()){
// 		live_data_names.push_back(name);
		live_data_type[i]=type;
		live_data_color[i]=col;
		live_data_marker[i]=mark;	
	}
}

void nuclear_data_ob::data_live_odd_even(unsigned int i,int oddZ,int oddN){
	if(i<live_data.size()&&(oddZ||oddN)){
		for(unsigned int z=0;z<live_data[i].size();z++){
			for(unsigned int n=0;n<live_data[i][z].size();n++){				
				if(!odd_even(z,n,oddZ,oddN))live_data[i][z][n]=0;
			}
		}
	}
	return;
}
	

//////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// LiveDataSlicer Display  //////
	///////////////////////////////////////////	
//////////////////////////////////////////////////////////////////////////////////////

void nuclear_data_ob::LiveDynamicExec(TVirtualPad* pad,Int_t Z, Int_t N, Int_t NZ, TObject *select){
	LiveDynamicExec(pad,Z,Z+N,NZ);
}

void nuclear_data_ob::LiveDynamicExec(TVirtualPad* pad,int Z,int A,int NZAbool,double limitL,double limitU){
	int N=A-Z;
	
	TVirtualPad *padsav = gPad;//Save the current pad
	
	pad->cd();
	gPad->Update(); // important !!! without this certain draws get confused
	pad->GetCanvas()->RaiseWindow();

		
	// Load all the data for the selected from the matrix
	int sel_min=384;
	int sel_max=0;
	TGraph all_energy_levels;
	TGraph all_axis2_values;
	vector< TGraphAsymmErrors > individuals;
	for(unsigned int i=0;i<live_data_type.size();i++){
		TGraphAsymmErrors current;
		for(int xx=0;xx<128*NZAbool;xx++){
			if(xx>=limitL&&xx<=limitU){
				double point=0;
				
				int lz=xx,la=A;
				if(NZAbool==1){lz=Z;la=xx+Z;}
				else if(NZAbool==2){la=N+xx;}
				point=get_data_live(i,lz,la);
				
				if(point!=0){
					if(live_data_type[i]==0)all_energy_levels.SetPoint(all_energy_levels.GetN(),xx,point);
					if(live_data_type[i]==1)all_axis2_values.SetPoint(all_axis2_values.GetN(),xx,point);
					current.SetPoint(current.GetN(),xx,point);
				
					//Newly switched to TGraphAsymmErrors////
					double eyu,eyl;
					get_data_live_errors(i,lz,la,eyu,eyl);
					if(eyu)current.SetPointEYhigh(current.GetN()-1,eyu);
					if(eyl)current.SetPointEYlow(current.GetN()-1,eyl);
					//////////////////////////////////////////
					
					if(live_data_type[i]<3){
						if(xx>sel_max)sel_max=xx;
						if(xx<sel_min)sel_min=xx;
					}
				}
			}
		}
		current.SetMarkerColor(live_data_color[i]);
		current.SetMarkerStyle(live_data_marker[i]);
// 			current.SetMarkerSize(10);
		individuals.push_back(current);
	}
	
	// Find which is going to be the base data set
	
	TGraph winner;
	int mastertype=-1;		
	if(all_energy_levels.GetN()>0){
		winner=all_energy_levels;
		mastertype=0;
	}else if(all_axis2_values.GetN()>0){
		winner=all_axis2_values;
		mastertype=1;
	}else{
		for(unsigned int i=0;i<individuals.size();i++){
			if(individuals[i].GetN()>0){
				winner=individuals[i];
				mastertype=2;
				break;
			}
		}
	}
	
	bool dualyaxis=(all_axis2_values.GetN()>0&&all_energy_levels.GetN()>0);
	
	if(mastertype>=0){//If there was no data abort
		
		//A little precaution in case one of the minor datum are much wider than the axis control ones
		winner.SetPoint(winner.GetN(),sel_max,0);
		winner.SetPoint(winner.GetN(),sel_min,0);
		winner.Draw();
		TH1F* graph_hist=winner.GetHistogram();
		
		
		int RRR= round(graph_hist->GetXaxis()->GetXmax());
		int LLL= round(graph_hist->GetXaxis()->GetXmin());
		if((int)LLL%2)LLL-=1;
		if((int)(RRR-LLL)%2)RRR+=1;
		int ndiv=(RRR-LLL);
		TH1F frame_hist("frame_hist","frame_hist",ndiv,LLL,RRR);
		

		double axr=RRR;
		double axl=LLL;
		double axt=graph_hist->GetYaxis()->GetXmax();
		double axb=graph_hist->GetYaxis()->GetXmin();
		frame_hist.SetMaximum(axt);
		
		cout<<endl<<" "<<ndiv<<flush;
		if(ndiv==(RRR-LLL)&&ndiv>4){ndiv/=2;}
		cout<<endl<<" "<<ndiv<<flush;
		while(ndiv>10&&!(ndiv%2)){ndiv/=2;}
		cout<<endl<<" "<<ndiv<<flush;
		
		ndiv+=100*((RRR-LLL)/ndiv);
		
		frame_hist.GetXaxis()->SetNdivisions(ndiv,kFALSE);

		//Turn labels off if no master (odd input but may be desired)
		if(mastertype==2)frame_hist.GetYaxis()->SetLabelSize(0);
		
		//Add Axis label if level energy
		if(mastertype==0){
			frame_hist.GetYaxis()->SetTitle("Excitation Energy [keV]");
			frame_hist.GetYaxis()->SetTitleSize(0.045);
			frame_hist.GetYaxis()->CenterTitle();
			frame_hist.GetYaxis()->SetTitleOffset(1.2);
		}

		frame_hist.GetXaxis()->SetTitle("Neutron Number [N] / Mass Number [A]");
		if(NZAbool==2)frame_hist.GetXaxis()->SetTitle("Proton Number [Z] / Mass Number [A]");
		if(NZAbool==3)frame_hist.GetXaxis()->SetTitle("Proton Number [Z] / Neutron Number [N]");
		frame_hist.GetXaxis()->SetTitleSize(0.045);
		frame_hist.GetXaxis()->CenterTitle();
		frame_hist.GetXaxis()->SetTitleOffset(1.8);
		
		//Format the output frame histogram
		stringstream ss;
		if(NZAbool==1)ss<<get_symb(Z)<<" Z = "<<Z;
		else if(NZAbool==2)ss<<" N = "<<N;
		else ss<<" A = "<<A;
		frame_hist.SetTitle(ss.str().c_str());
		if(mastertype==0){frame_hist.SetMinimum(0);axb=0;}
		frame_hist.SetLineColor(0);
		frame_hist.SetStats(kFALSE);		
		frame_hist.DrawCopy();
		
		//Save some properties of the primary axis
		int ndx=ndiv;
		int ndy=frame_hist.GetYaxis()->GetNdivisions();
		
	
		int sel=Z;
		if(NZAbool==2){sel=N;}
		
		//Draw the mass/N axis
		TGaxis axis;
		axis.SetLabelSize(0.03);
		if(NZAbool==3)axis.DrawAxis(axr,axb-(axt-axb)*.08,axl,axb-(axt-axb)*.08,A-axr,A-axl,ndx,"NI");
		else axis.DrawAxis(axl,axb-(axt-axb)*.08,axr,axb-(axt-axb)*.08,axl+sel,axr+sel,ndx,"NI");
		axis.SetLabelOffset(0.01);
		
		TF2 scale("scale","y*[1]+[0]");
		
		// If there are levels and axised data
		if(dualyaxis){
			//Add an extra axis for the specified extra data class
			double ax,ay,bx,by;
			all_axis2_values.ComputeRange(ax,ay,bx,by);
			double R=by-ay;
			if(R==0)R=1;
			//  axis.SetLabelColor(kRed);
			double a=ay-R*(1./8.),b=by+R*(1./8.);
			axis.DrawAxis(axr,axb,axr,axt,a,b,ndy,"+L");
			double gr=(axt-axb)/(b-a);
			double cp=axb-a*gr;
			scale.SetParameters(cp,gr);
		}
		
		// Do the levels
		if(mastertype==0){
			TLine line;
			line.SetLineWidth(3);
			TLine line_join;
			line_join.SetLineWidth(1);
			
			for(unsigned int i=0;i<live_data_type.size();i++){
				if(live_data_type[i]==0&&individuals[i].GetN()>0){
					line.SetLineColor(live_data_color[i]);
					line_join.SetLineColor(live_data_color[i]);
					
					double cx=0,cy=0;
					
					for(int j=0;j<individuals[i].GetN();j++){
						double xxx,yyy;
						individuals[i].GetPoint(j,xxx,yyy);
						line.DrawLine(xxx-level_width,yyy,xxx+level_width,yyy);
						if(cy!=0)line_join.DrawLine(xxx-level_width,yyy,cx+level_width,cy);
						cx=xxx;cy=yyy;
					}
				}
			}
		}
		
		//Do the data 
		if(mastertype<2){
			for(unsigned int i=0;i<live_data_type.size();i++){
				if(live_data_type[i]==1&&individuals[i].GetN()>0){
					if(dualyaxis){
						individuals[i].Apply(&scale);
					}
					individuals[i].DrawClone("samep");
				}
			}
		}			
		
		//Do the remaining solo data sets which are all scaled 
		for(unsigned int i=0;i<live_data_type.size();i++){
			if(live_data_type[i]==2&&individuals[i].GetN()>0){
				double ax,ay,bx,by;
				individuals[i].ComputeRange(ax,ay,bx,by);
				double R=by-ay;
				if(R==0)R=1;
				double a=ay-R*(1./8.),b=by+R*(1./8.);
				double gr=(axt-axb)/(b-a);
				double cp=axb-a*gr;
				scale.SetParameters(cp,gr);
				individuals[i].Apply(&scale);
				individuals[i].DrawClone("samep");
			}
		}			
		
		pad->Update();
	}

	padsav->cd();//Change back if we moved away
	gPad->Update();
}//end of (LiveDynamicExec)

///////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// PENS parser functions  //////
	///////////////////////////////////////////	
////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////
	///////////////////////////////////////////
	//////// PENS parser Energy List  //////
	///////////////////////////////////////////	
////////////////////////////////////////////////////////////////


int nuclear_data_ob::LoadEnergyListFile(string filename){
	//Load the data into the global variables
   	ifstream infile;
	infile.open((filename).c_str());
	if(infile.is_open()){
		string str;
		while(getline(infile, str, '\n')){
			stringstream ss;
			ss << str;
			double trans;
			ss>>trans;
			ScanTransEnergy.push_back(trans);
			ScanTransString.push_back(str);
		}
		return 1;
	}
	cout<<endl<<"File "<<filename<<" not found."<<endl;
	return 0;
}


int nuclear_data_ob::AddElectronListLee(string sym,int A,int format,double cut){
	int Z=get_Z(sym);
	if(Z){return AddElectronListLee(Z,A,format,cut);}
	return 0;
}
int nuclear_data_ob::AddElectronListLee(int Z,int A,int format,double cut){
	AddEnergyListLee(Z,A,format,cut,get_Kbinding(Z)," K");
	AddEnergyListLee(Z,A,format,cut,get_Lbinding(Z)," L");
	return 1;
}

int nuclear_data_ob::AddEnergyListLee(string sym,int A,int format,double cut){
	int Z=nuclear_data_ob::get_Z(sym);
	if(Z)return AddEnergyListLee(Z,A,format,cut);
	return 0;
}

int nuclear_data_ob::AddEnergyListLee(int Z,int A,int format,double cut,double sub,string note){
	if(!LeeData())return 0;

	int count=0;
	
	cNucleusIterator Iter;
	while(cNucleusInh* nucleus=Iter()){
		if(nucleus->GetZ()==Z&&(nucleus->GetA()==A||A==0)){//Only add specified nuclei (or Z)
			for(unsigned int i=0;nucleus->IsTrans(i);i++){//Iterate over all transitions of this nucleus
				
				double Ep=nucleus->GetLevelEnergy(nucleus->GetTransP(i));
				double Ey=nucleus->GetTransEnergy(i);
				Ey-=sub;
				
				if((cut<=0||cut>Ep)&&Ey>0){//Cut off higher levels	
					ScanTransEnergy.push_back(Ey);
				
					stringstream ss;
					ss<<Ey;
					if(format)ss<<" "<<nucleus->ENSDFNucleusString();
					if(format>1)ss<<" "<<nucleus->ENSDFTransitionString(i);
					ss<<note;
					
					ScanTransString.push_back(ss.str());
					count++;
				}
			}
		}
	}
	cout<<endl<<count<<" transitions loaded."<<endl;

	return 1;
}


//////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////
	//////// PENS parser Fill Dynamic from Adder  //////
	//////////////////////////////////////////////////	
///////////////////////////////////////////////////////////////////////
void nuclear_data_ob::AddENSDFdatum(NucDatumSpecifier* Adder){if(!LeeData())return;
	
	push_data_live(Adder->AdderName(),Adder->cDrawType,Adder->cColour,Adder->cMarker);//Create a new black data item
	int ii=live_data.size()-1;
	
	cNucleusIterator Iter;	
	while(cNucleusInh* nucleus=Iter()){
		int lZ=nucleus->GetZ(),lN=nucleus->GetN();if(!general_reader(lZ,lN+lZ))continue;
		if(odd_even(lZ,lN,Adder->oddN,Adder->oddZ)){
			double datum[3]={0,0,0};
			if(Adder->GetDatum(datum,nucleus)){
				if(datum[0])live_data[ii][lZ][lN]=datum[0];
				if(datum[1])live_data_lower_error[ii][lZ][lN]=datum[1];
				if(datum[2])live_data_upper_error[ii][lZ][lN]=datum[2];
			}
		}
	}
}	



	///////////////////////////////////////////////////
	///////////////////////////////////////////////////
	/////////// END OF NUCLEAR DATA OBJECT  ///////////
	//////////////////////////////////////////////////
	///////////////////////////////////////////////////


	///////////////////////////////////////////////////
	///////////     cNucleusIterator        ///////////
	//////////////////////////////////////////////////


	cNucleusIterator::cNucleusIterator():iter_i(0),nucpoint(0){
		if(nuclear_data_ob::LeeData())nuclear_data_ob::LeeData()->SetBranchAddress("Nucleus",&nucpoint);
	}
	
	cNucleusIterator::~cNucleusIterator(){}

	cNucleusInh* cNucleusIterator::operator() (){
		if(nuclear_data_ob::LeeData())if(iter_i<nuclear_data_ob::LeeData()->GetEntries()){
			nuclear_data_ob::LeeData()->GetEntry(iter_i);
			iter_i++;		
			return static_cast< cNucleusInh* > (nucpoint);
		}
		return 0;
	}
	

	
	
