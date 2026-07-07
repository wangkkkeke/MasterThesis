#include "Cpuuser.h"
#include "Cpuuser_abstract.h"
#include "InterfaceBond/ibond_types.h"
#include "InterfaceBond/ibond_benchmark.h"
#include "Standard_library.h"

CPUUSER Create_cpuuser()
{
    CPUUSER u;
    FILE *log = fopen("user_solver_loaded.txt", "w");
    if (log != NULL)
    {
        fprintf(log, "Create_cpuuser called\n");
        fclose(log);
    }

    u = (CPUUSER)malloc(sizeof(CPUUSER_struct));
    if (u == NULL) return NULL;

    memset(u, 0, sizeof(CPUUSER_struct));

    u->nuser     = 1;
    u->nuserstep = 0;
    u->dusertime = R0;
    u->duserdt   = R0;

    u->ibond_level = 0;
    u->ibond_verify_case = 0;
    ibond_mgr_init(&u->ibond_mgr);
    ibond_config_mock(u);

    return u;
}
