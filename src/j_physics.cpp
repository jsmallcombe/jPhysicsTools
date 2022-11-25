//
//
//	j_physics version 2.0
// 	27/1/25		25/1/2015
//	james.smallcombe@outlook.com
//
//

#include "j_physics.h"

  /////////////////////////////////////////
 ////////// Functionallity Tools ///////// 
/////////////////////////////////////////

TLorentzVector make_lorentzvec(TVector3 mom,double mass){
	return TLorentzVector(mom,get_relE_mom(mom.Mag(),mass));
}	

void alight_to_Z(TVector3 beam,TVector3& toadjust){
	if(beam.Theta()>0.000000000000000001){
		TRotation rot;
		rot.RotateZ(-beam.Phi());
		rot.RotateY(-beam.Theta());
		toadjust*=rot;	
	}
	return;
}

  //////////////////////////////////////////////
 ////////// Nuclear Data Calculations ///////// 
//////////////////////////////////////////////

//
double classical_radius(double A){ //input A output in fm
	return 1.2*pow(round(A),(1.0/3.0));
}
	
double classical_barrier(double A1,double Z1,double A2,double Z2,double fm){ //input AZAZ,fm output in MeV
	return jam_phys_e4pieps*round(Z1)*round(Z2)/(classical_radius(A1)+classical_radius(A2)+fm);
}

double safe_r(double A1,double A2,int i){  // NOTE difference in R definition, here we use 1.2 as the base value (giving 1.25 and 1.44
	if(i==0)return ((classical_radius(A1)+classical_radius(A2))/0.96)+5.1;//Cline1969    
	if(i==1)return ((classical_radius(A1)+classical_radius(A2))*1.2)+2;//Alder and Winther 1975
	return ((classical_radius(A1)+classical_radius(A2))*1.33);//Friedlander
}

double viola_TKE(double A,double Z){ //input AZ output in MeV
	return (0.1189*Z*Z/(pow(round(A),(1.0/3.0))))+7.3;
}

double neck_TKE_manea(double A1,double Z1,double A2,double Z2){ //input AZ output in MeV
	
	//MISSING ELIPSOID K CORRECTION TO COULOMB BECAUSE MATHS WAS HARD
	//APPROX
	
	double L=(classical_radius(A1)+classical_radius(A2))/2;
	double c=pow((5/(4*TMath::Pi())),0.5);
	double bet1_postsci=nuclear_data_ob::get_beta(Z1,A1);
	double bet2_postsci=nuclear_data_ob::get_beta(Z2,A2);
	double a1_postsci=classical_radius(A1)*(1+c*bet1_postsci);
	double a2_postsci=classical_radius(A2)*(1+c*bet2_postsci);
	double x=L/(a1_postsci+a2_postsci);
	
	double g1=(1+c*bet1_postsci)/(1-0.5*c*bet1_postsci);
	double g2=(1+c*bet2_postsci)/(1-0.5*c*bet2_postsci);
	double f1=x*x*x*g1*g1/8;
	double f2=x*x*x*g2*g2/8;

	double r1=0.5*x*a1_postsci;
	double r2=0.5*x*a2_postsci;

	double bet1_presci=nuclear_data_ob::get_beta(Z1*(1-f1),(A1)*(1-f1));
	double bet2_presci=nuclear_data_ob::get_beta(Z2*(1-f2),(A2)*(1-f2));
	double a1_presci=classical_radius(A1*(1-f1))*(1+c*bet1_presci);
	double a2_presci=classical_radius(A2*(1-f2))*(1+c*bet2_presci);
	
	double terms=(1-f1)*(1-f2)*Z1*Z2/(L+a1_presci+a2_presci);
	terms+=f1*(1-f2)*Z1*Z2/(r1+r2+r2+a2_presci);
	terms+=f2*(1-f1)*Z1*Z2/(r2+r1+r1+a1_presci);
	terms+=f2*f1*Z1*Z2/(r2+r1);	
	
	return 1.44*terms;
}

// Return the maximum CM beam scattering angle for safe coulex distance of approach, given beam energy lab
double safe_coulex_angle(double AB,double ZB,double AT,double ZT,double e_lab){ //input AZAZ,MeV output in rad
	return happy_ruth_theta(AB,ZB,AT,ZT,get_com_KE(get_rel_mom(e_lab,AB),AB,AT));
}

// Returns the maximum beam energy for safe coulex distance of approach for a given CM beam scattering angle
double safe_coulex_beam(double A1,double Z1,double A2,double Z2,double theta_cm){ //input AZAZ,rad output in MeV
	double rmin=safe_r(A1,A2,0);//hardsphere touching distance + a little in fm
	double ang=sqrt((1+cos(theta_cm))/(1-cos(theta_cm)))*cos(theta_cm/2)/(1-sin(theta_cm/2));
	if(!(ang>0))ang=2;
	double KE_cm_tot=jam_phys_e4pieps*Z1*Z2*ang/(2*rmin);
	
	return get_KE(reverseal_mom_calc(momentum_energysplit_CoM(KE_cm_tot,A1,A2),A1, A2),A1);
}

