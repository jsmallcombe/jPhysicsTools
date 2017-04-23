#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main(int argc, char * argv[]){
	
	if(argc<1)return 0;
	
	ofstream headers_one,headers_two,headers_three,headers_four,headers_five;
	headers_one.open("NucDataOb/autohead/data_headers.h");
	headers_two.open("NucDataOb/autohead/data_init.h");
	headers_three.open("NucDataOb/autohead/data_data.h");
	headers_four.open("NucDataOb/autohead/function_declarations.h");
	headers_five.open("NucDataOb/autohead/function_definitions.h");

	
	for(int i=1;i<=argc;i++){
		stringstream in_name;
		in_name<<argv[i];
		string filename=in_name.str();
		ifstream infile;
		ofstream outfile;
		
		
		if(filename.find(".txt")==filename.size()-4){
			string name=filename.substr(filename.find("input")+6);
			name=name.substr(0,name.find(".txt"));
			
			infile.open((filename).c_str());
			if(infile.is_open())outfile.open(("NucDataOb/autohead/"+name+".h").c_str());
			
			if(outfile.is_open()){
				
				int switch2d=0;
				string str;
				
				while(getline(infile, str, '\n')){
		
					vector<double> input;
					stringstream ss;
					ss << str;
					double trans;
					while(ss >> trans) input.push_back(trans);
					
					if(switch2d==0){
						switch2d=1;
						if(input.size()>2)switch2d=2;
					}

					if(input.size()>switch2d){
						int x=input[0],y=input[1];
						if(switch2d==2){
							if(x>=0&&x<128&&y>=0&&y<256)
							//outfile<<"nuclear_data_ob::"<<name<<"["<<x<<"]["<<y<<"]="<<input[2]<<";"<<endl;
							outfile<<" "<<name<<"["<<x<<"]["<<y<<"]="<<input[2]<<";"<<endl;
						}else{
							if(x>=0&&x<256)
							//outfile<<"nuclear_data_ob::"<<name<<"["<<x<<"]="<<input[1]<<";"<<endl;
							outfile<<" "<<name<<"["<<x<<"]="<<input[1]<<";"<<endl;
						}
					}
				}
				outfile.close();
				infile.close();
								
				if(switch2d==2) headers_one<<"static double "<<name<<"[128][256];"<<endl;
				else headers_one<<"static double "<<name<<"[256];"<<endl;
				
				headers_one<<"static bool "<<name<<"_set;"<<endl;
				
				if(switch2d==2) headers_two<<"double nuclear_data_ob::"<<name<<"[128][256]={{0}};"<<endl;
				else headers_two<<"double nuclear_data_ob::"<<name<<"[256]={0};"<<endl;
				
				headers_three<<"#include \"NucDataOb/autohead/"<<name<<".h\""<<endl;
				
				
				//Create the header and body data for automatic get_data functions
			
				if(switch2d==2){
					headers_four<<"//Returns "<<name<<" [Inputs(Z,N)]"<<endl;
					headers_four<<"static double get_"<<name<<"(int,int);"<<endl<<endl;
				}else{
					headers_four<<"//Returns "<<name<<" [Inputs(Z)]"<<endl;
					headers_four<<"static double get_"<<name<<"(int);"<<endl<<endl;
				}
			
				headers_five<<"double nuclear_data_ob::get_"<<name<<"(int z";
				if(switch2d==2){
					headers_five<<",int a){"<<endl;
					headers_five<<"if(general_reader(z,a)) return "<<name<<"[z][a-z];"<<endl;
				}else{
					headers_five<<"){"<<endl;
					headers_five<<"if(general_reader(z)) return "<<name<<"[z];"<<endl;
				}
				headers_five<<"return 0;}"<<endl<<endl;
			}
		}
	}
	
	headers_one.close();
	headers_two.close();
	headers_three.close();
	headers_four.close();
	headers_five.close();
	return 0;
}


