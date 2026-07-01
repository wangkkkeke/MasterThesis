#include "Cpucore.h"
#include "Cpuuser_abstract.h"
#include "Cpuuser.h"
#include <stdio.h>

/* Forward declaration -- defined in ibond_init.c */
void ibond_identify(CPUCORE cpucore, CPUUSER cpuuser);

void user_solver(CPUCORE cpucore, CPUUSER cpuuser)
{
    /* Issue003: one-time Bond identification on first call.
     * MultiFracS calls user_solver directly (not via solve_for_user),
     * so this is the earliest point we have CPUCORE access.
     * Not fully thread-safe: acceptable for single-setup explicit dynamics. */
    static int s_ibond_init = 0;
    if (!s_ibond_init)
    {
        s_ibond_init = 1;
        ibond_identify(cpucore, cpuuser);
    }

    /* Issue001 diagnostic: print once per ~1000 calls */
    static int s_call = 0;
    s_call++;
    if (s_call % 1000 == 1)
    {
        printf("[User_solver] call=%d  nibond=%d  nfn=%d  ndn=%d  nsph=%d\n",
               s_call, cpuuser->nibond,
               cpucore->nfn, cpucore->ndn, cpucore->nsph);
    }

    /* InterfaceBond force calculation (Issue005) */
}

void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser)
{
    /* InterfaceBond force write-back to FEM nodes (Issue006) */
}