// Return the maximum CM beam scattering angle for safe coulex distance of approach, given CoM total KE
double happy_ruth_theta(double A1,double Z1,double A2,double Z2,double e_cm){ //input AZAZ,MeV output in rad
	double b=coulex_safe_impact_parameter(A1,Z1,A2,Z2,e_cm);
    if(b>0){	
        double alpha=jam_phys_e4pieps*Z1*Z2/(e_cm*b);
        return 2*asin(alpha/sqrt(4+alpha*alpha)); //theta from that impact parameter cm
    }
     return pi;
}

/// https://farside.ph.utexas.edu/teaching/336k/Newton/node51.html

double coulex_impact_parameter(double AB,double ZB,double AT,double ZT,double e_cm,double theta_cm){
    double b=jam_phys_e4pieps*ZB*ZT/(e_cm*tan(theta_cm/2));
	return b; 
}

double coulex_safe_impact_parameter(double AB,double ZB,double AT,double ZT,double e_cm){
    
    double rmin=safe_r(AB,AT,0);//hardsphere touching distance + a little in fm
	double Etouch=jam_phys_e4pieps*ZB*ZT/rmin;//MeV. not actually touching
	if(e_cm<=Etouch) return 0;
	double b=(sqrt(1-(Etouch/e_cm)))*rmin; //impact parameter for selected rmin and e_cm
	
	return b; 
}


double rutherford_crosssection(double Z1,double Z2,double e_cm,double thetamin,double thetamax){ //input AZAZ,MeV,rad,rad output in mb
	if(thetamin>thetamax){double x=thetamin;thetamin=thetamax;thetamax=x;}
	if(thetamin<1E-6)thetamin=1E-6;
	if(thetamax>pi)thetamax=pi;

	double closest=jam_phys_e4pieps*Z1*Z2/(e_cm);
	
	// e^2/4*pi*epsilion_0 = finestructure * hbar * c = 197.3/137 MeV fm
	
	double constterm=closest*closest/16;
	
	double angular_dep=(2/(sin(thetamin/2)*sin(thetamin/2)))-(2/(sin(thetamax/2)*sin(thetamax/2)));
	angular_dep*=2*pi;
	
	return constterm*angular_dep*10; //multiply by 10 converts from fm^2 to mb
}

double rutherford_crosssection_lab(double AB,double AT,double Z1,double Z2,double Ebeam,double thetamin,double thetamax,int mode){
	
	double* ret=DetectorCoMAnglesElastic(Ebeam,AB,AT,thetamin,thetamax);
	
	double Ecm=get_com_KE_MeVbeam(Ebeam,AB,AT);

	double beam=0;
	if(ret[0]>0.0001)beam+=rutherford_crosssection(Z1,Z2,Ecm,ret[0],ret[1]);
	if(ret[2]>0.0001)beam+=rutherford_crosssection(Z1,Z2,Ecm,ret[2],ret[3]);

	double targ=0;
	if(ret[4]>0.0001)targ+=rutherford_crosssection(Z1,Z2,Ecm,ret[4],ret[5]);
	if(ret[6]>0.0001)targ+=rutherford_crosssection(Z1,Z2,Ecm,ret[6],ret[7]);
	
	delete ret;
	
	if(mode==0)return beam;
	if(mode==1)return targ;
	return beam+targ;//We dont use the fancy overlap part of ret for this as for rutherford you usually want total rate, even if it includes double hits
}








  ///////////////////////////////////////////////////////////////
 ////////// Single Body Relativistic  E & P calculators  ///////
///////////////////////////////////////////////////////////////

double get_relE_mom(double mom,double Amass){
	double mass=(jam_phys_amu*Amass);
	return sqrt((mom*mom)+(mass*mass));
}

double get_relE_KE(double KE,double Amass){
	double mass=(jam_phys_amu*Amass);
	return KE+mass;
}

double get_rel_mom(double emev,double Amass,bool overkill){//input particle KE in MeV and mass in amu
	double mass=(jam_phys_amu*Amass);
	double mom=emev+mass;
	mom*=mom;
	mom-=(mass*mass);
	mom=sqrt(mom);
	if(overkill) cout<<endl<<"Relativistic momentum = "<<mom<<" MeV/c. Classical = "<<sqrt(emev*2*mass);
	return mom;//momentum in MeV/c
}
	
double get_KE(double mom,double Amass,bool overkill){//input particle momentum in MeV/c and mass in amu
	double mass=(jam_phys_amu*Amass);
	double emev=sqrt(mom*mom+mass*mass)-mass;
	if(overkill) cout<<endl<<"KE = "<<emev<<" MeV. Classical = "<<(mom*mom)/(2*mass);
	return emev;//KE in MeV
}


