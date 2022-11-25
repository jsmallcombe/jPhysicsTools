#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

#include "jphysmaster.h"


using namespace::std;
int main(int argc, const char * arg[]){
	if(argc>4){
		stringstream s1,s2,s3,s4;
		s1<<arg[1];
		s2<<arg[2];
		s3<<arg[3];
		s4<<arg[4];
        
        int AB,Z1,AT,Z2;
        
        s1>>AB;
        s2>>Z1;
        s3>>AT;
        s4>>Z2;
        
        cout << safe_coulex_beam(AB,Z1,AT,Z2);
        
    }
	return 0;
}

