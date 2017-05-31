#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "jphysmaster.h"


using namespace::std;
int main(int argc, const char * arg[]){
	if(argc>1){
		stringstream ss;
		ss<<arg[1];
        cout<<nuclear_data_ob::get_Z(ss.str())<<endl;
	}
	return 0;
}