double get_KE(TLorentzVector* four){//input Ep 4vec in MeV
	return four->E()-four->M();//KE in MeV
}


   //////////////////////////////////////////////////////
  ////////// Beta and Gamma calculators          ///////
 ////////// single particle in frame velocities /////// 
////////////////////////////////////////////////////// 

double get_gamma_KE(double emev,double Amass){//input particle KE in MeV and mass in amu
	double mass=(jam_phys_amu*Amass);
	double gamma=(emev/mass)+1;
	return gamma;
}

double get_gamma_mom(double mom,double Amass){//input particle KE in MeV and mass in amu
	double beta=get_beta_mom(mom,Amass);
	double gamma=1/sqrt(1-(beta*beta));
	
	return gamma;
}
double get_beta_KE(double emev,double Amass){//input particle KE in MeV and mass in amu
	double gamma=get_gamma_KE(emev,Amass);
	double beta=1/gamma;
	beta*=beta;
	beta=sqrt(1-beta);
	return beta;
}

double get_beta_mom(double mom,double Amass){//input particle momentum in MeV/c and mass in amu
	double mass=(jam_phys_amu*Amass);
	double beta=1/sqrt(((mass*mass)/(mom*mom))+1);
	return beta;//in frame velocity in C
}

double get_beta(TLorentzVector four){//input Ep 4vec in MeV
	return four.Beta();
}

TVector3 get_beta_vec(TVector3 mom,double mass){
	TVector3 beta = mom.Unit();
	beta*=get_beta_mom(mom.Mag(),mass);
	return beta;
}


TVector3 get_beta_vec(TLorentzVector four){//input Ep 4vec in MeV
	TVector3 beta = four.Vect().Unit();
	beta*=four.Beta();
	return beta;
}


     ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
   /////////////////////// Centre of Mass Calculations ///////////////////
  ///////////////////////    (Zero Momentum Frame)    ///////////////////
 ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

  ////////////////////////////////////
 ///////// Total KE in CoM    ///////
//////////////////////////////////// 

double get_com_KE(double mom,double massA,double massB){//input mom in MeV/c and 2 masses in amu
	double E_lab= get_relE_mom(mom,massA)+get_relE_mom(0,massB);
	double invarient_S=sqrt(E_lab*E_lab-mom*mom);
	return invarient_S - (massA+massB)*jam_phys_amu;
}
double get_com_KE_MeVbeam(double MeVbeam,double AB,double AT){
	return get_com_KE(get_rel_mom(MeVbeam,AB),AB,AT);
}

double get_com_KE(TVector3 momA,double massA,TVector3 momB,double massB){//input mom in MeV/c and 2 masses in amu
	double E_lab= get_relE_mom(momA.Mag(),massA)+get_relE_mom(momB.Mag(),massB);
	double invarient_S=sqrt(E_lab*E_lab-((momA+momB).Mag())*((momA+momB).Mag()));
	return invarient_S - (massA+massB)*jam_phys_amu;
}
double get_com_KE(TLorentzVector fourA,TLorentzVector fourB){//input Ep 4vec in MeV
	double invarient_S=(fourA+fourB).M();
	return invarient_S - fourA.M() - fourB.M();
}

   ////////////////////////////////////
  ///////// Velocity of CoM    ///////
 /////////   (Boost beta)     ///////
//////////////////////////////////// 

double get_com_beta(double mom,double Amass,double Bmass){//input MeV/c and mass in amu
	return mom/(get_relE_mom(mom,Amass)+get_relE_mom(0,Bmass));
}

double get_com_beta(TVector3 momA,double massA,TVector3 momB,double massB){
	return (momA+momB).Mag()/(get_relE_mom(momA.Mag(),massA)+get_relE_mom(momB.Mag(),massB));
}

TVector3 get_com_beta_vec(TVector3 momA,double massA,TVector3 momB,double massB){
	TVector3 beta = (momA+momB).Unit();
	beta*=get_com_beta(momA,massA,momB,massB);
	return beta;
}

TVector3 get_com_beta_vec(TVector3 momA,double massA,TVector3 momB,double massB,TVector3 momC, double massC){
	TVector3 beta = (momA+momB+momC).Unit();
	beta*=(momA+momB+momC).Mag()/(get_relE_mom(momA.Mag(),massA)+get_relE_mom(momB.Mag(),massB)+get_relE_mom(momC.Mag(),massC));
	return beta;
}

double get_com_beta(TLorentzVector fourA,TLorentzVector fourB){//input Ep 4vec in MeV
	return get_beta(fourA+fourB);
}

TVector3 get_com_beta_vec(TLorentzVector fourA,TLorentzVector fourB){//input Ep 4vec in MeV
	return get_beta_vec(fourA+fourB);
}

