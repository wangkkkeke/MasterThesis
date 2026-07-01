#include "Cpuuser.h"
#include "Cpuuser_abstract.h"
#include "Cpucore.h"
#include "Standard_library.h"

/* Read *InterfaceBond section from inp file.
 * Format (one line after keyword):
 *   Kn, Kt, ft, fs, phi, rcut
 */
static void read_ibond_parameters(CPUUSER cpuuser, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    char line[256];

    if (fp == NULL)
    {
        printf("[User_preprocess] warning: cannot open %s\n", filename);
        return;
    }

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
                printf("[User_preprocess] InterfaceBond params: "
                       "Kn=%.3e Kt=%.3e ft=%.3e rcut=%.3e\n",
                       cpuuser->ibond_kn, cpuuser->ibond_kt,
                       cpuuser->ibond_ft, cpuuser->ibond_rcut);
            }
            break;
        }
    }
    fclose(fp);
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
    strcpy(cpuuser->userInputFileName, userfilename);
    read_ibond_parameters(cpuuser, userfilename);
    printf("[User_preprocess] done. nibond=%d (identification pending)\n",
           cpuuser->nibond);
}
