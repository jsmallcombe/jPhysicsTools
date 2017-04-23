//
//
//	James Root Library
//	Relativistic Kinematics and other physics functions
//	05 Mar 2017
//	james.smallcombe@outlook.com
//
//

#ifndef jamesphysics_h
#define jamesphysics_h

#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include <TObjArray.h>
#include <TMath.h>

#include <TLorentzVector.h>
#include <TVector3.h>

#include "james_root_maths.h"
#include "james_nuclear_data_ob.h"

using namespace std;


  /////////////////////////////////////////
 ////////// Functionallity Tools ///////// 
/////////////////////////////////////////

// Returns a shinney new TLorentzVector Ep-4vec [Inputs(P_vector (MeV/c), A_0 (amu))]
TLorentzVector make_lorentzvec(TVector3,double);

// Frame rotation to frame where vec_1=(0,0,1) [Inputs(Master_vector,Vector_to_change)]
// Leaves vec_1 unchanged
// (Change beam LAST and only IF needed)
void alight_to_Z(TVector3,TVector3&);


  //////////////////////////////////////////////
 ////////// Nuclear Data Calculations ///////// 
//////////////////////////////////////////////

// Returns nominal radius in (fm) [Inputs(A)]
double classical_radius(double);

// Returns coulomb barrier (MeV) [Inputs(A1,Z1,A2,Z2,gap[fm])]
double classical_barrier(double,double,double,double,double=0);	

// Returns colulex safe distance of closest approach in fm [Inputs(A1,A2,switch)]
double safe_r(double,double,int=0);	

// Returns expected fission TKE (MeV) [Inputs(Compound_A,Compound_Z)]
double viola_TKE(double,double);

// Returns fission TKE from deformation neck calculation (MeV) [Inputs(Frag1_A,Frag1_Z,Frag2_A,Frag2_Z)]
double neck_TKE_manea(double,double,double,double);


// Return the maximum CM beam scattering angle for safe coulex distance of approach, given beam energy lab
double safe_coulex_angle(double,double,double,double,double); //[Inputs(A1,Z1,A2,Z2,E_lab)]

// Returns the maximum beam energy for safe coulex distance of approach for a given CM beam scattering angle
double safe_coulex_beam(double,double,double,double,double); //[Inputs(A1,Z1,A2,Z2,rad_cm)]

// Returns angle at which ruthford scattering uncleam (rad) [Inputs(A1,Z1,A2,Z2,E_cm)]
double happy_ruth_theta(double,double,double,double,double);

// Returns integrated 2pi rutherford_crosssection in mb [Inputs(Z1,Z2,E_cm,thetamin_cm,thetamax_cm)]
double rutherford_crosssection(double,double,double,double,double);

  ///////////////////////////////////////////////////////////////
 ////////// Single Body Relativistic E & P calculators   ///////
///////////////////////////////////////////////////////////////

// Returns total E relativistic [Inputs(P_frame (MeV/c), Mass_0 (amu))]
double get_relE_mom(double,double);

// Returns total E relativistic [Inputs(KE (MeV), Mass_0 (amu))]
double get_relE_KE(double,double);

// Returns P relativistic in current frame [Inputs(KE_frame (MeV), Mass_0 (amu), Print (TRUE/FALSE))]
double get_rel_mom(double,double,bool=false);

// Returns KE in current frame [Inputs(P_frame (MeV/c), Mass_0 (amu), Print (TRUE/FALSE))]
double get_KE(double,double,bool=false);

// Extract KE in current frame from TLorentzVector [Inputs(TLorentzVector*)]    Ep 4-vec in MeV
double get_KE(TLorentzVector*);


   //////////////////////////////////////////////////////
  ////////// Beta and Gamma calculators          ///////
 ////////// single particle in frame velocities /////// 
////////////////////////////////////////////////////// 

// Returns Gamma of single particle in frame [Inputs(KE_frame (MeV), Mass_0 (amu))]
double get_gamma_KE(double,double);

// Returns Gamma of single particle in frame [Inputs(P_frame (MeV/c), Mass_0 (amu))]
double get_gamma_mom(double,double);

// Returns Beta of single particle in frame [Inputs(KE_frame (MeV), Mass_0 (amu))]
double get_beta_KE(double,double);

// Returns Beta of single particle in frame [Inputs(P_frame (MeV/c), Mass_0 (amu))]
double get_beta_mom(double,double);

//Extract Beta of single particle in frame from TLorentzVector [Inputs(TLorentzVector*)]    Ep 4-vec in MeV
double get_beta(TLorentzVector);

// Returns vector with magniude Beta [Inputs(P vector (MeV/c), Mass_0 (amu))]
TVector3 get_beta_vec(TVector3,double);