TVector3 get_com_beta_vec(TLorentzVector fourA,TLorentzVector fourB,TLorentzVector fourC){//input Ep 4vec in MeV
	return get_beta_vec(fourA+fourB+fourC);

}

  ///////////////////////////////////
 ///////// CoM -> Beam cals   //////
///////////////////////////////////

double reverseal_beta_calc(double mom_0,double targ_mass){
	return mom_0/get_relE_mom(mom_0,targ_mass);	
}

double reverseal_mom_calc(double mom_0,double beam_mass, double targ_mass){
	double beta=reverseal_beta_calc(mom_0,targ_mass);
	return (1/sqrt(1-beta*beta))*(mom_0+beta*get_relE_mom(mom_0,beam_mass));
}

double reverseal_beta_calc_KE(double KE,double beam_mass,double targ_mass){
	return reverseal_beta_calc(momentum_energysplit_CoM(KE,beam_mass,targ_mass),targ_mass);
}

double reverseal_mom_calc_KE(double KE,double beam_mass, double targ_mass){
	return reverseal_mom_calc(momentum_energysplit_CoM(KE,beam_mass,targ_mass),beam_mass,targ_mass);
}

  ////////////////////////////////////////
 ///////// Product Energy Split    //////
////////////////////////////////////////

double momentum_energysplit_CoM(double KE,double Amass,double Bmass){
	double massA=(jam_phys_amu*Amass);
	double massB=(jam_phys_amu*Bmass);
	
	double p=sqrt(KE)*sqrt(2*massB+KE)*sqrt(4*massA*massA+4*massA*massB+4*KE*massA+2*KE*massB+KE*KE);
	p/=sqrt(4*massA*massA+8*massA*massB+8*KE*massA+4*massB*massB+8*KE*massB+4*KE*KE);
	
	return p;
}

double momentum_beam_P_CoM(double mom,double Amass,double Bmass){
	double beta= mom/(get_relE_mom(mom,Amass)+get_relE_mom(0,Bmass));
	return (beta/sqrt(1-beta*beta))*jam_phys_amu*Bmass;	
}

    ///////////////////////////////////////////
   ///////// Product Momentum Split    ///////
  /////////   known trajectories      ///////
 /////////   Momentum conservation   ///////
///////////////////////////////////////////


vector< double > mom_conserve_unit(TVector3 vecZ,TVector3 vecA,TVector3 vecB){
	vector< double > ret(2);
	
	//assumes a perfect plane
	double theta1 = vecZ.Angle(vecA);
	double theta2 = vecZ.Angle(vecB);
	
	//these new lines of code average a bit for imperfect planes
	double tot=abs(vecB.Angle(vecA));
	double fract=theta1/(theta1+theta2);
	theta1=0.5*(theta1+fract*tot);
	theta2=0.5*(theta2+(1-fract)*tot);
	
	ret[0]=1/(TMath::Cos(theta1)+(TMath::Sin(theta1)/TMath::Tan(theta2)));		
	ret[1]=1/(TMath::Cos(theta2)+(TMath::Sin(theta2)/TMath::Tan(theta1)));
	return ret;
}

vector< double > mom_conserve_split(TVector3 vecZ,TVector3 vecA,TVector3 vecB){
	vector< double > ret= mom_conserve_unit(vecZ,vecA,vecB);
	
	double mom=vecZ.Mag();
	ret[0]=ret[0]*mom;
	ret[1]=ret[1]*mom;
	
	return ret;
}

vector< double > mom_conserve_unit(TVector3 vecZ,TVector3 vecA,TVector3 vecB,TVector3 vecC){
	vector< double > ret(3);
	
	double thetaA = vecZ.Angle(vecA);
	double thetaB = vecZ.Angle(vecB);
	double thetaC = vecZ.Angle(vecC);
	TVector3 flatA = vecA-(TMath::Cos(thetaA)*vecA.Mag())*vecZ.Unit();
	TVector3 flatB = vecB-(TMath::Cos(thetaB)*vecB.Mag())*vecZ.Unit();
	TVector3 flatC = vecC-(TMath::Cos(thetaC)*vecC.Mag())*vecZ.Unit();
	double phiA = flatC.Angle(flatA);
	double phiB = flatC.Angle(flatB);

	//length MA=1
	double MB=(TMath::Sin(phiA)*flatA.Mag())/(TMath::Sin(phiB)*flatB.Mag());
	double MC=((flatA+(flatB*MB)).Mag())/(flatC.Mag());
		
	double A=TMath::Cos(thetaA)*vecA.Mag();
	double B=TMath::Cos(thetaB)*vecB.Mag()*MB;
	double C=TMath::Cos(thetaC)*vecC.Mag()*MC;
	
	ret[0]=vecA.Mag()/(A+B+C);
	ret[1]=(vecB.Mag()*MB)/(A+B+C);
	ret[2]=(vecC.Mag()*MC)/(A+B+C);

 	if(ret[0]<0||ret[1]<0||ret[2]<0){ret[0]=0;ret[1]=0;ret[2]=0;}
	
	return ret;
}

