//
//
//	James Target Object and related functions 2.1
// 	27/01/25		25/01/2015
//	james.smallcombe@outlook.com
//
//

#include "james_target.h"

///////////////////////////////////////////////
/////////// Conversion functions    ///////////
///////////////////////////////////////////////

//If at centre give half thickness
//rotation clockwise while looking down
//thickness is total
//(0,0,1) is beam direction
//(0,1,0) axis of rotation, clockwise from "above"
//direction from 0, rotation in degrees, nominal thickness
double target_effective(TVector3 world,double degees,double thickness){
	TVector3 shldntbndd=world;
	TRotation rot;
	rot.RotateY((-degees/180)*TMath::Pi());
	shldntbndd*=rot;
	double the=shldntbndd.Theta();
	return abs(thickness/(TMath::Cos(the)));
	
}
double target_effective(TVector3 world,TVector3 targ_norm,double thickness){
	double ang= world.Angle(targ_norm);
	if(ang==0)ang=0.00000000000001;
	return abs(thickness/(cos(abs(ang))));
}


//input density in g/cm3 and arial density in ug/cm2
double giveme_um(double p,double a, bool print){
	double t=(a/p)*0.01;
	if(print)cout<<endl<<"Thickness "<<t<<" um."<<flush;
	return t;
}

//input density in g/cm3 and thickness in um
double giveme_areal(double p,double t,bool print){
	double a=(t*p)*100;
	if(print)cout<<endl<<"Areal density "<<a<<" ug/cm^2."<<flush;
	return a;
}

void set_global_compound(vector<double> k){
	
	double n=floor((double)k.size()/3.0);
	//setting commpounds into range.h
	if(n>1){
		if(n>4)n=4;
		nelem = n;	
		for(int m=0;m<n;m++){
			absorb[m].z = round(k[m*3]);
			absorb[m].a = round(k[(m*3)+1]);
			absorb[m].w = k[(m*3)+2];
		}
	}
}


///////////////////////////////////////////////////
/////////// Constructor & Destructor    ///////////
//////////////////////////////////////////////////


target::target(int a, int b, double c, TVector3 d, int e, double g, int h, int i, int j): targ_Z(a), targ_A(b),target_thickness(c),targ_norm(d),targ_fornmal(d),targ_compound(e),backing_thickness(g),backing_Z(h),backing_A(i),backing_compound(j),downstream_back(0),eloss_frag_graph_targ(),eloss_frag_graph_back()
{
// 	stringstream ss;// 	rand.SetSeed();// 	ss << rand.Rndm();// 	randstr=ss.str();
// 	eloss_frag_graph_targ=TH2D(("eloss_frag_graph_targ"+randstr).c_str(),"eloss_frag_graph_targ", 10000,0,1000,2000,0.05,200.05);
// 	eloss_frag_graph_back=TH2D(("eloss_frag_graph_back"+randstr).c_str(),"eloss_frag_graph_back", 10000,0,1000,2000,0.05,200.05);

	if(TVector3(0.0,0.0,1.0).Angle(targ_norm)>(pi/2)){targ_fornmal=-targ_norm;downstream_back=true;} else targ_fornmal=targ_norm;
	for(int j=0;j<4;j++)particle.push_back(new TGraph());
}



// C++11CODE //target::target(int a, int b, double c, double d, int e, double g, int h, int i, int j): target(a,b,c,TVector3(0.0,0.0,1.0),e,g,h,i,j)
target::target(int a, int b, double c, double d, int e, double g, int h, int i, int j): targ_Z(a), targ_A(b),target_thickness(c),targ_norm(0.0,0.0,1.0),targ_fornmal(0.0,0.0,1.0),targ_compound(e),backing_thickness(g),backing_Z(h),backing_A(i),backing_compound(j),downstream_back(0),eloss_frag_graph_targ(),eloss_frag_graph_back()
{
	targ_norm.RotateY((-d/180)*pi);
	if(TVector3(0.0,0.0,1.0).Angle(targ_norm)>(pi/2)){targ_fornmal=-targ_norm;downstream_back=true;} else targ_fornmal=targ_norm;
	for(int j=0;j<4;j++)particle.push_back(new TGraph());
}


target::target( const target &obj){
	targ_Z=obj.targ_Z;
	targ_A=obj.targ_A;
	target_thickness=obj.target_thickness;
	targ_norm=obj.targ_norm;
	targ_fornmal=obj.targ_fornmal;
	targ_compound=obj.targ_compound;
	backing_thickness=obj.backing_thickness;
	backing_Z=obj.backing_Z;
	backing_A=obj.backing_A;
	backing_compound=obj.backing_compound;
	downstream_back=obj.downstream_back;
	
	particle.resize(4);
	for(int j=0;j<4;j++)particle[j] = (TGraph*)obj.particle[j]->Clone();	
//	for(int j=0;j<4;j++)particle.push_back(new TGraph(*(obj.particle[j])));	
	
	eloss_frag_graph_targ=obj.eloss_frag_graph_targ;
	eloss_frag_graph_back=obj.eloss_frag_graph_back;
}

