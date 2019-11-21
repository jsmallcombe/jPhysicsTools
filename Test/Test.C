{
string dir=gSystem->pwd();	
string load=dir+"/bin/libjroot_phys.so";
dir=".x "+dir+"/Test";

//load the library	
gROOT->ProcessLine(".include ./include");
gSystem->Load(load.c_str());

//load some 1D histograms
gROOT->ProcessLine((dir+"/data/1Dhist.C").c_str());

//Pick a script by commenting
  dir+="/scripts/legenedre_spherical_manual.C";
//  dir+="/scripts/narget.C";
// dir+="/scripts/NucDataOb.C";
// dir+="/scripts/HistFormat.C";
// dir+="/scripts/GammaRayTest.C";

//Run that script
gROOT->ProcessLine(dir.c_str());
}