vector< double > mom_conserve_split(TVector3 vecZ,TVector3 vecA,TVector3 vecB,TVector3 vecC){
	vector< double > ret= mom_conserve_unit(vecZ,vecA,vecB,vecC);
	
	double mom=vecZ.Mag();
	ret[0]=ret[0]*mom;
	ret[1]=ret[1]*mom;
	ret[2]=ret[2]*mom;
	
	return ret;
}


vector< double > fission_compound_unit(TVector3 compound,TVector3 A,TVector3 B,TVector3 beam){
	vector< double > ret(2);
	alight_to_Z(beam,compound);
	alight_to_Z(beam,A);
	alight_to_Z(beam,B);
	double theta1=A.Theta();
	double theta2=B.Theta();
	double theta5=compound.Theta();
	double phinaught=angledifference(A.Phi(),B.Phi());
	
	double pA1=0;
	double pA2=0;
	double pB1=0;
	double pB2=0;

	double temp_par=2*sin(theta1)*cos(phinaught)*tan(theta2);
	double AAA=1-cos(theta1)*temp_par+(cos2(theta1)*(tan2(theta2)-1));
	double BBB=temp_par-(2*cos(theta1)*tan2(theta2));
	BBB*=cos(theta5);
	double CCC=cos2(theta5)*tan2(theta2)-sin2(theta5);

	if(BBB*BBB>=4*AAA*CCC){
		pA1=(sqrt((BBB*BBB)-(4*AAA*CCC))-BBB)/(2*AAA);
		pA2=(-sqrt((BBB*BBB)-(4*AAA*CCC))-BBB)/(2*AAA);
		pB1=((cos(theta5)/cos(theta2)))-pA1*(cos(theta1)/cos(theta2));
		pB2=((cos(theta5)/cos(theta2)))-pA2*(cos(theta1)/cos(theta2));
		
	}
	
	TVector3 ma=(A.Unit()*pA1+B.Unit()*pB1);
	TVector3 mb=(A.Unit()*pA2+B.Unit()*pB2);
	
	double ca=ma.Unit().Dot(compound.Unit());
	double cb=mb.Unit().Dot(compound.Unit());
	
	if((pA2<=0||pB2<=0||ca>=cb)&&pA1>0&&pB1>0){
		ret[0]=pA1;
		ret[1]=pB1;
	}
		
	if((pA1<=0||pB1<=0||ca<cb)&&pA2>0&&pB2>0){
		ret[0]=pA2;
		ret[1]=pB2;
	}

	return ret;
}

vector< double > fission_compound_split(TVector3 compound,TVector3 A,TVector3 B,TVector3 beam){
	vector< double > ret= fission_compound_unit(compound,A,B,beam);

	double mom=compound.Mag();
	ret[0]=ret[0]*mom;
	ret[1]=ret[1]*mom;
	
	return ret;
}




    ////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////
  /////////////////////// Kinematics cals full integrated ////////////////////
 ////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////
 /////////  Full Reaction Lab      //////
////////////////////////////////////////


