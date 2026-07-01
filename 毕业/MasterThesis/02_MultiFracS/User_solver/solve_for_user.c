#include "Cpucore.h"
#include "Cpuuser_abstract.h"
#include "Cpuuser.h"
void solve_user(CPUCORE cpucore, CPUUSER cpuuser)
{
	for (int i = 0; i < cpuuser->nuser; i++)
	{
		user_solver(cpucore, cpuuser);
		cpuuser->nuserstep++;
		cpuuser->dusertime += cpuuser->duserdt;
	}
}