//Draw all m values separately for a give L
//Compare 2 methods for calculation
//S = 0 draw associate polynomials 
//S = 1 draw spherical harmonics 
void draw_leg(int L,int S=0){

	string title="associate polynomials";
	if(S>0){
		S=1;
		title="spherical harmonics";
	}
	else S=0;
	
	bool divid=true;

	int fin=2;
	
	spherical_harmonic sphe(L);
	
	legendre_polynomials leg(L);

	for(int k=0;k<2;k++){
		TCanvas* divplot=new TCanvas();
		divplot->Divide(L*2+1);
		divid=(!divid);
		
		if(divid)divplot->SetTitle((title+" method ratio").c_str());
		else divplot->SetTitle((title+" method overlay").c_str());
		
		int m=-L;
		for(int l=1;l<=L*2+1;l++){
			TGraph bob,bill;
			
			for(int i=0;i<1000;i++){
				double theta=pi*(double)i/1000.0;
				
				if(S==0){// associate polynomials 
					double y=0;
					double x=cos(theta);
					if(L==1){
						if(m==1)y=-sqrt(1-x*x);
						if(m==0)y=x;	
						if(m==-1)y=0.5*sqrt(1-x*x);
					}			
					if(L==2){
						if(m==2)y=3*(1-x*x);	
						if(m==1)y=-3*x*sqrt(1-x*x);	
						if(m==0)y=0.5*(3*x*x-1);	
						if(m==-1)y=0.5*x*sqrt(1-x*x);;	
						if(m==-2)y=0.125*(1-x*x);	
					}			
					if(L==3){
						if(m==3)y=-15*sqrt(1-x*x)*(1-x*x);
						if(m==2)y=15*x*(1-x*x);
						if(m==1)y=-1.5*sqrt(1-x*x)*(5*x*x-1);
						if(m==0)y=0.5*(5*x*x*x-3*x);
						if(m==-1)y=0.125*sqrt(1-x*x)*(5*x*x-1);
						if(m==-2)y=0.125*x*(1-x*x);
						if(m==-3)y=(15.0/720.0)*sqrt(1-x*x)*(1-x*x);
					}			
					if(L==4){
						if(m==4)y=105*(1-x*x)*(1-x*x);
						if(m==3)y=-105*x*(1-x*x)*sqrt(1-x*x);
						if(m==2)y=7.5*(7*x*x-1)*(1-x*x);
						if(m==1)y=-2.5*(7*x*x*x-3*x)*sqrt(1-x*x);
						if(m==0)y=0.125*(35*x*x*x*x-30*x*x+3);
						if(m==-1)y=0.125*(7*x*x*x-3*x)*sqrt(1-x*x);
						if(m==-2)y=(15.0/720.0)*(7*x*x-1)*(1-x*x);
						if(m==-3)y=(105./5040.)*x*(1-x*x)*sqrt(1-x*x);
						if(m==-4)y=(105./40320.)*(1-x*x)*(1-x*x);
					}
					if(divid){
						if(y!=0)bob.SetPoint(bob.GetN(),theta,leg.eval_associated(m,x)/y);
					}else{
						bob.SetPoint(bob.GetN(),theta,leg.eval_associated(m,x));
						bill.SetPoint(bill.GetN(),theta,y);
					}
				}
				
				if(S==1){// spherical harmonics
					double y=0;
					double x=theta;
					if(L==1){
						if(m==1)y=-0.5*sqrt(3/(2*pi))*sin(x);
						if(m==0)y=0.5*sqrt(3/(pi))*cos(x);	
						if(m==-1)y=0.5*sqrt(3/(2*pi))*sin(x);
					}			
					if(L==2){
						if(m==2)y=0.25*sqrt(15/(2*pi))*sin(x)*sin(x);	
						if(m==1)y=-0.5*sqrt(15/(2*pi))*cos(x)*sin(x);
						if(m==0)y=0.25*sqrt(5/(pi))*(3*cos(x)*cos(x)-1);
						if(m==-1)y=0.5*sqrt(15/(2*pi))*cos(x)*sin(x);	
						if(m==-2)y=0.25*sqrt(15/(2*pi))*sin(x)*sin(x);
					}			
					if(L==3){
						if(m==3)y=-0.125*sqrt(35/pi)*sin(x)*sin(x)*sin(x);
						if(m==2)y=0.25*sqrt(105/(2*pi))*sin(x)*sin(x)*cos(x);
						if(m==1)y-=0.125*sqrt(21/(pi))*sin(x)*(5*cos(x)*cos(x)-1);
						if(m==0)y=0.25*sqrt(7/(pi))*(5*cos(x)*cos(x)*cos(x)-3*cos(x));
						if(m==-1)y=0.125*sqrt(21/(pi))*sin(x)*(5*cos(x)*cos(x)-1);
						if(m==-2)y=0.25*sqrt(105/(2*pi))*sin(x)*sin(x)*cos(x);
						if(m==-3)y=0.125*sqrt(35/pi)*sin(x)*sin(x)*sin(x);
					}			
					if(L==4){
						if(m==4)y=(3./16.)*sqrt(35/(2*pi))*sin(x)*sin(x)*sin(x)*sin(x);
						if(m==3)y=-0.375*sqrt(35/(pi))*sin(x)*sin(x)*sin(x)*cos(x);
						if(m==2)y=0.375*sqrt(5/(2*pi))*sin(x)*sin(x)*(7*cos(x)*cos(x)-1);
						if(m==1)y=-0.375*sqrt(5/(pi))*sin(x)*(7*cos(x)*cos(x)*cos(x)-3*cos(x));
						if(m==0)y=(3./16.)*sqrt(1/(pi))*(35*cos(x)*cos(x)*cos(x)*cos(x)-30*cos(x)*cos(x)+3);
						if(m==-1)y=0.375*sqrt(5/(pi))*sin(x)*(7*cos(x)*cos(x)*cos(x)-3*cos(x));
						if(m==-2)y=0.375*sqrt(5/(2*pi))*sin(x)*sin(x)*(7*cos(x)*cos(x)-1);
						if(m==-3)y=0.375*sqrt(35/(pi))*sin(x)*sin(x)*sin(x)*cos(x);
						if(m==-4)y=(3./16.)*sqrt(35/(2*pi))*sin(x)*sin(x)*sin(x)*sin(x); 
					}
					if(divid){
						if(y!=0)bob.SetPoint(bob.GetN(),theta,sphe.modsq(m,x)/(y*y));
					}else{
						bob.SetPoint(bob.GetN(),theta,sphe.modsq(m,x));
						bill.SetPoint(bill.GetN(),theta,(y*y));
					}
				}				
			}
			
			divplot->cd(l);
			gPad->Update();
			bob.SetLineColor(2);
			stringstream ss;
			ss<<"L = "<<L<<" m = "<<m;
			bob.SetTitle(ss.str().c_str());
			bob.DrawClone("AL");
			if(!divid)bill.DrawClone("SAMEL");
			
			m++;
		}
		if(L>4)k=2;
	}
}