//inputs E in MeV, Beam in amu, Target in Amu, lab angle, Recoil A in AMU, recoil B in jam_phys_amu
//give AMU accurately to account for Q value and also excitation can be added into the masses
//returns:
// [0]MA,[1]MB,
// [2]lab_theta_maxA,[3]lab_theta_maxB,
// ---
// [4]lab_thetaA1,[5]lab_thetaB1,
// [6]CoM_thetaA1,[7]CoM_thetaB1,
// [8]lab_PA1,[9]lab_PB1,
// ---
// [10]lab_thetaA2,[11]lab_thetaB2,
// [12]CoM_thetaA2,[13]CoM_thetaB2,
// [14]lab_PA2,[15]lab_PB2,
double* kinetic_lab_calcs_P(double Ebeam,double ABeam,double ATarg,double thetalab,double AA,double AB){
	double* ret= new double[19];
	ret[0]=AA;
	ret[1]=AB;
	ret[4]=thetalab;
	ret[10]=thetalab;
	ret[16]=Ebeam;
	ret[17]=ABeam;
	ret[18]=ATarg;
	
	//calculate the CoM frame properties
	double massA=AA*jam_phys_amu;
	double massB=AB*jam_phys_amu;
	double combeta = get_com_beta(get_rel_mom(Ebeam,ABeam),ABeam,ATarg);
	double comgamma = 1/sqrt(1-(combeta*combeta));
	double bg = combeta*comgamma;
	double bg2 = bg*bg;
	
	double pcm0 = bg*ATarg*jam_phys_amu;
	double pcm1 = pcm0;
	if(!((ABeam==AA)&&(ATarg==AB))) pcm1 = sqrt(((ATarg*ATarg+ABeam*ABeam-AA*AA-AB*AB)*jam_phys_amu*jam_phys_amu + 2*pcm0*pcm0)/2);

	//is there a max angle problem//max lab angle
	bool A=false,B=false;
	if(massA*bg>pcm1)A=true;
	if(massB*bg>pcm1)B=true;
	if(A)ret[2]=TMath::ASin(pcm1/(massA*bg));else ret[2]=TMath::Pi();
	if(B)ret[3]=TMath::ASin(pcm1/(massB*bg));else ret[3]=TMath::Pi();

	//calcs for recoil "AA"
	double E_bg=get_relE_mom(pcm1,AA)*bg;
	   
	double pA=E_bg*TMath::Cos(thetalab);
	double pB=pcm1*pcm1-massA*massA*(TMath::Sin(thetalab)*TMath::Sin(thetalab)*bg2);
	double pC=1+(TMath::Sin(thetalab)*TMath::Sin(thetalab)*bg2);
	if(pB>0)pB=comgamma*sqrt(pB);
	else pB=0;

	//if impossible angle
	if(thetalab>ret[2]&&A){
		ret[5]=0;ret[6]=0;ret[7]=0;ret[8]=0;ret[9]=0;ret[11]=0;ret[12]=0;ret[13]=0;ret[14]=0;ret[15]=0;
	}else{
		ret[8]=(pA+pB)/pC;
		ret[6] = TMath::ACos((ret[8]*TMath::Cos(thetalab)-E_bg)/(pcm1*comgamma));
		ret[7] = TMath::Pi()-ret[6];

		double y=TMath::Sin(ret[7])*pcm1;
		double x=TMath::Cos(ret[7])*pcm1;
		double xpA=comgamma*x+bg*get_relE_mom(pcm1,AB);
		ret[5]=TMath::ATan(y/xpA);
		ret[9]=sqrt(xpA*xpA+y*y);

		//if multisolutions for this lab angle
		if(A){
			ret[14]=(pA-pB)/pC;
			ret[12] = TMath::ACos((ret[14]*TMath::Cos(thetalab)-E_bg)/(pcm1*comgamma));
			ret[13] = TMath::Pi()-ret[12];

			y=TMath::Sin(ret[13])*pcm1;
			x=TMath::Cos(ret[13])*pcm1;
			xpA=comgamma*x+bg*get_relE_mom(pcm1,AB);
			ret[11]=TMath::ATan(y/xpA);
			ret[15]=sqrt(xpA*xpA+y*y);
		}else{
			//ret[14]=ret[8];ret[12]=ret[6];ret[13]=ret[7];ret[11]=ret[5];ret[15]=ret[9];
			ret[14]=0;ret[12]=0;ret[13]=0;ret[11]=0;ret[15]=0;
		}
	}

	return ret;	
}


double* kinetic_lab_calcs_elastic_P(double Ebeam,double AB,double AT,double thetalab){
	return kinetic_lab_calcs_P(Ebeam,AB,AT,thetalab,AB,AT);
}

void kinetic_lab_calcs_readout(double* inp){
	cout<<endl<<endl;
	for(int i=0;i<19;i++){
		cout<<"["<<i<<"] "<<kin_labels[i]<<" : "<<inp[i]<<endl;
	}
}

//inputs E in MeV, Beam in amu, Target in Amu, lab angle Radians, Recoil A in AMU, recoil B in jam_phys_amu
//give AMU accurately to account for Q value and also excitation can be added into the masses
//returns, Energy solution A1, A2, thetamax A, Energy solution B1, B2, thetamax B
double* kinetic_lab_calcs_E(double Ebeam,double AB,double AT,double thetalab,double AC,double AD){
	double* ret=kinetic_lab_calcs_P(Ebeam,AB,AT,thetalab,AC,AD);
	ret[8]=get_KE(ret[8],ret[0]);
	ret[14]=get_KE(ret[14],ret[0]);
	ret[9]=get_KE(ret[9],ret[1]);
	ret[15]=get_KE(ret[15],ret[1]);
	return ret;	

}

double* kinetic_lab_calcs_elastic_E(double Ebeam,double AB,double AT,double thetalab){
	double* ret=kinetic_lab_calcs_E(Ebeam,AB,AT,thetalab,AB,AT);
	return ret;
}


