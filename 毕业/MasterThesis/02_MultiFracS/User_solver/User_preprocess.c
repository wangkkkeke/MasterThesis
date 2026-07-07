#include "Cpuuser.h"

#include "Cpuuser_abstract.h"

#include "Cpucore.h"

#include "InterfaceBond/ibond_types.h"
#include "InterfaceBond/ibond_benchmark.h"

#include "Standard_library.h"



/* Read *InterfaceBond section from a text file.

 * Format (one line after keyword):

 *   Kn, Kt, ft, fs, phi, rcut

 * Returns 1 if *InterfaceBond was found and parsed, else 0.

 */

static int read_ibond_parameters(CPUUSER cpuuser, const char *filename)

{

    FILE *fp = fopen(filename, "r");

    char line[256];

    int found = 0;



    if (fp == NULL)

        return 0;



    while (fgets(line, sizeof(line), fp) != NULL)

    {

        if (strncmp(line, "*InterfaceBond", 14) == 0)

        {

            if (fgets(line, sizeof(line), fp) != NULL)

            {

                sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf",

                       &cpuuser->ibond_kn,

                       &cpuuser->ibond_kt,

                       &cpuuser->ibond_ft,

                       &cpuuser->ibond_fs,

                       &cpuuser->ibond_phi,

                       &cpuuser->ibond_rcut);

                found = 1;

            }

            break;

        }

    }

    fclose(fp);

    return found;

}



/* Derive inp path from user path: foo.user -> foo.inp */

static void make_inp_fallback_name(const char *userfilename, char *out, int outlen)

{

    int i, len, dot;



    strncpy(out, userfilename, outlen - 1);

    out[outlen - 1] = '\0';



    len = (int)strlen(out);

    dot = -1;

    for (i = len - 1; i >= 0; i--)

    {

        if (out[i] == '.')

        {

            dot = i;

            break;

        }

    }

    if (dot >= 0 && (len - dot) <= 6)

        strcpy(out + dot, ".inp");

    else if (len + 4 < outlen)

        strcat(out, ".inp");

}



/* Allocate InterfaceBond arrays after nibond is determined.

 * Called by ibond_identify() in ibond_init.c.

 */

void allocate_ibond_arrays(CPUUSER cpuuser)

{

    int n = cpuuser->nibond;

    int i;

    if (n <= 0) return;



    cpuuser->i1ibsphid = (int  *)malloc(n * sizeof(int));

    cpuuser->i1ibdnid  = (int  *)malloc(n * sizeof(int));

    cpuuser->d1ibkn    = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibkt    = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfnx   = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfny   = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfnz   = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfsx   = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfsy   = (Real *)malloc(n * sizeof(Real));

    cpuuser->d1ibfsz   = (Real *)malloc(n * sizeof(Real));

    cpuuser->i1ibbk    = (int  *)malloc(n * sizeof(int));



    for (i = 0; i < n; i++)

    {

        cpuuser->d1ibfnx[i] = R0;  cpuuser->d1ibfny[i] = R0;

        cpuuser->d1ibfnz[i] = R0;

        cpuuser->d1ibfsx[i] = R0;  cpuuser->d1ibfsy[i] = R0;

        cpuuser->d1ibfsz[i] = R0;

        cpuuser->i1ibbk[i]  = 0;

        cpuuser->d1ibkn[i]  = cpuuser->ibond_kn;

        cpuuser->d1ibkt[i]  = cpuuser->ibond_kt;

    }

}



void preprocess_cpuuser(CPUUSER cpuuser, char *userfilename)

{

    FILE *log;

    FILE *probe;

    char inpfilename[256];

    const char *sourcefile = userfilename;

    int parsed = 0;



    strcpy(cpuuser->userInputFileName, userfilename);



    probe = fopen(userfilename, "r");

    if (probe != NULL)

    {

        fclose(probe);

        parsed = read_ibond_parameters(cpuuser, userfilename);

        if (parsed)

            printf("[User_preprocess] reading: %s\n", userfilename);

        else

            printf("[User_preprocess] %s opened but *InterfaceBond not found\n",

                   userfilename);

    }

    else

    {

        printf("[User_preprocess] .user not found: %s\n", userfilename);



        make_inp_fallback_name(userfilename, inpfilename, (int)sizeof(inpfilename));

        printf("[User_preprocess] fallback: %s\n", inpfilename);



        parsed = read_ibond_parameters(cpuuser, inpfilename);

        if (parsed)

            sourcefile = inpfilename;

    }



    if (parsed)

    {

        printf("[User_preprocess] InterfaceBond found\n");

        printf("[User_preprocess] rcut = %.6f\n", (double)cpuuser->ibond_rcut);

        printf("[User_preprocess] Kn=%.3e Kt=%.3e ft=%.3e fs=%.3e phi=%.3f\n",

               cpuuser->ibond_kn, cpuuser->ibond_kt,

               cpuuser->ibond_ft, cpuuser->ibond_fs,

               cpuuser->ibond_phi);

    }

    else

    {

        printf("[User_preprocess] warning: *InterfaceBond not parsed "

               "(ibond_rcut remains %.6e)\n", (double)cpuuser->ibond_rcut);

    }



    log = fopen("user_preprocess_done.txt", "w");

    if (log != NULL)

    {

        fprintf(log, "preprocess_cpuuser: %s\n", userfilename);

        fprintf(log, "source_file: %s\n", sourcefile);

        fprintf(log, "InterfaceBond_parsed: %d\n", parsed);

        fprintf(log, "ibond_rcut=%.6e\n", cpuuser->ibond_rcut);

        fclose(log);

    }



    printf("[User_preprocess] done. nibond=%d (identification pending)\n",

           cpuuser->nibond);

    {
        FILE *vfp = fopen("ibond_verify_case.txt", "r");
        if (vfp != NULL)
        {
            int case_id = 0;
            if (fscanf(vfp, "%d", &case_id) == 1 && case_id >= 0 && case_id <= 23)
                cpuuser->ibond_verify_case = case_id;
            fclose(vfp);
        }
        if (cpuuser->ibond_verify_case == 2)
            cpuuser->dev_anchor_ux = 0.001;
        if (cpuuser->ibond_verify_case >= 5 && cpuuser->ibond_verify_case <= 8)
            cpuuser->ibond_level = 1;
        if (cpuuser->ibond_verify_case >= 9 && cpuuser->ibond_verify_case <= 11)
            cpuuser->ibond_level = 2;
        if (cpuuser->ibond_verify_case >= 21)
            cpuuser->ibond_level = 1;
        printf("[User_preprocess] ibond_verify_case=%d dev_anchor_ux=%.6e\n",
               cpuuser->ibond_verify_case, (double)cpuuser->dev_anchor_ux);
    }

    ibond_benchmark_load_from_file(cpuuser, sourcefile);

    if (ibond_benchmark_is_active(cpuuser))
    {
        ibond_mgr_clear(&cpuuser->ibond_mgr);
        cpuuser->ibond_level = (cpuuser->bench_kind == 2) ? 2 : 1;
        printf("[User_preprocess] Benchmark-%d active test_id=%d level=%d\n",
               cpuuser->bench_kind, cpuuser->bench1_test_id, cpuuser->ibond_level);
    }
    else if (cpuuser->ibond_verify_case < 20)
        ibond_config_mock(cpuuser);
    else
        ibond_mgr_clear(&cpuuser->ibond_mgr);

}


