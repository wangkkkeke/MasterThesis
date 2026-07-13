#include <stdio.h>

#include "proto_api.h"

/*
 * Unified entry: first version calls regular packing only.
 * random / FCC reserved for later; API stays frozen.
 */
int sphere_generate(void)
{
    printf("[Sphere] sphere_generate -> regular\n");
    return sphere_generate_regular();
}
