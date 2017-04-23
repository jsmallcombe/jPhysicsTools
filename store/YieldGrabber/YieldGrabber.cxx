//**********************************************************************************************************************//
// Author: Jack Henderson (TRIUMF) Hacked by James
// jhenderson@triumf.ca
//
// For use with the ROOT framework
//
//**********************************************************************************************************************//

#include "YieldGrabber.h"

void YieldGrabber::ProcessData(){

	vector< std::string > line;
	std::string temp;
	std::string stab_test;
	std::string A_string;

	for(unsigned int i=0;i<data.size();i++){

		line = data.at(i);
		istringstream convert1(line.at(0));
		int z_val;
		if(!(convert1 >> z_val))
			z_val=0;
		temp = line.at(1);
		for(unsigned int j=0;j<temp.size()-1;j++)
			if(isdigit(temp[j]))
				A_string.push_back(temp[j]);

		int state_val;
		if(temp[temp.size()-2] == 'm'){
			state_val = (int)(temp[temp.size()-1] - '0');
			state_val++;
		}
		else
			state_val = 1;

		int a_val;
		istringstream convert2(A_string);
		if(!(convert2 >> a_val))
			a_val=0;
		int n_val = a_val - z_val;

		double d;
		temp = line.at(2);
		istringstream convert3(temp);
		if(!(convert3 >> d))
			d=0;

		istringstream convert4(line.at(3));
		int p_current;
		if(!(convert4 >> p_current))
			p_current=0;

		temp = line.at(4);
		if(temp.compare("Re")==0)
		{
			temp = "Re surface";
		}
		else if(temp.compare("Ta")==0)
		{
			temp = "Ta surface";
		}		
	
		A_string.clear();

		Nuclei[n_val-1][z_val-1].yield.push_back(d);
		Nuclei[n_val-1][z_val-1].proton_current.push_back(p_current);
		Nuclei[n_val-1][z_val-1].ion_source.push_back(temp);
		Nuclei[n_val-1][z_val-1].state.push_back(state_val);	
		Nuclei[n_val-1][z_val-1].tar_mat.push_back(target_mat.at(i));

	}

	line.clear();
	data_grabbed = true;

}

void YieldGrabber::PrintIsotopeInfo(int z_in, int n_in){

	int z = z_in -1;
	int n = n_in -1;

	if(!data_grabbed)
		Start();
	
	PrintMeanIntensity(n_in,z_in);

	int n_states=0;
	for(unsigned int i=0;i<Nuclei[n][z].yield.size();i++){
		if(Nuclei[n][z].state.at(i) > n_states)
			n_states = Nuclei[n][z].state.at(i);
	}

	cout << "Number of states (ground + metastable): " << n_states << endl;
	
	for(int j=0;j<n_states;j++){
		if(j>0)
			cout << "Nucleus: " << z_in+n_in << element[z] << "m" << j << endl;
		else
			cout << "Nucleus: " << z_in+n_in << element[z] << endl;

		cout << "Yield:\t\t\t\tProton current:\t\tTarget:\t\t\tIon source:" << endl;
		for(unsigned int i=0;i<Nuclei[n][z].yield.size();i++){
			if(Nuclei[n][z].state.at(i) == j+1)
				cout << std::setw(10) << std::setprecision(5) << std::scientific << Nuclei[n][z].yield.at(i) << "\t\t\t" << Nuclei[n][z].proton_current.at(i) << "\t\t\t" << Nuclei[n][z].tar_mat.at(i)  << "\t\t\t" << Nuclei[n][z].ion_source.at(i) << endl;
		}
	}
}

