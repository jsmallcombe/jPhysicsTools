double nuclear_data_ob::get_beta(int z,int a){
if(general_reader(z,a)) return beta[z][a-z];
return 0;}

double nuclear_data_ob::get_density_gcm3(int z){
if(general_reader(z)) return density_gcm3[z];
return 0;}

double nuclear_data_ob::get_element_mass(int z){
if(general_reader(z)) return element_mass[z];
return 0;}

double nuclear_data_ob::get_Kbinding(int z){
if(general_reader(z)) return Kbinding[z];
return 0;}

double nuclear_data_ob::get_L0_2(int z,int a){
if(general_reader(z,a)) return L0_2[z][a-z];
return 0;}

double nuclear_data_ob::get_L0_3(int z,int a){
if(general_reader(z,a)) return L0_3[z][a-z];
return 0;}

double nuclear_data_ob::get_L2_1(int z,int a){
if(general_reader(z,a)) return L2_1[z][a-z];
return 0;}

double nuclear_data_ob::get_L2_2(int z,int a){
if(general_reader(z,a)) return L2_2[z][a-z];
return 0;}

double nuclear_data_ob::get_L2_3(int z,int a){
if(general_reader(z,a)) return L2_3[z][a-z];
return 0;}

double nuclear_data_ob::get_L3_1(int z,int a){
if(general_reader(z,a)) return L3_1[z][a-z];
return 0;}

double nuclear_data_ob::get_L4_1(int z,int a){
if(general_reader(z,a)) return L4_1[z][a-z];
return 0;}

double nuclear_data_ob::get_L4_2(int z,int a){
if(general_reader(z,a)) return L4_2[z][a-z];
return 0;}

double nuclear_data_ob::get_L4_3(int z,int a){
if(general_reader(z,a)) return L4_3[z][a-z];
return 0;}

double nuclear_data_ob::get_Lbinding(int z){
if(general_reader(z)) return Lbinding[z];
return 0;}

double nuclear_data_ob::get_lifetime(int z,int a){
if(general_reader(z,a)) return lifetime[z][a-z];
return 0;}

double nuclear_data_ob::get_mass_table(int z,int a){
if(general_reader(z,a)) return mass_table[z][a-z];
return 0;}

double nuclear_data_ob::get_Mbinding(int z){
if(general_reader(z)) return Mbinding[z];
return 0;}

double nuclear_data_ob::get_q_sq(int z,int a){
if(general_reader(z,a)) return q_sq[z][a-z];
return 0;}

double nuclear_data_ob::get_rho_sq(int z,int a){
if(general_reader(z,a)) return rho_sq[z][a-z];
return 0;}