// Returns vector with magniude Beta [Inputs(TLorentzVector*)]    Ep 4-vec in MeV
TVector3 get_beta_vec(TLorentzVector);

inline double get_gamma(double& beta){return 1/sqrt(1-beta*beta);}
inline double get_beta(double& gamma){return sqrt(1-(1/(gamma*gamma)));}

     ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////
   /////////////////////// Centre of Mass Calculations ///////////////////
  ///////////////////////    (Zero Momentum Frame)    ///////////////////
 ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

  ////////////////////////////////////
 ///////// Total KE in CoM    ///////
//////////////////////////////////// 

// Returns Total KE in CoM for beam + target [Inputs(P_beam (MeV/c), Mass_beam (amu), Mass_target (amu))]
double get_com_KE(double,double,double);

// Returns Total KE in CoM from P vectors [Inputs(P_vector_1 (MeV/c), Mass_1 (amu), P_vector_2 (MeV/c), Mass_2 (amu))]
double get_com_KE(TVector3,double,TVector3,double);

// Returns Total KE in CoM from 2 TLorentzVectors [Inputs(TLorentzVector,TLorentzVector)]    Ep 4-vec in MeV
double get_com_KE(TLorentzVector ,TLorentzVector );

   ////////////////////////////////////
  ///////// Velocity of CoM    ///////
 /////////   (Boost beta)     ///////
//////////////////////////////////// 

// Returns Beta OF the CoM for beam + target [Inputs(P_beam (MeV/c), Mass_beam (amu), Mass_target (amu))]
double get_com_beta(double,double,double);

// Returns Beta OF the CoM from P vectors [Inputs(P_vector_1 (MeV/c), Mass_1 (amu), P_vector_2 (MeV/c), Mass_2 (amu))]
double get_com_beta(TVector3,double,TVector3,double);

// Returns Beta_vector OF the CoM from P vectors [Inputs(P_vector_1 (MeV/c), Mass_1 (amu), P_vector_2 (MeV/c), Mass_2 (amu))]
TVector3 get_com_beta_vec(TVector3,double,TVector3,double);

// Returns Beta_vector OF the CoM from THREE P vectors [Inputs(P_vector_1 (MeV/c), Mass_1 (amu), P_vector_2 (MeV/c), Mass_2 (amu), P_vector_3 (MeV/c), Mass_3 (amu))]
TVector3 get_com_beta_vec(TVector3,double,TVector3,double,TVector3, double);

// Returns Beta OF the CoM from 2 TLorentzVectors [Inputs(TLorentzVector,TLorentzVector)]   Ep 4-vec in MeV
double get_com_beta(TLorentzVector ,TLorentzVector );

// Returns Beta_vector OF the CoM from TLorentzVectors [Inputs(TLorentzVector,TLorentzVector)]   Ep 4-vec in MeV
TVector3 get_com_beta_vec(TLorentzVector ,TLorentzVector );

// Returns Beta_vector OF the CoM from THREE TLorentzVectors [Inputs(TLorentzVector,TLorentzVector,TLorentzVector)]   Ep 4-vec in MeV
TVector3 get_com_beta_vec(TLorentzVector ,TLorentzVector ,TLorentzVector );

  ///////////////////////////////////
 ///////// CoM -> Beam cals   //////
///////////////////////////////////

//Returns CoM beta, given the in CoM momentum  [Inputs(P_CoM (MeV/c), targ_mass (amu))]
double reverseal_beta_calc(double,double);

//Returns beam momentum, given the in CoM momentum [Inputs(P_CoM (MeV/c), beam_mass (amu), targ_mass (amu))]
double reverseal_mom_calc(double,double,double);

//Returns CoM beta, given the in CoM KE_tot  [Inputs(KE_tot (MeV), beam_mass (amu), targ_mass (amu))]
double reverseal_beta_calc_KE(double,double,double);

//Returns beam momentum, given the in CoM KE_tot [Inputs(KE_tot (MeV), beam_mass (amu), targ_mass (amu))]
double reverseal_mom_calc_KE(double,double,double);

  ////////////////////////////////////////
 ///////// Product Energy Split    //////
////////////////////////////////////////

// Returns momentum P_1=P_2 for CoM sharing of released energy [Inputs(Energy Released/KE (MeV), Mass_1 (amu), Mass_2 (amu))]
double momentum_energysplit_CoM(double,double,double);

// Returns momentum P_1=P_2 for CoM for beam + target [Inputs(P_beam (MeV/c), Mass_beam (amu), Mass_target (amu))]
double momentum_beam_P_CoM(double,double,double);

    ///////////////////////////////////////////
   ///////// Product Momentum Split    ///////
  /////////   known trajectories      ///////
 /////////   Momentum conservation   ///////
///////////////////////////////////////////


