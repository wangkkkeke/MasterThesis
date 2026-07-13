#include <stdio.h>

#include "proto_api.h"

void sphere_clear_force(void)
{
    int i;

    for (i = 0; i < sphere_num; ++i) {
        sphere_fx[i] = 0.0;
        sphere_fy[i] = 0.0;
        sphere_fz[i] = 0.0;
    }
}
