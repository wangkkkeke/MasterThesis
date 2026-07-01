#include "Cpuuser.h"
#include "Cpuuser_abstract.h"
#include "Standard_library.h"

CPUUSER Create_cpuuser()
{
    CPUUSER cpuuser = (CPUUSER)malloc(sizeof(CPUUSER_struct));
    if (cpuuser == NULL) return NULL;

    /* framework fields */
    cpuuser->userInputFileName[0] = '\0';
    cpuuser->nuser     = 1;
    cpuuser->nuserstep = 0;
    cpuuser->dusertime = R0;
    cpuuser->duserdt   = R0;

    /* InterfaceBond fields -- all pointers NULL, counts zero */
    cpuuser->nibond    = 0;
    cpuuser->i1ibsphid = NULL;
    cpuuser->i1ibdnid  = NULL;
    cpuuser->d1ibkn    = NULL;
    cpuuser->d1ibkt    = NULL;
    cpuuser->d1ibfnx   = NULL;
    cpuuser->d1ibfny   = NULL;
    cpuuser->d1ibfnz   = NULL;
    cpuuser->d1ibfsx   = NULL;
    cpuuser->d1ibfsy   = NULL;
    cpuuser->d1ibfsz   = NULL;
    cpuuser->i1ibbk    = NULL;

    cpuuser->ibond_kn   = R0;
    cpuuser->ibond_kt   = R0;
    cpuuser->ibond_ft   = R0;
    cpuuser->ibond_fs   = R0;
    cpuuser->ibond_phi  = R0;
    cpuuser->ibond_rcut = R0;

    return cpuuser;
}