//inputs E in MeV, Beam in amu, Target in Amu, CM angle Radians, Recoil A in AMU, recoil B in jam_phys_amu
//give AMU accurately to account for Q value and also excitation can be added into the masses
//returns, angle_lab A, angle_lab B
double* kinetic_CM_to_lab_angle(double Ebeam,double AB,double AT,double thetaCM,double AC,double AD){
	double* ret= new double[2];
	
	double combeta = get_com_beta(get_rel_mom(Ebeam,AB),AB,AT);
	double comgamma = 1/sqrt(1-(combeta*combeta));
	
	double pcm0 = combeta*comgamma*AT*jam_phys_amu;
	double pcm1 = sqrt(((AT*AT+AB*AB-AC*AC-AD*AD)*jam_phys_amu*jam_phys_amu + 2*pcm0*pcm0)/2);

	double y=TMath::Sin(thetaCM)*pcm1;
	double x=TMath::Cos(thetaCM)*pcm1;

	double EA=get_relE_mom(pcm1,AC);
	double xpA=comgamma*x+combeta*comgamma*EA;
	ret[0]=TMath::ATan(y/xpA);

	double EB=get_relE_mom(pcm1,AD);	
	double xpB=comgamma*x+combeta*comgamma*EB;
	ret[1]=TMath::ATan(y/xpB);

	return ret;	
}


double* kinetic_CM_to_lab_angle_elastic(double Ebeam,double AB,double AT,double thetaCM){
	return kinetic_CM_to_lab_angle(Ebeam,AB,AT,thetaCM,AB,AT);
}

  ////////////////////////////////////////
 /////////    Detector Angles     ///////
////////////////////////////////////////

double* DetectorCoMAngles(double energy,double AB,double AT,double AE,double AR,double lower,double upper){
	//Returns a series of CoM angles corresponsing to the ejectile
	//ret[0,1] Ejectile CoM angle range lower,upper A for ejectile detection
	//ret[2,3] Ejectile CoM angle range lower,upper B for ejectile detection
	//ret[4,5] Ejectile CoM angle range lower,upper A for recoil detection
	//ret[6,7] Ejectile CoM angle range lower,upper B for recoil detection
	//ret[8,9] Ejectile CoM angle range lower,upper A for either detection
	//ret[10,12] Ejectile CoM angle range lower,upper B for either detection
	//ret[12,13] Ejectile CoM angle range lower,upper C for either detection
	//ret[14,15] Ejectile CoM angle range lower,upper D for either detection
	
	
	double u[4],l[4];
	for(int i=0;i<4;i++){u[i]=-1;l[i]=-1;}
	
	higher_jd(lower,upper);//idiot check

	////// Ejectile (beam in elastic) ///////
	// Determine the possible CM angles for a given beam lab angle
	double* ret=kinetic_lab_calcs_P(energy,AB,AT,lower,AE,AR);
	
	if(ret[2]>lower){// ret[2] is the largest lab angle available to the beam, important in inverse kinematics
			// this checks the beam can ever reach the detector, before continuing
		
		l[0]=ret[6];l[1]=ret[12];// Save the two possible CM angles, if there is only one the second will be 0
		if(ret[2]<upper){// check if the beam can cover the whole detector
			u[0]=l[1];l[1]=-1;// in the case where it cannot there will be two CM solutions for lower angle
					  // and the CM range between the two covers the lab angles from lower to max
		}else{
			delete ret; //If it can reach the outer edge then fetch the one or two solutions for the upper in CM
			ret=kinetic_lab_calcs_P(energy,AB,AT,upper,AE,AR);
// 			kinetic_lab_calcs_readout(ret);
			u[0]=ret[6];u[1]=ret[12];// in the case of two u[] and l[] will be correctly paired up as both are given smallest CM angle first by "kinetic_lab_calcs_P"
		}
	}
	delete ret;
	
	
	////// Recoil (target in elastic) ///////
	// Slightly different because we want to check angle of recoil for detection
	// But we want to save the CM angle of ejectile, because that is how the xsec distribution is given
	
	ret=kinetic_lab_calcs_P(energy,AB,AT,lower,AR,AE);;//Switched beam and target on output of the so we can give target angle
	
	if(ret[2]>lower){
		l[2]=ret[7];l[3]=ret[13];// Note different ret[] taken because we ask the CM angle of the opposite particle to the Lab angle input
		if(ret[2]<upper){
			u[2]=l[3];l[3]=-1;
		}else{
			delete ret;
			ret=kinetic_lab_calcs_P(energy,AB,AT,upper,AR,AE);
			u[2]=ret[7];u[3]=ret[13];
		}
	}
	delete ret;
	
	// Convert to degrees
	// Quickly sort the ordering as for a second CM solution the "lower" will have a larger CM angle than the "upper"
	for(int i=0;i<4;i++){
		higher_jd(l[i],u[i]);
	}
	
	////// EITHER ///////
	////// B or T //////
	////// SUM    //////
	
	// This is a little more involved because we dont want to just add the two together as that may double count xsec
	// We need to check for overlap in their CM angular ranges
	
	double su[4],sl[4];
	for(int i=0;i<4;i++){;su[i]=u[i];sl[i]=l[i];} //copy over the range delimiters 

	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){// compare each pair to all above it
			if((su[i]>sl[j])&&(sl[i]<su[j])){// If there is any overlap
				higher_jd(su[i],su[j]);// copy the outer limits to one entry
				higher_jd(sl[j],sl[i]);
				su[i]=-1;// delete the other
				sl[i]=-1;
				j=4;
			}
		}		
	}
	// Now we have dealt with any overlaps
	
	// It is possible any remaining separate ranges are not cm ordered
	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){
			if(sl[j]<sl[i]){
				swap_jd(sl[j],sl[i]);
				swap_jd(su[j],su[i]);
			}
		}
	}
	
	ret=new double[16];
	
	for(int i=0;i<4;i++){
		ret[i*2]=l[i];
		ret[1+i*2]=u[i];
	
		ret[8+i*2]=sl[i];
		ret[9+i*2]=su[i];
	}
	
	return ret;	
}

