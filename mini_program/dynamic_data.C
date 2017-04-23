#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TList.h>
#include <TObject.h>
#include <TApplication.h>

#include "jlibmaster.h"

using namespace::std;
int main(int argc, char *argv[]){
	TApplication *app = new TApplication("app", &argc, argv);
		LiveDataSlicer* live=new LiveDataSlicer();
// 		LiveDataSlicer(nuclear_data_ob::get_mass_table);
		live->ReDrawMagic();

		live->Connect("Destroyed()", "TApplication", app, "Terminate()");
	app->Run();		

	return 0;
};

