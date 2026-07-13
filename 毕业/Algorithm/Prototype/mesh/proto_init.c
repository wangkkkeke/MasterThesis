#include <stdio.h>

#include "proto_api.h"

int prototype_initialize(int max_node, int max_tet, int max_sphere, int max_bond)
{
    printf("[Driver] prototype_initialize\n");

    if (proto_alloc_arrays(max_node, max_tet, max_sphere, max_bond) != 0) {
        fprintf(stderr, "[Driver] prototype_initialize failed\n");
        return -1;
    }

    node_num = 0;
    tet_num = 0;
    sphere_num = 0;
    bond_num = 0;
    proto_time = 0.0;
    proto_dt = 0.0;
    proto_t_end = 0.0;

    printf("[Driver] prototype_initialize ok\n");
    return 0;
}

void prototype_finalize(void)
{
    printf("[Driver] prototype_finalize\n");
    proto_free_arrays();
    printf("[Driver] prototype_finalize ok\n");
}
