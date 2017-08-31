{
   TH1D* hist=new TH1D("hist","hist",8000,0,2000);
   for(int i=1;i<=hist->GetNbinsX();i++)hist->SetBinContent(i,589);

   //Alpha gated 110Pd
//    GenGeResponse(373.866,hist,2191630);
//    GenGeResponse(398.725,hist,161218);
//    GenGeResponse(439.919,hist,490444);
//    GenGeResponse(547.211,hist,761943);
//    
   //207Bi source
	GenGeResponse(1070,hist);
	GenGeResponse(570,hist); 
   
	ApplyGeEff(hist);
	hist->SetMinimum(1);
	TCanvas* can=new TCanvas();
	hist->Draw("logy");
	can->SetLogy();
	
}