target& target::operator=( const target &obj){
	if(this!=&obj){//to prevent self-assignment errors
		for(int j=0;j<4;j++)delete particle[j];	
		
		targ_Z=obj.targ_Z;targ_A=obj.targ_A;
		target_thickness=obj.target_thickness;	targ_norm=obj.targ_norm;
		targ_fornmal=obj.targ_fornmal;	targ_compound=obj.targ_compound;
		backing_thickness=obj.backing_thickness;backing_Z=obj.backing_Z;
		backing_A=obj.backing_A;backing_compound=obj.backing_compound;
		downstream_back=obj.downstream_back;
		
		particle.resize(4);
		for(int j=0;j<4;j++)particle[j] = (TGraph*)obj.particle[j]->Clone();	
	//	for(int j=0;j<4;j++)particle.push_back(new TGraph(*(obj.particle[j])));	
		
		eloss_frag_graph_targ=obj.eloss_frag_graph_targ;
		eloss_frag_graph_back=obj.eloss_frag_graph_back;
	}
	return (*this); // for cascading assignment
}

target::~target(){
	for(int j=0;j<4;j++)delete particle[j];	
}

target target::inverse(){
	if(backing_thickness>0){
		target rettarg(backing_Z,backing_A,backing_thickness,-targ_norm,backing_compound,target_thickness,targ_Z,targ_A,targ_compound);
	for(int j=0;j<1;j++)rettarg.particle[j] = (TGraph*)this->particle[j+2]->Clone();	
	for(int j=0;j<1;j++)rettarg.particle[j+2] = (TGraph*)this->particle[j]->Clone();		
		rettarg.eloss_frag_graph_targ=this->eloss_frag_graph_back;
		rettarg.eloss_frag_graph_back=this->eloss_frag_graph_targ;
		return rettarg;
	}
	return *this;
}

//////////////////////////////////
/////////// Methods    ///////////
//////////////////////////////////

double target::number_density(){//return partiles/mb
	double fraction=1.0;
	if(targ_compound<0){
		fraction=0;
		double tar=0,sum=0;
		for(int m=0;m<nelem;m++){
			if(targ_Z==absorb[m].z&&targ_A==absorb[m].a)tar=absorb[m].w;
			sum+=absorb[m].w;
		}
		if(tar>0)fraction=tar/sum;
	}
	return target_effective(TVector3(0.0,0.0,1.0),targ_norm,1.0)*target_thickness*fraction*6.02214129E-10/double(targ_A);
}


double target::beam_e_centre(int z,int a,double mev,TVector3 beamv,double fraction_in){
	double enterance=2;
	if(abs(targ_fornmal.Angle(beamv))<pi/2)enterance=-1;
// 	cout<<endl<<startfr<<" "<<fraction_in<<endl;
	return traverse(z,a,mev,beamv,enterance,fraction_in,false);
}

double target::beam_e_centre_reverse(int z,int a,double mev,TVector3 beamv,double fraction_in){
	double enterance=2;
	if(abs(targ_fornmal.Angle(beamv))<pi/2)enterance=-1;	
	return traverse(z,a,mev,beamv,enterance,fraction_in,true);
}

double target::particle_e_exit(int z,int a,double mev,TVector3 traj,double& fraction_in){
	double exit=-1;
	if(abs(targ_fornmal.Angle(traj))<pi/2)exit=2;	
	return traverse(z,a,mev,traj,fraction_in,exit,false);
}

double target::particle_e_reverse(int z,int a,double mev,TVector3 traj,double fraction_in){
	double exit=-1;
	if(abs(targ_fornmal.Angle(traj))<pi/2)exit=2;	
	return traverse(z,a,mev,traj,fraction_in,exit,true);
}

double target::traverse(int z,int a,double mev_in,TVector3 traj,double startfr,double endfr,bool reverse){
	
	double mev=abs(mev_in);	
	if(mev<0.001&&!reverse)return 0.0;//avoid some problems

	double * tempd= new double(0);
	double eff_thick=target_effective(targ_norm,traj,1.0);
	double pfrac=1;
			
	if(reverse){double a=startfr;startfr=endfr;endfr=a;traj-=traj;}

	bool flip=false;
	if(abs(targ_fornmal.Angle(traj))>pi/2){//going out the back (upstream). Counts through 3 layers, what order they are in depends on direction relative to target orinations
		flip=true;
		startfr=1-startfr;
		endfr=1-endfr;
	}
	if(startfr>endfr){double a=startfr;startfr=endfr;endfr=a;}
	
	if(!(downstream_back^flip)&&startfr<0&&backing_thickness>0){//backing layer 1
			pfrac=-startfr;
			if(endfr<0)pfrac+=endfr;
			if(reverse) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);
	}
	if(startfr<1&&endfr>0){//target, layer 2
			if(startfr<0)startfr=0;
			if(endfr<1)pfrac=endfr-startfr;
			else pfrac=1-startfr;	
			if(reverse) mev=egassap(0,z,a,targ_compound,targ_Z,targ_A,eff_thick*(target_thickness/1000)*pfrac,mev,tempd);
			else mev=passage(0,z,a,targ_compound,targ_Z,targ_A,mev,eff_thick*(target_thickness/1000)*pfrac,tempd);
	}		
	if((downstream_back^flip)&&backing_thickness>0&&endfr>1){//layer 3
			if(startfr<1)startfr=1;
			if(endfr<2)pfrac=endfr-startfr;
			else pfrac=2-startfr;
			if(reverse) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);
	}
	
	if(mev<0.001)return 0.0;//avoid some problems
	if(!(reverse^(mev_in>mev))){//if they energy has gone up instead of down
		if(mev<0.1)return 0;//The range library tends to get shitty near 0
		return mev_in;
	}//
	delete tempd;
	return mev;	
}

