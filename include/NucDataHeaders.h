private:
static double beta[128][256];
static bool beta_set;
static double density_gcm3[256];
static bool density_gcm3_set;
static double element_mass[256];
static bool element_mass_set;
static double Kbinding[256];
static bool Kbinding_set;
static double L0_2[128][256];
static bool L0_2_set;
static double L0_3[128][256];
static bool L0_3_set;
static double L2_1[128][256];
static bool L2_1_set;
static double L2_2[128][256];
static bool L2_2_set;
static double L2_3[128][256];
static bool L2_3_set;
static double L3_1[128][256];
static bool L3_1_set;
static double L4_1[128][256];
static bool L4_1_set;
static double L4_2[128][256];
static bool L4_2_set;
static double L4_3[128][256];
static bool L4_3_set;
static double Lbinding[256];
static bool Lbinding_set;
static double lifetime[128][256];
static bool lifetime_set;
static double mass_table[128][256];
static bool mass_table_set;
static double Mbinding[256];
static bool Mbinding_set;
static double q_sq[128][256];
static bool q_sq_set;
static double rho_sq[128][256];
static bool rho_sq_set;
public:
//Returns beta [Inputs(Z,N)]
static double get_beta(int,int);

//Returns density_gcm3 [Inputs(Z)]
static double get_density_gcm3(int);

//Returns element_mass [Inputs(Z)]
static double get_element_mass(int);

//Returns Kbinding [Inputs(Z)]
static double get_Kbinding(int);

//Returns L0_2 [Inputs(Z,N)]
static double get_L0_2(int,int);

//Returns L0_3 [Inputs(Z,N)]
static double get_L0_3(int,int);

//Returns L2_1 [Inputs(Z,N)]
static double get_L2_1(int,int);

//Returns L2_2 [Inputs(Z,N)]
static double get_L2_2(int,int);

//Returns L2_3 [Inputs(Z,N)]
static double get_L2_3(int,int);

//Returns L3_1 [Inputs(Z,N)]
static double get_L3_1(int,int);

//Returns L4_1 [Inputs(Z,N)]
static double get_L4_1(int,int);

//Returns L4_2 [Inputs(Z,N)]
static double get_L4_2(int,int);

//Returns L4_3 [Inputs(Z,N)]
static double get_L4_3(int,int);

//Returns Lbinding [Inputs(Z)]
static double get_Lbinding(int);

//Returns lifetime [Inputs(Z,N)]
static double get_lifetime(int,int);

//Returns mass_table [Inputs(Z,N)]
static double get_mass_table(int,int);

//Returns Mbinding [Inputs(Z)]
static double get_Mbinding(int);

//Returns q_sq [Inputs(Z,N)]
static double get_q_sq(int,int);

//Returns rho_sq [Inputs(Z,N)]
static double get_rho_sq(int,int);

