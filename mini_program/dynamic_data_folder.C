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
	nuclear_data_ob bob;

	TSystemDirectory system("",gSystem->pwd());
	TList *l=system.GetListOfFiles();
	if(l){
// 		l->Print();
		TIter next(l);
		TObject* obj;
		while ((obj=next())){
			if(string(obj->ClassName())=="TSystemFile"){
				TSystemFile* file=(TSystemFile*)obj;
				bob.add_data_live(string(file->GetName()));
			}	
		}
		delete l;
	}
	
	if(bob.size_data_live()>0){
		for(uint i=0;i<bob.size_data_live();i++){
			uint t=0,c=0,m=0;
			cout<<endl<<bob.get_name_data_live(i)<<" Type:"<<flush;
			cin>>t;
			if(t<3){
				cout<<" Colour:"<<flush;
				cin>>c;
				cout<<" Marker:"<<flush;
				cin>>m;
			}
			bob.format_data_live(i,t,c,m);
		}
			
		bob.print_data_live();
		
		TApplication *app = new TApplication("app", &argc, argv);
			LiveDataSlicer* slice=new LiveDataSlicer();
			slice->Connect("TCanvas", "Closed()", "TApplication", gApplication, "Terminate()");
		app->Run();		
	}
	return 0;
};

