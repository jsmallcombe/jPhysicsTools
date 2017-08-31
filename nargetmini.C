extern "C" {
	#include <dedx.h>
}


using namespace::std;
int main(int argc, const char * arg[]){
	
	dedx_workspace *ws;
	dedx_config *cfg;
	int err;
	int datasets=1;
	ws = dedx_allocate_workspace(datasets, &err);
	
	return 0;
}
