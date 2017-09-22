{ 
	draw_hist_inset((TH1*)sili->Clone(),(TH1*)gammas->Clone());
	TCanvas* EY_A=draw_electron_gamma((TH1*)sili->Clone(),(TH1*)gammas->Clone());
	TCanvas* EY_B=draw_electron_gamma((TH1*)sili->Clone(),(TH1*)gammas->Clone());
	AddElectronGammaLabels(EY_A,570,"Pd");
	AddElectronGammaLabels(EY_B,400,800,570,"Pd","4_{1}^{+}#rightarrow2_{1}^{+}");
	
// 	AddPeakLabel(400);
// 	AddPeakLabel(540,bob->cd(1),"",0,false,bob->cd(2));
// 	AddPeakLabel(bob,590)	
		
	TCanvas* can=new TCanvas();
	sili->GetXaxis()->SetRangeUser(400,800);
	sili->Draw();
	AddElectronLabel(570,"Pd");
	
}