void target::set_particle(int Z,int A){
	//reset
	for(int j=0;j<4;j++) *particle[j]= TGraph();
	
	double E=500.0;
	double xt=E,yt=1E10;
	double xb=E,yb=1E10;
	bool t=false,b=false;
	double R=0;
	while(E>0.050){
		if(target_thickness>0){
			if(!t)R=rangen(0,Z,A,targ_compound,targ_Z,targ_A,E)*1000;
			if(!(R<yt&&R>0)||t){R=E*(yt/xt);t=true;}//if stupid value produced, track linearly to zero
			particle[0]->SetPoint(particle[0]->GetN(),R,E);
			particle[1]->SetPoint(particle[1]->GetN(),E,R);
			xt=E;yt=R;
		}
		
		if(backing_thickness>0){
			if(!b)R=rangen(0,Z,A,backing_compound,backing_Z,backing_A,E)*1000;
			if(!(R<yb&&R>0)||b){R=E*(yb/xb);b=true;}
			particle[2]->SetPoint(particle[2]->GetN(),R,E);
			particle[3]->SetPoint(particle[3]->GetN(),E,R);
			xb=E;yb=R;
		}
		E*=0.95;
	}
	
	//add the very important zerpoint
	for(int j=0;j<4;j++)particle[j]->SetPoint(particle[j]->GetN(),0,0);
}

double target::get_range_particle(bool back,double mev){
	if(mev>0){
		if(back)return particle[3]->Eval(mev);
		else return particle[1]->Eval(mev);
	}
	return 0.0;
}

double target::passage_particle(bool back,double mev,double ugcm2,bool reverse){
	if(mev>0){
		double R=this->get_range_particle(back,mev);
		if(R>ugcm2){
			double i=-1; if(reverse)i=1;
			if(back)return particle[2]->Eval(R+i*ugcm2);
			else return particle[0]->Eval(R+i*ugcm2);
		}
	}
	return 0.0;
}

double target::traverse_p(double mev_in,TVector3 traj,double startfr,double endfr,bool reverse){
	return this->traverse_p(mev_in,target_effective(targ_norm,traj,1.0),startfr,endfr,reverse);
}

double target::traverse_p(double mev_in,double eff,double startfr,double endfr,bool reverse){
	double mev=abs(mev_in);
	if(mev<0.001&&!reverse)return 0.0;//avoid some problems

	double pfrac=1;
			
	if(reverse){double a=startfr;startfr=endfr;endfr=a;}

	bool flip=false;
	if(endfr<startfr){//going out the back (upstream). Counts through 3 layers, what order they are in depends on direction relative to target orinations
		flip=true;
		startfr=1-startfr;
		endfr=1-endfr;
	}
	if(startfr>endfr){double a=startfr;startfr=endfr;endfr=a;}
	
	if(!(downstream_back^flip)&&startfr<0&&backing_thickness>0){//backing layer 1
			pfrac=-startfr;
			if(endfr<0)pfrac+=endfr;
			mev=this->passage_particle(true,mev,eff*(backing_thickness/1000)*pfrac,reverse);
	}
	if(startfr<1&&endfr>0){//target, layer 2
			if(startfr<0)startfr=0;
			if(endfr<1)pfrac=endfr-startfr;
			else pfrac=1-startfr;	
			mev=this->passage_particle(false,mev,eff*(backing_thickness/1000)*pfrac,reverse);
	}		
	if((downstream_back^flip)&&backing_thickness>0&&endfr>1){//layer 3
			if(startfr<1)startfr=1;
			if(endfr<2)pfrac=endfr-startfr;
			else pfrac=2-startfr;
			mev=this->passage_particle(true,mev,eff*(backing_thickness/1000)*pfrac,reverse);
	}
	
	if(mev<0.001)return 0.0;//avoid some problems
	if(!(reverse^(mev_in>mev))){return mev_in;}
	return mev;	
}