// Draw the pure lm distributions for all values of m
// Draw the 2 panels lm spherical harmonics and lm gamma distributions
// Note: gamma distributions are functions of Ylm Ylm-1 and Ylm+1 so not directly comparable
void draw_seper_leg(int L){
	spherical_harmonic sphe(L);
	
	for(int k=0;k<2;k++){
		TCanvas* divplot=new TCanvas();
		divplot->Divide((2*L)+1);
		if(k==0)divplot->SetTitle("sphe");else divplot->SetTitle("gamma");
		cout<<endl;
		for(int M=-L;M<=L;M++){
				
			TGraph bob;
			
			for(int i=0;i<1000;i++){
				double theta=pi*(double)i/1000.0;
				double x=cos(theta);
				double A=0;
				if(k==0)A+=sphe.modsq(M,x);
				else A+=sphe.gamma_Z(M,x);
				bob.SetPoint(bob.GetN(),theta,A);
			}
			
			double integral=0;
			for(int i=0;i<1000;i++){
				double theta=pi*(double)i/1000.0;
				integral+=bob.Eval(theta);
// 				integral+=sin(theta)*bob.Eval(theta);
			}			
			cout<<"m = "<<M<<"     "<<integral<<endl;
			
			divplot->cd(M+L+1);
			gPad->Update();
			bob.SetLineColor(2);
			stringstream ss;
			ss<<"L = "<<L<<" m = "<<M;
			bob.SetTitle(ss.str().c_str());
			bob.DrawClone("AL");
		}
	}
}

// Draw the sum of progressive sum of lm distributions from -m to +m
// Draw the 2 panels spherical harmonics and gamma distributions
// Note: gamma distributions are functions of Ylm Ylm-1 and Ylm+1 so not directly comparable
void draw_step_leg(int L){
	spherical_harmonic sphe(L);
	
	for(int k=0;k<2;k++){
		TCanvas* divplot=new TCanvas();
		divplot->Divide(2*L);
		if(k==0)divplot->SetTitle("sphe");else divplot->SetTitle("gamma");
	
		for(int M=-L+1;M<=L;M++){
				
			TGraph bob,bill;
			
			for(int i=0;i<1000;i++){
				double A=0,B=0;
				double theta=pi*(double)i/1000.0;
				double x=cos(theta);	
				for(int m=-L;m<=M;m++){
					if(k==0)A+=sphe.modsq(m,x);
					else A+=sphe.gamma_Z(m,x);
					if(m==M-1)B=A;
				}
				bob.SetPoint(bob.GetN(),theta,A);
				bill.SetPoint(bill.GetN(),theta,B);	
			}
			
			divplot->cd(M+L);
			gPad->Update();
			bob.SetLineColor(2);
			bob.SetMinimum(0);
			bob.DrawClone("AL");
			bill.DrawClone("SAMEL");
		}
	}
}



