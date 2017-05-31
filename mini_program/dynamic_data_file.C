#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TList.h>
#include <TObject.h>
#include <TApplication.h>


#include "jphysmaster.h"

using namespace::std;
int main(int argc, char *argv[]){
	
	string file="Data.txt";
	
	for(int i=1;i<argc;i++){
		stringstream ss;
		ss<<argv[i];
		ifstream testfile(ss.str());
		if(testfile.is_open()){
			file=ss.str();
			testfile.close();
			break;
		}
	}

	nuclear_data_ob::readall_data_live(file);

		
	int dummy=1;
	TApplication *app = new TApplication("app", &dummy, argv);
		LiveDataSlicer* slice=new LiveDataSlicer();
		slice->Connect("TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");
	app->Run();		
	
	return 0;
};

