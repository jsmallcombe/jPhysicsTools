#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "jphysmaster.h"


using namespace::std;
int main(int argc, const char * arg[]){
	if(argc>1){
		stringstream ss;
		ss<<arg[1];
        int z;
        ss>>z;
        cout<<nuclear_data_ob::get_symb(z)<<endl;
	}
	return 0;
}