//Draw gamma ray distributions for all transitions J=ini -> |J-L| ... |J+L|
//Draw 2 sets for initial sigma_m = 0.01 and 15 (around 0)
void draw_gamma(int L,int ini){
	
	int fin_min=abs(ini-L);
	int fin_max=ini+L;
	int N=fin_max-fin_min+1;
	
	gamma_dist distA,distB;
	distA.set_gamma_L(L);
	distA.set_alignment(ini,0.01);
	distB.set_gamma_L(L);
	distB.set_alignment(ini,15);
	
	TCanvas* divplot=new TCanvas();
	if(N>1)divplot->Divide(N);
	int p=1;
	for(int fin=fin_min;fin<=fin_max;fin++){
			
		TGraph bob,bill;
		for(int i=0;i<1000;i++){
			double theta=pi*(double)i/1000.0;
			bob.SetPoint(bob.GetN(),theta,distA.simplified_gamma_dist(fin,theta));
			bill.SetPoint(bill.GetN(),theta,distB.simplified_gamma_dist(fin,theta));
		}	
			
		stringstream ss;
		ss<<"J="<<L<<" "<<ini<<"->"<<fin;
	if(N>1)	divplot->cd(p);
		gPad->Update();
		bob.SetLineColor(2);
		bob.SetTitle(ss.str().c_str());
		bob.DrawClone("AL");
		bill.DrawClone("SAMEL");
		cout<<endl<<fin<<" "<<p;
		p++;
	}
}

// strange thing described in title
// basically shows contribution of last m for sum over all m for different l
void draw_sum_leg(int L_max){	
	for(int k=0;k<2;k++){
	TCanvas* divplot=new TCanvas();
	divplot->Divide(L_max);
	if(k==0)divplot->SetTitle("sphe");else divplot->SetTitle("gamma");
		for(int L=1;L<=L_max;L++){
			
			spherical_harmonic sphe(L);
			TGraph bob,bill;
			
			for(int i=0;i<1000;i++){
				double A=0,B=0;
				double theta=pi*(double)i/1000.0;
				double x=cos(theta);	
				for(int m=-L;m<=L;m++){
					if(k==0)A+=sphe.modsq(m,x);
					else A+=sphe.gamma_Z(m,x);
					if(m==L-1)B=A;
				}
				bob.SetPoint(bob.GetN(),theta,B);
				bill.SetPoint(bill.GetN(),theta,A);	
			}
			
			stringstream ss;
			ss<<"L = "<<L<<"#sum^{m=L-1}_{m=-L}";
			if(k==0)ss<<" |Y_{ml}(#theta)|^{2}";
			else ss<<" Z_{ml}(#theta)";
		
			divplot->cd(L);
			gPad->Update();
			bob.SetTitle(ss.str().c_str());
			bob.SetLineColor(2);
			bob.SetMaximum(1);
			bob.SetMinimum(0);
			bob.DrawClone("AL");
			bill.DrawClone("SAMEL");
		}
	}
}


void legenedre_spherical_manual(){
	//Do stuff
}


//Draw gamma ray distributions for mixed E2,M1
void draw_E2M1(int ini,int fin,double delta=0.5,double sigma=0.01){

	
	if(abs(ini-fin)>1)return;
	if(ini+fin<2)return;
	
	gamma_dist distA,distB;
	distA.set_gamma_L(2);
	distA.set_alignment(ini,sigma);
	distB.set_gamma_L(1);
	distB.set_alignment(ini,sigma);
		
	//Seems distribution from simplified_gamma_dist isnt normalised? ...
	double sumA=0,sumB=0;
	for(int i=0;i<1000;i++){
		double theta=pi*(double)i/1000.0;
		sumA+=distA.simplified_gamma_dist(fin,theta)*sin(theta);
		sumB+=distB.simplified_gamma_dist(fin,theta)*sin(theta);
	}	
	
	double M=1./(1+delta*delta);
	double E=1-M;
	
	
	TGraph bob,bill;
	for(int i=1;i<1000;i++){
		double theta=pi*(double)i/1000.0;
		
		double Edis=distA.simplified_gamma_dist(fin,theta);
		double Mdis=distB.simplified_gamma_dist(fin,theta);
		
		double sumdist=(Edis*E/sumA)+(Mdis*M/sumB);
		double ratio=sumdist/(Edis/sumA);
		
	
		bob.SetPoint(bob.GetN(),theta,sumdist);
		bill.SetPoint(bill.GetN(),theta,ratio);
	}		
	
		stringstream ss;
		ss<<ini<<"->"<<fin<<" #delta(E2/M1)="<<delta<<" #sigma_{m}="<<sigma;
		bob.SetTitle(ss.str().c_str());
		bill.SetTitle("W_{#gamma}(#delta)/W_{#gamma}(E2)");
		
		TCanvas* divplot=new TCanvas();
		divplot->Divide(2);
		divplot->cd(1);
		gPad->Update();
		bob.DrawClone("AL");
		divplot->cd(2);
		gPad->Update();
		bill.SetMinimum(0);
		bill.DrawClone("AL");

// 	}
}