double* DetectorCoMAnglesElastic(double BeamMeV,double massbeam,double masstarget,double thetamin,double thetamax){
	return DetectorCoMAngles(BeamMeV, massbeam, masstarget,massbeam, masstarget, thetamin, thetamax);
}


  /////////////////////////////////////////////////
 ///////// Lab to CoM single reverse boost    ////
/////////////////////////////////////////////////

double* lab_boost_CMP_query(double combeta, double thetalab,double P_CM,double M_0){
// ret[0] CoM_thetaA1
// ret[1] lab_PA1
// ret[2] CoM_thetaA2
// ret[3] lab_PA2
// ret[4] lab_theta_maxA
	double* ret= new double[5];
	//calculate the CoM frame properties
	double massA=M_0*jam_phys_amu;
	double comgamma = 1/sqrt(1-(combeta*combeta));
	double bg = combeta*comgamma;
	double bg2 = bg*bg;
	
	double pcm1=P_CM; //single particle momentum in back to back CoM 

	//is there a max angle problem//max lab angle
	bool A=false;
	
	if(massA*bg>pcm1)A=true;
	
	if(A)ret[4]=TMath::ASin(pcm1/(massA*bg));else ret[4]=TMath::Pi();

	//calcs for recoil "AA"
	double E_bg=get_relE_mom(pcm1,M_0)*bg;
	double pA=E_bg*TMath::Cos(thetalab);
	double pB=pcm1*pcm1-massA*massA*(TMath::Sin(thetalab)*TMath::Sin(thetalab)*bg2);
	double pC=1+(TMath::Sin(thetalab)*TMath::Sin(thetalab)*bg2);

	if(pB>0)pB=comgamma*sqrt(pB);
	else pB=0;
	
	//if impossible angle
	if(thetalab>ret[4]&&A){
		ret[0]=0;ret[1]=0;ret[2]=0;ret[3]=0;
	}else{
		ret[1]=(pA+pB)/pC;
		ret[0] = TMath::ACos((ret[1]*TMath::Cos(thetalab)-E_bg)/(pcm1*comgamma));

		//if multisolutions for this lab angle
		if(A){
			ret[3]=(pA-pB)/pC;
			ret[2] = TMath::ACos((ret[3]*TMath::Cos(thetalab)-E_bg)/(pcm1*comgamma));
		}else{
			ret[3]=0;ret[2]=0;
		}
	}
	return ret;	
}

    ///////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////
  /////////////////////// Useful Decay Stuff ////////////////////
 ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

double beta_fermi_fn_aprox(double T_MeV,int Z){
	if(Z<=0||T_MeV<=0)return 0;
	
	double a=0.0055465;
	double b=0.076929;
	double a_0=0.40456;
	double b_0=0.073184;	
	if(Z>56){
		a=0.0012277;
		b=0.10122;	
	}
	
	double A=1+a_0*exp(b_0*Z);
	double B=a*Z*exp(b*Z);
	
	if(Z<16)A=0.073*Z+0.94;
		
	return sqrt(A+(B/T_MeV));
	
	//From A simple relation for the Fermi function // 1985 J. Phys. G: Nucl. Phys. 11 359
}

double unnorm_beta_dist_TKE(double T_MeV,double Q,int Z){
	if(Z==0||T_MeV<=0||T_MeV>=Q)return 0;
	
	double p=(T_MeV+0.511);
	p*=p;
	p-=0.511*0.511;
	
	if(Z>0) return p*(Q-T_MeV)*beta_fermi_fn_aprox(T_MeV,Z);
	else return p*(Q-T_MeV)/beta_fermi_fn_aprox(T_MeV,abs(Z));//NOT SURE ABOUT THIS, ONE BOOK SUGGESTED IT
	
}


double K_bind_aprox_keV(int Z){
	if(Z<3)return 0;
	double rydberg_energy=13.61;
	
	return (rydberg_energy/1000)*(Z-2)*(Z-2);
	
	//From Radiation Physics for Medical Physicists By Ervin B. Podgorsak
}


