#include "Cpucore.h"
#include "Cpuuser_abstract.h"
#include "Cpuuser.h"
#include "InterfaceBond/ibond_types.h"
#include "InterfaceBond/ibond_benchmark.h"
#include <stdio.h>

void user_solver(CPUCORE cpucore, CPUUSER cpuuser)
{
    static int s_ibond_done = 0;
    static int s_call = 0;
    int vc;

    s_call++;

    if (!s_ibond_done)
    {
        if (cpucore == NULL || cpucore->nfn <= 0)
            return;

        vc = cpuuser->ibond_verify_case;

        printf("[User_solver] first call: nfn=%d ndn=%d nsph=%d ibond_rcut=%.6f verify_case=%d\n",
               cpucore->nfn, cpucore->ndn, cpucore->nsph,
               (double)cpuuser->ibond_rcut, vc);

        if (ibond_benchmark_is_active(cpuuser) && vc == 0)
        {
            ibond_identify(cpucore, cpuuser);
            if (cpuuser->bench1_test_id == 0 || cpuuser->bench1_test_id == 2)
            {
                ibond_benchmark_write_setup_log(cpucore, cpuuser);
                ibond_benchmark_write_log(cpucore, cpuuser);
                ibond_benchmark_write_vtk(cpucore, cpuuser);
                printf("[User_solver] Benchmark-%d Step-1: identify only, nibond=%d\n",
                       cpuuser->bench_kind, cpuuser->nibond);
                s_ibond_done = 1;
                return;
            }

            if (cpuuser->nibond > 0)
                ibond_compute_forces(cpucore, cpuuser);
            ibond_benchmark_write_log(cpucore, cpuuser);
            ibond_benchmark_write_vtk(cpucore, cpuuser);
            printf("[User_solver] Benchmark-%d Step-2: compute only, nibond=%d\n",
                   cpuuser->bench_kind, cpuuser->nibond);
            s_ibond_done = 1;
            return;
        }

        if (vc == 20)
        {
            ibond_provider_probe(cpucore, cpuuser);
            printf("[User_solver] Case L: probe only, nibond=%d\n", cpuuser->nibond);
            s_ibond_done = 1;
            return;
        }

        ibond_identify(cpucore, cpuuser);

        if (vc == 21)
        {
            printf("[User_solver] Case M: identify only, nibond=%d\n", cpuuser->nibond);
            s_ibond_done = 1;
            return;
        }

        if (vc == 22)
        {
            if (cpuuser->nibond > 0)
                ibond_compute_forces(cpucore, cpuuser);
            ibond_provider_log_bond_force(cpucore, cpuuser);
            printf("[User_solver] Case N: compute+log only, nibond=%d\n", cpuuser->nibond);
            s_ibond_done = 1;
            return;
        }

        if (vc == 23)
        {
            printf("[User_solver] Case O: identify done, nibond=%d (apply on next calls)\n",
                   cpuuser->nibond);
            if (cpuuser->nibond <= 0)
                ibond_provider_log_apply(cpucore, cpuuser);
            s_ibond_done = 1;
            return;
        }

        if (vc == 8)
        {
            printf("[User_solver] Case H: second Identify()\n");
            ibond_identify(cpucore, cpuuser);
            printf("[User_solver] Case H: nibond=%d (expect 3, not 6)\n", cpuuser->nibond);
        }

        if (vc == 6 || vc == 7)
        {
            printf("[User_solver] Case %c: RemoveBond(1)\n", (vc == 6) ? 'F' : 'G');
            ibond_mgr_remove_bond(&cpuuser->ibond_mgr, 1);
            ibond_sync_nibond(cpuuser);
            printf("[User_solver] after remove: nibond=%d\n", cpuuser->nibond);
        }

        if (vc == 7)
        {
            printf("[User_solver] Case G: Re-Identify()\n");
            ibond_identify(cpucore, cpuuser);
            printf("[User_solver] Case G: nibond=%d\n", cpuuser->nibond);
        }

        s_ibond_done = 1;
        return;
    }

    if (ibond_benchmark_is_active(cpuuser))
        return;

    if (cpuuser->nibond > 0 &&
        cpuuser->ibond_verify_case != 21 &&
        cpuuser->ibond_verify_case != 22)
    {
        ibond_compute_forces(cpucore, cpuuser);
        ibond_apply_forces(cpucore, cpuuser);
    }

    if (s_call == 1000 || s_call == 10000)
        printf("[User_solver] call=%d nibond=%d nfn=%d nsph=%d\n",
               s_call, cpuuser->nibond, cpucore->nfn, cpucore->nsph);
}

void user_to_MultiFracS(CPUCORE cpucore, CPUUSER cpuuser)
{
    static volatile int s_export_guard = 1;
    if (s_export_guard && cpucore != NULL && cpuuser != NULL)
        (void)cpuuser->nibond;
}