//Use TH2D not graph2D because interpolate on graph is too slow
void target::fragment_set(double Z,double A){
	stringstream ss;
	ss << targ_Z << " " <<targ_A<<" "<<target_thickness;
	string extrastr=ss.str();
	
	//If its already been made it'll be stored in the run directory
	TFile* qfile = new TFile("eloss_store.root","READ");
	if(qfile->IsOpen()){
		TH2D * h2a;
		h2a = (TH2D*)qfile->Get("eloss_frag_graph_targ");
		this->eloss_frag_graph_targ= *h2a;
		this->eloss_frag_graph_targ.SetName(("eloss_frag_graph_targ"+extrastr).c_str());
		TH2D * h2b;
		h2b = (TH2D*)qfile->Get("eloss_frag_graph_back");
		this->eloss_frag_graph_back= *h2b;
		this->eloss_frag_graph_back.SetName(("eloss_frag_graph_back"+extrastr).c_str());
		cout<<endl<<endl<<"READ FRAGMENT E LOSS TO TARGET. DELETE eloss_store.root IF UNDESIRED."<<endl<<endl;
		
		qfile->Close();
		delete qfile;
		return;
	}
	
	//otherwise create new ones
	

	eloss_frag_graph_targ=TH2D(("eloss_frag_graph_targ"+extrastr).c_str(),"eloss_frag_graph_targ", 10000,0,1000,2000,0.05,200.05);
	eloss_frag_graph_back=TH2D(("eloss_frag_graph_back"+extrastr).c_str(),"eloss_frag_graph_back", 10000,0,1000,2000,0.05,200.05);
	
	double ratio=Z/A;
	
	//create the var hist
	//82
	//double xbins[]={0.05,0.15,0.25,0.35,0.45,0.55,0.65,0.75,0.85,0.95,1.25,1.75,2.25,2.75,3.25,3.75,4.25,4.75,5.25,6.5,7.5,8.5,9.5,10.5,11.5,12.5,13.5,14.5,15.5,16.7,17.5,18.5,19.5,21,23,25,27,29,31,33,35,37,39,41,46,50,54,58,62,66,70,74,78,82,95,105,115,125,135,145,155,165,175,185,195,210,230,250,270,290,310,330,350,370,390,425,475,550,650,750,850,950,1050};
	double xbins[347];
	for(int z=0;z<=199;z++)xbins[z]=0.1*(double)z;
	for(int z=0;z<=60;z++)xbins[z+200]=(0.5*(double)z)+20;
	for(int z=0;z<=50;z++)xbins[z+260]=((double)z)+50;
	for(int z=0;z<=40;z++)xbins[z+300]=(10*(double)z)+100;
	for(int z=0;z<=5;z++)xbins[z+340]=(100*(double)z)+500;
	xbins[346]=1001;
	TH2D varhista("varhista","varhista", 346,xbins,200,0.5,200.5);	
	TH2D varhistb("varhistb","varhistb", 346,xbins,200,0.5,200.5);
	
	//For targ material
	//calc the z averages E loss	

	for(int a=9;a<=200;a++){
		double* tempd=new double(0);
		double idealZ=(double)a*ratio;
		int z=round(idealZ);
		double weight_sum=0;
		double ZZ[5];
		for(int k=-2;k<=2;k++){
			ZZ[k+2]=TMath::Gaus(z+k,idealZ);
			weight_sum+=ZZ[k+2];
		}
		int f=0,l=4;
		if(abs(idealZ-(double)z)>0.25){weight_sum-=ZZ[0];f=1;}
		if(abs(idealZ-(double)z)<-0.25){weight_sum-=ZZ[4];l=3;}

		for(int i=1;i<=346;i++){//346
			double Emev=varhista.GetXaxis()->GetBinCenter(i);
			double en=0;
			for(int k=f;k<=l;k++){
				en+=(Emev-passage(0,z+k-2,a,targ_compound,targ_Z,targ_A,Emev,1.1*(target_thickness/1000),tempd))*ZZ[k];//*(3-abs(k));
			}
			en/=weight_sum;			
			if(en>Emev)en=Emev;
			if(en<0)en=0;
			varhista.SetBinContent(i,a,en);
		}	
		delete tempd;
		// 	was split into 2 loops because it was really slow otherwise for some reason
		tempd=new double(0);
		for(int i=1;i<=346;i++){//346
			double Emev=varhistb.GetXaxis()->GetBinCenter(i);
			double en=0;
			for(int k=f;k<=l;k++){
				en+=(Emev-passage(0,z+k-2,a,backing_compound,backing_Z,backing_A,Emev,1.1*(backing_thickness/1000),tempd))*ZZ[k];//*(3-abs(k));
			}
			en/=weight_sum;			
			if(en>Emev)en=Emev;
			if(en<0)en=0;
			varhistb.SetBinContent(i,a,en);	
		}
		delete tempd;	
	}

	//copy into a more fleshed out even histogram
	for(int i=1;i<=10000;i++){
		double Emev=(0.05+(0.1*i));
		for(int j=90;j<=2000;j++){
			double mass=(0.1+(0.1*j));
			double ena=varhista.Interpolate(Emev,mass);
			eloss_frag_graph_targ.SetBinContent(i,j,ena);			
			double enb=varhistb.Interpolate(Emev,mass);
			eloss_frag_graph_back.SetBinContent(i,j,enb);
		}
	}
	
	eloss_frag_graph_targ.Smooth();	
	eloss_frag_graph_targ.Smooth();	
	eloss_frag_graph_targ.Smooth();			
				
	eloss_frag_graph_back.Smooth();
	eloss_frag_graph_back.Smooth();
	eloss_frag_graph_back.Smooth();
	
	//write it for saves
	TFile* rfile = new TFile("eloss_store.root","RECREATE");
		eloss_frag_graph_targ.Write("eloss_frag_graph_targ");
		eloss_frag_graph_back.Write("eloss_frag_graph_back");
	rfile->Close();
	delete rfile;
}