// Returns P given trajectories using P conservation [Inputs(P_vec_beam (MeV/c), vec_1, vec_2)]
// Assumes a perfect 3 vector plane.
vector< double > mom_conserve_split(TVector3,TVector3,TVector3 );
// Returns fractions of P_0
vector< double > mom_conserve_unit(TVector3,TVector3,TVector3 );

// Returns P given trajectories using P conservation [Inputs(P_vec_beam (MeV/c), vec_1, vec_2, vec_3)]
// Directions must be accurate for good result as assumes perfect
vector< double > mom_conserve_split(TVector3,TVector3,TVector3,TVector3 );
// Returns fractions of P_0
vector< double > mom_conserve_unit(TVector3,TVector3,TVector3,TVector3 );

// For reactions of the type A + B -> Compound* + D -> FF_1 + FF_2 + D
// Good when phi is poorly known, but unreliable.
// [Inputs(P_vec_compound (MeV/c), Vec_FF1, Vec_FF2, vec_beam)]
vector< double > fission_compound_split(TVector3,TVector3,TVector3,TVector3=TVector3(0,0,1));
// Returns fractions of P_0
vector< double > fission_compound_unit(TVector3,TVector3,TVector3,TVector3=TVector3(0,0,1));



    ////////////////////////////////////////////////////////////////////////////
   ////////////////////////////////////////////////////////////////////////////
  /////////////////////// Kinematics cals full integrated ////////////////////
 ////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


  ////////////////////////////////////////
 /////////  Full Reaction Lab      //////
////////////////////////////////////////

// Full computation of reaction products with specified final angles in LAB frame
// Must use actual mass WITH excess adjusted to get correct result i.e. Qval
// For excitation increase mass of products
// Returns angles, momenta and masses (for full list see kin_labels[] or use kinetic_lab_calcs_readout()).
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), Lab_angle_ejectile (radians), Mass_ejectile (amu), Mass_recoil (amu))]
double* kinetic_lab_calcs_P(double,double,double,double,double,double);
// Elastic scattering
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), Lab_angle_ejectile (radians))]
double* kinetic_lab_calcs_elastic_P(double,double,double,double);

//Use to print to terminal kinetic_lab_calcs_P outputs
void kinetic_lab_calcs_readout(double*);
const string kin_labels[] = {"Mass_A","Mass_B","Theta_max_A","Theta_max_B","Theta_A_Lab0","Theta_B_Lab1","Theta_A_CoM1","Theta_B_CoM1","PE_Lab_A1","PE_Lab_B1","Theta_A_Lab0","Theta_B_Lab2","Theta_A_CoM2","Theta_B_CoM2","PE_Lab_A2","PE_Lab_B2","E_beam","Mass_Beam","Mass_Targ"}; // all const

// Returns angles, energies and masse
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), Lab_angle_ejectile (radians), Mass_ejectile (amu), Mass_recoil (amu))]
double* kinetic_lab_calcs_E(double,double,double,double,double,double);
// Elastic scattering
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), Lab_angle_beam (radians))]
double* kinetic_lab_calcs_elastic_E(double,double,double,double);


  ////////////////////////////////////////
 /////////    Full Reaction CoM   ///////
////////////////////////////////////////

// Full computation but simple readout, uses CM angle
// Must use actual mass WITH excess adjusted to get correct result i.e. Qval
// For excitation increase mass of products
// Returns LAB angles or ejectile and recoil
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), CM_angle_ejectile (radians), Mass_ejectile (amu), Mass_recoil (amu))]
double* kinetic_CM_to_lab_angle(double,double,double,double,double,double);
// Elastic scattering
// [Inputs(Ebeam (MeV), Mass_beam (amu), Mass_targ (amu), CM_angle_beam (radians))]
double* kinetic_CM_to_lab_angle_elastic(double,double,double,double);


  /////////////////////////////////////////////////
 ///////// Lab to CoM single reverse boost    ////
/////////////////////////////////////////////////

// Calc possible CoM angles for given lab IF CoM known
// Returns 2 CoM angles and 2 P_lab and theta_lab_max (2 solutions NOT 2 particles)
// [Inputs(Beta_CoM, Theta_lab (radians), P_CoM (MeV/c), Mass_0 (amu))]
double* lab_boost_CMP_query(double,double,double,double);
// ret[0] CoM_thetaA1
// ret[1] lab_PA1
// ret[2] CoM_thetaA2
// ret[3] lab_PA2
// ret[4] lab_theta_maxA

    ///////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////
  /////////////////////// Useful Decay Stuff ////////////////////
 ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


double beta_fermi_fn_aprox(double,int);
double unnorm_beta_dist_TKE(double,double,int);

double K_bind_aprox_keV(int);




#endif