void YieldGrabber::GrabData(const char* target){

	char name[64];
	
	strcpy(name,std::getenv("JAMESLIB"));
	strcat(name,"/YieldGrabber/Data/");
	strcat(name,target);
	strcat(name,".dat");

	ifstream infile;
	infile.open(name);
	if(infile.is_open()){

		int i=0;

// 		unsigned int startyields = data.size();

		std::string line;
		while(getline(infile,line))
		{
			std::stringstream linestream(line);

			if(line.length() == 0 )
				continue;

			if(i==0){
				i++;
				continue;	
			}
		
			std::string value;

			while(linestream >> value)
				line_vec.push_back(value);
		
			data.push_back(line_vec);
			target_mat.push_back(target);

			line_vec.clear();

			i++;

		}

		infile.close();
	
	}
	else{
		cout << "File: " << name << " failed to open" << endl;
		return;
	}

}


void YieldGrabber::Start(){

	Clear();

	printf("Loading matrices\n");

	GrabData("SiC");
	GrabData("TiC");
	GrabData("NiO");
	GrabData("ZrC");
	GrabData("Nb");
	GrabData("Ta");
	GrabData("Th");
	GrabData("U");

	cout << "Processing data..." << endl;

	ProcessData();

	cout << "Data processed, " << data.size() << " yields loaded" << endl;

}

void YieldGrabber::PrintMeanIntensity(int N,int Z){

	CreateIntensityMatrix();
	cout << "Average intensity: " << Nuclei[N][Z].avg_yield << endl;

}


YieldGrabber::YieldGrabber()								
{ 
	data_grabbed = false;
	Clear();
	Start();		
} 

void YieldGrabber::Clear() 
{

	data.clear();							
	line_vec.clear();
	target_mat.clear();

	for(int i=0;i<146;i++){
		for(int j=0;j<94;j++){
			Nuclei[i][j].yield.clear();
			Nuclei[i][j].proton_current.clear();
			Nuclei[i][j].ion_source.clear();
			Nuclei[i][j].state.clear();
			Nuclei[i][j].tar_mat.clear();
			Nuclei[i][j].avg_yield = 0;
			Nuclei[i][j].max_yield = 0;
		}
	}

}

void YieldGrabber::CreateIntensityMatrix(int source){

	cout << "Setting up average/maximum yields" << endl;

	double counter;
	double sum;
	double max;

	if(source > 0)
	{

		for(int i=0;i<146;i++){
			for(int j=0;j<94;j++){
				counter = 0;
				sum = 0;
				max = 0;
				Nuclei[i][j].avg_yield=0;
				Nuclei[i][j].max_yield=0;
				for(unsigned int k=0; k<Nuclei[i][j].yield.size(); k++){
					if(IonSourceComparison(Nuclei[i][j].ion_source.at(k)) == source){
						if(Nuclei[i][j].yield.at(k) > max)
							max = Nuclei[i][j].yield.at(k);
						sum = sum + Nuclei[i][j].yield.at(k);
						counter++;
					}
				}
				if(sum>0)
					Nuclei[i][j].avg_yield = (double) (sum/counter);
				Nuclei[i][j].max_yield = max;
			}
		}

	}
	else 
	{

		for(int i=0;i<146;i++){
			for(int j=0;j<94;j++){
				counter = 0;
				sum = 0;
				max = 0;
				Nuclei[i][j].avg_yield=0;
				Nuclei[i][j].max_yield=0;
				for(unsigned int k=0; k<Nuclei[i][j].yield.size(); k++){
					if(Nuclei[i][j].yield.at(k) > max)
						max = Nuclei[i][j].yield.at(k);
					sum = sum + Nuclei[i][j].yield.at(k);
					counter++;
				}
				if(sum > 0)
					Nuclei[i][j].avg_yield = (double) (sum/counter);
				if(max>0)
					Nuclei[i][j].max_yield = max;
			}
		}


	}

}

int YieldGrabber::IonSourceComparison(std::string input){

	if(input.compare("Re surface")==0)
		return 1;
	else if(input.compare("Ta surface")==0)
		return 2;
	else if(input.compare("TRILIS")==0)
		return 3;
	else if(input.compare("IG-LIS")==0)
		return 4;
	else if(input.compare("FEBIAD")==0)
		return 5;
	else
		return 0;
}