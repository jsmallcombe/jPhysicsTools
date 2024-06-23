#include "j_legendre.h"


long j_int_fac(long i){
	if(i==0)return 1;
	if(i<0)return 0;
	long ret=i;
	while(i>1){
		i--;
		ret*=i;			
	}
	return ret;
}

////////////////////////////////////////////////////////////////////////////////	
////////////////////////legendre_polynomials///////////////////////////
///////////////////////////////////////////////////////////////////////////////
	
legendre_polynomials::legendre_polynomials(int L) : l(abs(L)),poly_hold(),poly(){
	
	poly_hold.push_back(1);
	for(int i=0;i<l;i++)this->legen_internal(1);
	for(int i=0;i<l;i++)this->int_poly_diff();
	poly.push_back(poly_hold);//base legendre_polynomial (also m=0)
	
	vector< int > poly0 =poly_hold;
	
	for(int i=1;i<=l;i++){//does the m's of associated polynomails 
		poly_hold=poly0;
		for(int j=0;j<i;j++)this->int_poly_diff();
		for(int j=1;j<=i/2.0;j++)this->legen_internal(-1);//^(m/2) term, do the even ones here and add the halves on later
		poly.push_back(poly_hold);
	}
	
	int deno =(1 << l)*j_int_fac(l);
	tfac = 1.0/deno;

}
	
legendre_polynomials::legendre_polynomials( const legendre_polynomials &obj){
	l=obj.l;poly=obj.poly;tfac=obj.tfac;poly_hold=obj.poly_hold;
}

legendre_polynomials& legendre_polynomials::operator=( const legendre_polynomials &obj){
	if(this!=&obj){//to prevent self-assignment errors
		l=obj.l;poly=obj.poly;tfac=obj.tfac;poly_hold=obj.poly_hold;
	}
	return (*this); // for cascading assignment
}
double legendre_polynomials::eval(double x){
	return this->eval_associated(0,x);
}

double legendre_polynomials::eval_associated(int M,double x){
	int m=abs(M);
	if(m>l) return 0;
	
	bool odd_m=false;
	if((m%2)!=0)odd_m=true;
	
	double ret=poly[m][0];
	for(int j=1;(unsigned)j<poly[m].size();j++) ret+=poly[m][j]*pow(x,j);
	
	ret*=tfac;
	if(odd_m)ret*=-sqrt(abs(1-x*x));
	if(M<0){
		if(odd_m)ret=-ret;
		ret*=j_int_fac(l+M);
		ret/=j_int_fac(l-M);
	}
	return ret;
}

void legendre_polynomials::legen_internal(int rev){
	//rev=+1 poly * (X^2 - 1)
	//rev=-1 poly * (1 -X^2)
	
		poly_hold.push_back(0);
		poly_hold.push_back(0);		
		int N=poly_hold.size();

		for(int j=N-1;j>1;j--){
			poly_hold[j]=rev*poly_hold[j-2]-rev*poly_hold[j];
		}
		poly_hold[0]=-rev*poly_hold[0];
		poly_hold[1]=-rev*poly_hold[1];
}
	
void legendre_polynomials::int_poly_diff(){
		int N=poly_hold.size();
		for(int j=0;j+1<N;j++){
			poly_hold[j]=poly_hold[j+1]*(j+1);
		}
		poly_hold[N-1]=0;
}

////////////////////////////////////////////////////////////////////////////////	
////////////////////////spherical_harmonic///////////////////////////
///////////////////////////////////////////////////////////////////////////////

spherical_harmonic::spherical_harmonic(int L) : l(abs(L)),tfac(),poly(abs(L)){
	for(int i=-l;i<=l;i++){
		double t=((2*l+1)/(4*pi))*(j_int_fac(abs(l-i))/(double)j_int_fac(abs(l+i)));
		tfac.push_back(sqrt(abs(t)));
	}
}	

double spherical_harmonic::core(int &m,double &theta){
	if(abs(m)>l)return 0;
	
// 	if(m>0)cout<<gsl_sf_legendre_sphPlm((int)l,(int)abs(m),cos(theta))/(poly.eval_associated(m,cos(theta))*tfac[m+l])<<" "<<flush;
	
	return gsl_sf_legendre_sphPlm((int)l,(int)abs(m),cos(theta));
	
	return poly.eval_associated(m,cos(theta))*tfac[m+l];
}

double spherical_harmonic::real(int m,double theta,double phi){
	return this->core(m,theta)*cos(m*phi);
}

double spherical_harmonic::imaginary(int m,double theta,double phi){
	return this->core(m,theta)*sin(m*phi);
}

double spherical_harmonic::modsq(int m,double theta,double phi){
	double ret=this->core(m,theta);
	return ret*ret;
}


double spherical_harmonic::gamma_Z(int m,double theta){
	if(abs(m)>l)return 0;	
	
	// This gives the square of the VECTOR spherical harmonics i.e. the gamma distribution	
	double ret=0;
	for(int i=-l;i<=l;i++){
		for(int k=-1;k<=1;k++){
			double C=clebschgordancoefficients(l,1,i,k,l,m);
			if(C!=0){
				double x=this->core(i,theta)*C;
				ret+=x*x;	
			}
		}
	}
	
	return ret;
}


////////////////////////////////////////////////////////////////////////////////	
////////////////////////gamma_dist///////////////////////////
///////////////////////////////////////////////////////////////////////////////

