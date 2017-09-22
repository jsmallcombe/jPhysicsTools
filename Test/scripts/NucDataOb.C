{
	
	///////////////////////////////////////////////////////////////////////////
	/////////////////////  Loading Dynamic Data Examples //////////////////////
	///////////////////////////////////////////////////////////////////////////
	
	//This isnt needed, can do all the bellow with nuclear_data_ob:: its just longer
	//In fact creating a new object clears the classes static data
	nuclear_data_ob NOb;
	
// 	NOb.add_data_live("/home/jsmallcombe/Dropbox/codes/mini_apps/data_viewer/data/0_2.txt",1,1,20);
	
	//Load a whole bunch of hardcoded data into the dynamic data set
// 	NOb.add_data_live(NOb.get_L0_2,"0_2",0,2);
	NOb.add_data_live(NOb.get_rho_sq,"rho_sq",1,2,20);
	NOb.add_data_live(NOb.get_mass_table,"Mass",2,1,20);
	
	//Add some dynamic data using the NucDatumSpecifier class
	class NucDatumSpecifier nuc;
	nuc.oddZ=1;nuc.oddN=1;
	nuc.cPJ=2;nuc.cPP=1;
	nuc.cPN=1;nuc.cPT=1;
	NOb.AddENSDFdatum(&nuc);
	nuc.cPJ=4;
	NOb.AddENSDFdatum(&nuc);
	nuc.cPJ=0;nuc.cPN=2;nuc.cColour=2;
	NOb.AddENSDFdatum(&nuc);

	NOb.add_data_live((string)gSystem->pwd()+"/Test/data/favouritenuclei.txt",2,2,3);
			
	//Print the current dynamic data
	NOb.print_data_live();
	
	// Show the environment for seeing dynamic data
	// And GUI for adding data by click selection
	new LiveDataSlicer();
// 	new LiveDataSlicer(NOb.S2n);
// 	NOb.set_data_live(2);new LiveDataSlicer(NOb.data_live);
	
	
	///////////////////////////////////////////////////////////////////////////
	/////////////////////    GPad Energy Examples     //////////////////////
	///////////////////////////////////////////////////////////////////////////
	
// 	TCanvas *si = new TCanvas("si", "Energy Scan Example Electrons",12,187,700,502);
// 	sili->DrawCopy();
// 	
// 	PadScanData::AddElectronData("Pd",110,2,2000);
// 	PadScanData::AddElectronData("Cd",112,2,2000);
// 	PadScanData::Draw(si);
// 	gPad->Update();
	
	

// 	TCanvas *ge = new TCanvas("ge", "Energy Scan Example Gammas",12,187,700,502);
// // 	PadScanData::AddData(46,110,0,3000);
// // 	PadScanData::LoadFile((string)gSystem->pwd()+"/Test/data/gammapadinfo.txt");
// 	gammas->DrawCopy();
// 	PadScanData::Draw();

	
	///////////////////////////////////////////////////////////////////////////
	////////////////////    TH2 Data Drawing Example     //////////////////////
	///////////////////////////////////////////////////////////////////////////
	
// 	TH2F *hpxpy=NOb.hist_data_live(2);
// 
// 	TCanvas *c3 = new TCanvas("c3", "Magic Numbers Example",12,187,700,502);
// 	hpxpy->DrawCopy("colz");
//  	NOb.addmagic(c3,1);
// 	
// 	TCanvas *c4 = new TCanvas("c4", "Magic Numbers Zoom Example",12,187,700,502);
// 	hpxpy->GetXaxis()->SetRange(40,180);
// 	hpxpy->GetYaxis()->SetRange(12,102);	
// 	hpxpy->DrawCopy("colz");
//  	NOb.addmagic(c4,1);	
// 	
// 	TCanvas *c1 = new TCanvas("c1", "Lego Example",12,187,700,502);
// 	hpxpy->DrawCopy("lego2 0");
// 	
// 	TCanvas *c2 = new TCanvas("c2", "Lego Magic Example",12,187,700,502);
// 	NOb.addmagic(hpxpy);
// 	hpxpy->DrawCopy("lego2 0");

	///////////////////////////////////////////////////////////////////////////
	////////////////////         Text Data Example     //////////////////////
	///////////////////////////////////////////////////////////////////////////
	
// 	cout<<endl<<"Live Data #2 "<<NOb.get_name_data_live(2)<<" For "<<NOb.channelname(NOb.get_Z("Sm"),154)<<" = "<<NOb.get_data_live(2,62,154)<<endl;
// 	
// 	cout<<"mass_excess "<<NOb.get_mass_excess(62,154)<<endl;
// 	cout<<"get_nom_density "<<NOb.get_nom_density(62)<<endl;
// 	cout<<"S2n "<<NOb.S2n(62,154)<<endl;
// 	cout<<"Qbeta_p "<<NOb.Qbeta_p(62,154)<<endl;
	
	
	//////////////////////////////////////////////////////////////////////////////////
	/////////////         Text Text Load Will clear all live data     /////////////////
	//////////////////////////////////////////////////////////////////////////////////
	
	nuclear_data_ob::readall_data_live()
}