double target::fragment_e_exit(double mass,double energy,TVector3 traj,double fraction_in){
	if(fraction_in<=0)fraction_in=0.5;
	if(fraction_in!=0.5)if(abs(targ_fornmal.Angle(traj))<pi/2)fraction_in=1-fraction_in;//going out the front
	
	if(mass>=10&&mass<200&&energy>0&&energy<1000){
		bool backing_traversed=false;
		if(backing_thickness>0 && (abs(targ_norm.Angle(traj))>pi/2)){backing_traversed=true;}
		
		double ebeam_slow=energy;
		double eff_thick=target_effective(traj,targ_norm,(1.0/1.1));
		
		ebeam_slow=ebeam_slow-(eloss_frag_graph_targ.Interpolate(ebeam_slow,mass)*eff_thick*fraction_in);
		if(backing_traversed)ebeam_slow=ebeam_slow-(eloss_frag_graph_back.Interpolate(ebeam_slow,mass)*eff_thick);
		
		return ebeam_slow;	
		
// // // 		double* tempd=new double(0);
// // // 		double pass=passage(0,mass*(40.0/90.0),mass,targ_compound,targ_Z,targ_A,energy,target_effective(traj,targ_norm,(target_thickness/1000)),tempd);
// // // 		delete tempd;
// // // 		return pass;
	}
	return 0;
}

 

// double target::beam_e_centre(int z,int a,double mev,TVector3 beamv,double fraction_in){
// 	if(mev<0.001)return 0.0;
// 	
// 	if(fraction_in<=0)fraction_in=0.5;
// 	if(fraction_in!=0.5)if(abs(targ_fornmal.Angle(-beamv))<pi/2)fraction_in=1-fraction_in;//coming in the front
// 	
// 	bool backing_traversed=false;
// 	if(backing_thickness>0 && (abs(targ_norm.Angle(-beamv))>pi/2))backing_traversed=true;
// 	
// 	double ebeam_slow=mev;
// 	double eff_thick=target_effective(beamv,targ_norm,1.0);
// 	double * tempd= new double(0);
// 	
// 	if(backing_traversed)ebeam_slow=passage(0,z,a,targ_compound,backing_Z,backing_A,ebeam_slow,eff_thick*(backing_thickness/1000),tempd);
// 	ebeam_slow=passage(0,z,a,targ_compound,targ_Z,targ_A,ebeam_slow,eff_thick*(target_thickness/1000)*fraction_in,tempd);
// 
// 	delete tempd;
// 	if(ebeam_slow>mev)return mev;
// 	return ebeam_slow;
// }
// 
// double target::beam_e_centre_reverse(int z,int a,double mev,TVector3 beamv,double fraction_in){
// 	if(fraction_in<=0)fraction_in=0.5;
// 	if(fraction_in!=0.5)if(abs(targ_fornmal.Angle(-beamv))<pi/2)fraction_in=1-fraction_in;//coming in the front
// 	
// 	bool backing_traversed=false;
// 	if(backing_thickness>0 && (abs(targ_norm.Angle(-beamv))>pi/2))backing_traversed=true;
// 	
// 	double ebeam_fast=mev;
// 	double eff_thick=target_effective(beamv,targ_norm,1.0);
// 	double * tempd= new double(0);
// // 	cout<<z<<" "<<a<<" "<<targ_compound<<" "<<targ_Z<<" "<<targ_A<<" "<<eff_thick*(target_thickness/1000)*fraction_in<<" "<<ebeam_fast<<endl;
// 	ebeam_fast=egassap(0,z,a,targ_compound,targ_Z,targ_A,eff_thick*(target_thickness/1000)*fraction_in,ebeam_fast,tempd);	
// 	if(backing_traversed)ebeam_fast=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000),ebeam_fast,tempd);
// 	
// 	delete tempd;	
// 	return ebeam_fast;
// }
// 
// double target::particle_e_exit(int z,int a,double mev,TVector3 traj,double& fraction_in){
// 	if(mev<0.001)return 0.0;//avoid some problems
// 
// 	//fraction_in gives how far into the target FROM BEAM ORIGIN an evenr takes place
// 	//fraction_in between -1 and 2, dependent on backing	
// 	
// 	//invalid fraction_in
// 	if(fraction_in>1&&backing_thickness<=0)fraction_in = 1;
// 	if(fraction_in<0&&backing_thickness<=0)fraction_in = 0;
// 	if(fraction_in<-1)fraction_in = -1;
// 	if(fraction_in>2)fraction_in = 2;
// 
// 	
// 	bool beamward=false,backingward=false,backing_start=false;
// 	if(abs(targ_fornmal.Angle(traj))<pi/2)beamward=true;//going out the front
// 	if(backing_thickness>0 && (downstream_back==beamward))backingward=true;//going "towards" backing 
// 	if(abs(fraction_in-0.5)>0.5&&backing_thickness>0)backing_start=true;
// 	
// 	//if fraction is set to wrong side for target defintion we fix it
// 	if(downstream_back&&fraction_in<0)fraction_in=1-fraction_in;
// 	if(!downstream_back&&fraction_in>1)fraction_in=1-fraction_in;
// 	
// 
// 	double ebeam_slow=mev;
// 	double eff_thick=target_effective(targ_norm,traj,1.0);
// 	double * tempd= new double(0);
// 	
// 	if(backing_start){
// 		double fraction_back=fraction_in-1.0;//set distance from upstream
// 		if(fraction_in<0)fraction_back=fraction_in+1.0;//set distance from upstream
// 		if(beamward)fraction_back=1-fraction_back;//going out the front		
// 
// 		
// 		if(fraction_back>0)ebeam_slow=passage(0,z,a,backing_compound,backing_Z,backing_A,ebeam_slow,fraction_back*eff_thick*(backing_thickness/1000),tempd);
// 		if(!backingward)ebeam_slow=passage(0,z,a,targ_compound,targ_Z,targ_A,ebeam_slow,eff_thick*(target_thickness/1000),tempd);
// 	}else{
// 		double fraction_targ=fraction_in;
// 		if(beamward)fraction_targ=1-fraction_in;//going out the front	
// 
// 		if(fraction_targ>0)ebeam_slow=passage(0,z,a,targ_compound,targ_Z,targ_A,ebeam_slow,fraction_targ*eff_thick*(target_thickness/1000),tempd);
// 		if(backingward)ebeam_slow=passage(0,z,a,backing_compound,backing_Z,backing_A,ebeam_slow,eff_thick*(backing_thickness/1000),tempd);		
// 	}
// 	
// 	delete tempd;	
// 	if(ebeam_slow>mev)return mev;
// 	if(ebeam_slow<=mev&&ebeam_slow>0)return ebeam_slow;
// 	return 0;
// }
// 
// double target::particle_e_reverse(int z,int a,double mev,TVector3 traj,double fraction_in){
// 	if(fraction_in<=0)fraction_in=0.5;
// 	if(fraction_in!=0.5)if(abs(targ_fornmal.Angle(traj))<pi/2)fraction_in=1-fraction_in;//going out the front
// 	
// 	bool backing_traversed=false;
// 	if(backing_thickness>0 && (abs(targ_norm.Angle(traj))>pi/2))backing_traversed=true;
// 	
// 	double ebeam_fast=mev;
// 	double eff_thick=target_effective(targ_norm,traj,1.0);
// 	double * tempd= new double(0);
// 		
// 	if(backing_traversed)ebeam_fast=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000),ebeam_fast,tempd);
// 	ebeam_fast=egassap(0,z,a,targ_compound,targ_Z,targ_A,eff_thick*(target_thickness/1000)*fraction_in,ebeam_fast,tempd);
// 	
// 	delete tempd;
// 	return ebeam_fast;
// }