gamma_dist::gamma_dist(int L) : J1(0),J2(0),alighnment(),sphe(0){
    if(L>0)sphe = new spherical_harmonic(L);
}

void gamma_dist::set_gamma_L(int L){
    if(sphe)delete sphe;
    if(L>0)sphe = new spherical_harmonic(L);
}	

void gamma_dist::set_alignment(double I,double sigma){
    alighnment.clear();
    J1=abs(I);
    if(!jhic(I))J1=abs(round(I));
     double a=0;
    for(double i=-J1;i<=J1;i++)a+=exp(-abs(i)/abs(sigma));
    for(double i=-J1;i<=J1;i++){
      if(sigma<0) alighnment.push_back(1/(2*J1+1));
	else alighnment.push_back((exp(-abs(i)/abs(sigma)))/a);
    }
}

double gamma_dist::simplified_gamma_dist(double I,double theta){	
	J2=abs(I);
	if(!jhic(I))J2=abs(round(I));
	if(sphe){
		double ret=0;
		int L=sphe->get_l();
		
		for(double i=-J1;i<=J1;i++){
			for(double j=-J2;j<=J2;j++){
				for(double k=-L;k<=L;k++){
					double xx=clebschgordancoefficients(J1,J2,i,j,L,k);					
					if(xx!=0){
						xx*=xx;
						xx*=alighnment[i+J1];
						xx*=sphe->gamma_Z(k,theta);
						ret+=xx;
					}
				}
			}
		}
		return ret;
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////	
/////////////////////  Clebsch-Gordan coefficients  /////////////////////////	
////////////////////////////////////////////////////////////////////////////////	


double clebschgordancoefficients(double j1,double j2,double m1, double m2, double j, double m){
	//http://www.lajpe.org/jan10/15_Michael_Caola.pdf
	
// 	if((m1+m2)!=m || abs(m1)>j1 || abs(m2)>j2 || abs(j1-j2)>j || (j1+j2)<j) return 0;
// 
// 	if(!(jhic(j1)&&jhic(j2)&&jhic(m1)&&jhic(m2)&&jhic(j)&&jhic(m)))return 0;
// 	
// 	double sum=0;
// 	long r=-2*j;
// 	
// 	
// 	
// 	while(r<2*j){
// 		
// 		long deno=1;
// 		deno*=j_int_fac(r)*j_int_fac(j1+j2-j-r)*j_int_fac(j1+m1-r)*j_int_fac(j-j1+m2+r);
// 		deno*=j_int_fac(j-m1-j2+r)*j_int_fac(j2-m2-r);
// 		
// 		if(deno>0){
// 			long nume=j_int_fac(j+m)*j_int_fac(j-m)*j_int_fac(j1+m1)*j_int_fac(j1-m1)*j_int_fac(j2+m2)*j_int_fac(j2-m2);
// 			
// 			if(((long)(r+j1+j2-j))%2==0){
// 				sum+=(sqrt(nume)/deno);
// 			}else{
// 				sum-=(sqrt(nume)/deno);
// 			}			
// 		}
// 		r++;
// 	}
// 	
// 	double front=(2*j+1)*j_int_fac(j1-j2+j)*j_int_fac(j2-j1+j)*j_int_fac(j1+j2-j);
// 	front/=(double)j_int_fac(j1+j2+j+1);
	
// 	return sqrt(front)*sum;	
	


	return WignerSymbols::clebschGordan(j1,j2,j,m1,m2,m);
	
}

bool jhic(double in){
	if(round(in*2)-(in*2)!=0)return false;
	return true;	
}

double clebsch_print(double j1,double j2,double m1, double m2, double j, double m){
	
	if(!(jhic(j1)&&jhic(j2)&&jhic(m1)&&jhic(m2)&&jhic(j)&&jhic(m))){
		cout<<endl<<"One or more non half integer input"<<endl;
		return 0;
	}
	
	if((m1+m2)!=m){
		cout<<endl<<"m1+m2 != M   "<<m1<<"+"<<m2<<"!="<<m<< endl;
		return 0;
	}
		
	
	if(abs(m1)>j1){
		cout<<endl<<"|m1|>j1   |"<<m1<<"|>"<<j1<< endl;
		return 0;
	}
	
	if(abs(m2)>j2){
		cout<<endl<<"|m2|>j2   |"<<m2<<"|>"<<j2<< endl;
		return 0;
	}			
		
	if(abs(j1-j2)>j || (j1+j2)<j){
		cout<<endl<<"|j1-j2|<=J<=j1+j2 fail   |"<<j1<<"-"<<j2<<"|<="<<j<<"<="<<j1<<"+"<<j2<<endl;
		return 0;
	}	
	
	double C=clebschgordancoefficients(j1,j2,m1,m2,j,m);
	
	double CS=C*C;
	int nume;
	int deno;
	double best=1.0;
	
	for(int i=1;i<1000;i++){
		double val=CS*i;
		double test=abs(val-round(val));
		if(test<best){
			best=test;
			deno=i;
			nume=round(val);
		}
		if(test==0.0)break;		
	}
	
	cout<<endl<<"Clebsch ("<<j1<<" "<<j2<<","<<m1<<" "<<m2<<"|"<<j<<" "<<m<<") = "<<C;
	if(C!=0&&C!=1){
		cout<<" = ";
		if(C<0)cout<<"-";
		cout<<"("<<nume<<"/"<<deno<<")^0.5";
	}
	cout<<endl;
	return C;
}



