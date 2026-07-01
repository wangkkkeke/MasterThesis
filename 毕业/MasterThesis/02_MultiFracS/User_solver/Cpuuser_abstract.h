#include "Cpucore.h"

typedef struct CPUUSER_struct* CPUUSER;
typedef struct CPUUSER_struct CPUUSER_struct;
USERDLL CPUUSER Create_cpuuser();
USERDLL void solve_user(CPUCORE cpucore, CPUUSER cpuuser);
USERDLL void Output_mointor_history_user(CPUUSER cpuuser, int nhstep);
USERDLL void Output_vtk_user(CPUUSER cpuuser, long long nhstep);
USERDLL void preprocess_cpuuser(CPUUSER cpuuser, char* userfilename);
USERDLL void user_solver(CPUCORE cpucore, CPUUSER cpuuser);
USERDLL void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser);