// double target::traverse(int z,int a,double mev_in,TVector3 traj,double startfr,double endfr,bool inquiry){
// 	
// 	double mev=abs(mev_in);	
// 	if(mev<0.001&&!inquiry)return 0.0;//avoid some problems
// 
// 	double * tempd= new double(0);
// 	double eff_thick=target_effective(targ_norm,traj,1.0);
// 	double pfrac=1;
// 	
// // 	cout<<startfr<<" -> "<<endfr;
// 	if(abs(targ_fornmal.Angle(traj))<pi/2){//going out the front (downstream)
// 		if(!downstream_back&&startfr<0&&backing_thickness>0){//fronting
// 			pfrac=-startfr;
// 			if(endfr<0)pfrac+=endfr;
// 			if(inquiry) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);
// // 	cout<<"A"<<pfrac;	
// // 	cout<<" f "<<startfr<<"("<<pfrac<<")";
// 		}
// 		if(startfr<1&&endfr>0){//target
// 			if(startfr<0)startfr=0;
// 			if(endfr<1)pfrac=endfr-startfr;
// 			else pfrac=1-startfr;
// 			if(inquiry) mev=egassap(0,z,a,targ_compound,targ_Z,targ_A,eff_thick*(target_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,targ_compound,targ_Z,targ_A,mev,eff_thick*(target_thickness/1000)*pfrac,tempd);
// // 	cout<<" t "<<startfr<<"("<<pfrac<<")";
// // 	cout<<"B"<<pfrac;
// 		}		
// 		if(downstream_back&&backing_thickness>0&&endfr>1){//backing
// 			if(startfr<1)startfr=1;
// 			if(endfr<2)pfrac=endfr-startfr;
// 			else pfrac=2-startfr;
// 			if(inquiry) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);
// // 	cout<<" b "<<startfr<<"("<<pfrac<<")";
// // 	cout<<"C"<<pfrac;
// 		}
// 	}else{//going out the back (upstream)
// 		if(downstream_back&&startfr>1&&backing_thickness>0){//backing
// 			if(endfr>1)pfrac=startfr-endfr;
// 			else pfrac=startfr-1;
// 			if(inquiry) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);	
// // 	cout<<" b "<<startfr<<"("<<pfrac<<")";
// 		}
// 		if(startfr>0&&endfr<1){//target
// 			if(startfr>1)startfr=1;
// 			pfrac=startfr;
// 			if(endfr>0)pfrac-=endfr;
// 			if(inquiry) mev=egassap(0,z,a,targ_compound,targ_Z,targ_A,eff_thick*(target_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,targ_compound,targ_Z,targ_A,mev,eff_thick*(target_thickness/1000)*pfrac,tempd);
// // 	cout<<" t "<<startfr<<"("<<pfrac<<")";
// 		}		
// 		if(!downstream_back&&backing_thickness>0&&endfr<0){//fronting
// 			if(startfr>0)startfr=0;
// 			if(endfr>-1)pfrac=startfr-endfr;
// 			else pfrac=startfr+1;			
// 			if(inquiry) mev=egassap(0,z,a,backing_compound,backing_Z,backing_A,eff_thick*(backing_thickness/1000)*pfrac,mev,tempd);
// 			else mev=passage(0,z,a,backing_compound,backing_Z,backing_A,mev,eff_thick*(backing_thickness/1000)*pfrac,tempd);
// // 	cout<<" f "<<startfr<<"("<<pfrac<<")";
// 		}
// 	}
// 	
// 	if(!(inquiry^(mev_in>mev))){return mev_in;}
// 	delete tempd;
// 	return mev;	
// }


 
/* 
double target::lifetime_track(int z,int a,double& ns,TLorentzVector* lor,double& fraction_in){
	//calculate initial parameters
	double KE_0=get_KE(lor);
	double beta_0=lor->Beta();
	double mass=lor->M()/jam_phys_amu;
	TVector3 traj=lor->Vect();
	
	//calc data for complete target exit
	//calling this will sort out fraction_in if it is backing reversed
	double KE_exit=this->particle_e_exit(z,a,KE_0,traj,fraction_in);if(KE_exit<0.001)KE_exit=0;
	double beta_exit=0;
	if(KE_exit>0) beta_exit=get_beta_KE(KE_exit,mass);
	

	
	
	//some logic gate about the relative layers and trajectories
	bool beamward=false,backingward=false,backing_start=false;
	if(abs(targ_fornmal.Angle(traj))<pi/2)beamward=true;//going out the front
	if(backing_thickness>0 && (downstream_back==beamward))backingward=true;//going "towards" backing 
	if(abs(fraction_in-0.5)>0.5&&backing_thickness>0)backing_start=true;
	bool two_layer=false;
	if(backing_start^backingward)two_layer=true;//if two layers will be traversed
	
	
	//total target component thicknesses in um
	double eff_thick=target_effective(targ_norm,traj,1.0);

	
	double frac1=fraction_in;
	double um1=giveme_um(density_targ,target_thickness,false)*eff_thick;
	double um2=giveme_um(density_back,backing_thickness,false)*eff_thick;		
	int com_1=targ_compound,com_2=backing_compound;
	int z1=targ_Z,z2=backing_Z,a1=targ_A,a2=backing_A;
	double thick1=target_thickness*eff_thick,thick2=backing_thickness*eff_thick;	
	if(backing_start){
		frac1=fraction_in-1.0;//set distance from upstream
		if(fraction_in<0)frac1=fraction_in+1.0;//set distance from upstream
		
		com_2=targ_compound;com_1=backing_compound;
		z2=targ_Z;z1=backing_Z;a2=targ_A;a1=backing_A;
		thick2=target_thickness*eff_thick;thick1=backing_thickness*eff_thick;
		double x=um1;um1=um2;um2=x;
	}
	if(beamward)frac1=1-frac1;//only needed for frac1 as frac2 is always 1!
	um1*=frac1;//only needed for frac1 as frac2 is always 1!
	
	
	
	//////////////////////// 
	///////// start actual calculations
	////////////////////////
	double tempd;
	bool stopped=false;
	double stopfrac=0;
	double ran1,ran2,KE_inbetween;
	
	// A overall approximation because "passage" is not very good at small steps
	ran1=(rangen(0,z,a,com_1,z1,a1,KE_0)*1000)/thick1;
	if(two_layer){
		KE_inbetween=passage(0,z,a,com_1,z1,a1,KE_0,thick1*frac1/1000,&tempd);
		if(!(KE_inbetween>0.001))KE_inbetween=0;if(KE_inbetween>KE_0)KE_inbetween=KE_0;
		ran2=(rangen(0,z,a,com_2,z2,a2,KE_inbetween)*1000)/thick2;
		
		while(!(ran2>=0)){
			
			ran2=(rangen(0,z,a,com_2,z2,a2,KE_inbetween*10)*1000)/(thick2*10);
		}
	}
	
	//total length ahead
	double x_0=um1;
// 	if(ran1<frac1){
// 		stopped=true;
// 		stopfrac=ran1;
// 		um1*=(ran1/frac1);
// 		x_0*=(ran1/frac1);
// 		KE_inbetween=0.0;
// 		two_layer=false;
// 		KE_exit=0.0;
// 		beta_exit=0.0;
// 	}else{ran1=frac1;}
		
	if(two_layer){
		if(ran2<1){
			x_0+=um2*ran2;
			stopped=true;
			stopfrac=ran2+frac1;
			um2*=ran2;
			KE_exit=0.0;
			beta_exit=0.0;
		}//else{ran2=1; x_0+=um2;}
	}
	
	//Rough calc how long it takes to stop OR exit
// 	double rough_time_ns=(x_0/((beta_0+beta_exit)*0.5*jam_phys_speed_c_mm_ns*1000));
// 	rough_time_ns/=0.5*((1/sqrt(1-beta_0*beta_0))+(1/sqrt(1-beta_exit*beta_exit)));
	
// 	//if exit with time to spare	
// 	if(beta_exit>0&&!stopped){
// 		if(rough_time_ns*5<ns){//target interaction finished well before time out
// 			ns=ns-rough_time_ns;	
// 
// 			if(backingward)fraction_in=-1+(3*beamward);
// 			else fraction_in=1.0*beamward;		
// 
// 			return beta_exit;
// 		}
// 	}
	
	//if stopped with time to spare	
	if(stopped){
// 		if(rough_time_ns*1.5<ns){//target interaction finished well before time out
			ns=0.0;	

			if(beamward) fraction_in+=stopfrac;
			else fraction_in-=stopfrac;	
fraction_in=ran2;
			return 0.0;
// 		}
	}	
	

// 	//IF we have reached this point EITHER stops shorly before decay OR decays in/near target
// 	//Do two careful loop to see if realtime expires before exit OR stop
// 	//The loops run until particle exit if it will exit OR particle stop if it will stop
// 	
// 	//starting conditions into loop variabls
// 	double KE_c=KE_0;
// 	double beta_c=beta_0;
// 	double t_t=0.0;
// 
// 	//do 10 steps through the fraction of the first layer we must traverse
// 	for(int i=0;i<10;i++){
// 		double KE_l=passage(0,z,a,com_1,z1,a1,KE_c,thick1*0.1*ran1/1000,&tempd);
// 		if(KE_l<0.001)KE_l=0;//safety because passage bad when small
// 		if(KE_l<KE_c)KE_l=((KE_0-KE_inbetween)*(0.1*(double)i))+KE_inbetween;//safety because passage bad when small
// 	
// 		//time taken to cross this section		
// 		double beta_l=0;
// 		beta_l=get_beta_KE(KE_l,mass);
// 		double t_l=((um1*0.1)/((beta_c+beta_l)*0.5*jam_phys_speed_c_mm_ns*1000));
// 		t_l/=0.5*((1/sqrt(1-beta_c*beta_c))+(1/sqrt(1-beta_l*beta_l)));	
// 		
// 		// if decayed in that 10th
// 		if(t_l+t_t>=ns){
// 			double partway=abs(ns-t_t)/t_l;
// 			double KEF=KE_c+((KE_c-KE_l)*partway);
// 			partway=0.1*((double)i+partway)*ran1;
// 
// 			if(beamward) fraction_in+=partway;
// 			else fraction_in-=partway;
// 
// 			ns=0.0;//remaining after target			
// 			return get_beta_KE(KEF,mass);//beta
// 		}			
// 			
// 		//prepare for next loop
// 		t_t+=t_l;
// 		KE_c=KE_l;
// 		beta_c=beta_l;
// 	}
// 	
// 
// 	// ran2 should = 1 if particle doesnt stop
// 	if(two_layer){
// 		
// 		KE_c=KE_inbetween;
// 
// 		//do 10 steps through the fraction of the second layer we must traverse
// 		for(int i=0;i<10;i++){
// 			double KE_l=passage(0,z,a,com_2,z2,a2,KE_c,thick2*0.1*ran2/1000,&tempd);if(KE_l<0.001)KE_l=0;
// 			if(KE_l<0.001)KE_l=0;//safety because passage bad when small
// 			if(KE_l<KE_c)KE_l=((KE_inbetween-KE_exit)*(0.1*(double)i))+KE_exit;//safety because passage bad when small
// 			
// 			//time taken to cross this section		
// 			double beta_l=0;
// 			beta_l=get_beta_KE(KE_l,mass);
// 			double t_l=((um2*0.1)/((beta_c+beta_l)*0.5*jam_phys_speed_c_mm_ns*1000));
// 			t_l/=0.5*((1/sqrt(1-beta_c*beta_c))+(1/sqrt(1-beta_l*beta_l)));	
// 			
// 			//if decayed in that 10th
// 			if(t_l+t_t>=ns){
// 				double partway=abs(ns-t_t)/t_l;
// 				double KEF=KE_c+((KE_c-KE_l)*partway);
// 				partway=0.1*((double)i+partway)*ran2;
// 
// 				if(beamward) fraction_in+=(partway+ran1);
// 				else fraction_in-=(partway+ran1);
// 
// 				ns=0.0;//remaining after target			
// 				return get_beta_KE(KEF,mass);//beta
// 			}			
// 				
// 			//prepare for next loop
// 			t_t+=t_l;
// 			KE_c=KE_l;
// 			beta_c=beta_l;
// 		}
// 	}
// 	
// 	
// 	// IF it stops in the target and doesnt decay before this point
// 	if(stopped){
// 		ns=0.0;	
// 
// 		if(beamward) fraction_in+=stopfrac;
// 		else fraction_in-=stopfrac;	
// 
// 		return 0.0;
// 	}	
// 	
// 	
// 	//if it reached this point it has exited without decaying
// 	if(two_layer)frac1+=1;
// 	if(beamward) fraction_in+=frac1;
// 	else fraction_in-=frac1;
// 	ns-=t_t;//remaining after target			
// 	return get_beta_KE(KE_c,mass);//beta	
// 	
	

	
	fraction_in=1.4;return 1.4;
}*/
 
 
 
target W_186_straight(74,186,140.0,180.0,0,60.2,6,12);
target W_186_twisted=target(74,186,140.0,-135.0,0,60.2,6,12);
target W_184_straight=target(74,184,130.6,180.0,0,63.7,6,12);
target W_184_twisted=target(74,184,130.6,-135.0,0,63.7,6,12);
target W_182_straight=target(74,182,100.7,180.0,0,63.7,6,12);
target W_182_twisted=target(74,182,100.7,-135.0,0,63.7,6,12);
target Z_90_straight=target(40,90,61.0,0.0,-1,216.0,13,27,0);
// C++11CODE //vector< double > Z_O_compound={8,16,32,40,90,90};



// vector< double > Z_O_compound(){
// 	vector< double > x;
// 	x.push_back(40);
// 	x.push_back(90);
// 	x.push_back(90);
// 	x.push_back(8);
// 	x.push_back(16);
// 	x.push_back(32);
// 	return x;
// }