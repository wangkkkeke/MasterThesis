#include "ibond_benchmark.h"
#include "ibond_math.h"
#include "ibond_provider.h"
#include "../Cpucore.h"
#include "../Cpuuser.h"
#include "../Standard_library.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define IBOND_MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define IBOND_MKDIR(p) mkdir(p, 0755)
#endif

static void ibond_benchmark_ensure_output_dir(const char *dir)
{
    if (dir != NULL && dir[0] != '\0')
        IBOND_MKDIR(dir);
}

FILE *ibond_benchmark_fopen_output(int bench_kind, const char *fname,
                                   char *path_out, int path_len)
{
    const char *dirs_b1[] = {
        "../../../04_VerificationCases/Benchmark01/output",
        "benchmark01_output",
        ".",
        NULL
    };
    const char *dirs_b2[] = {
        "../../../04_VerificationCases/Benchmark02_TetSphere/output",
        "benchmark02_output",
        ".",
        NULL
    };
    const char **dirs = (bench_kind == 2) ? dirs_b2 : dirs_b1;
    int i;
    FILE *fp;

    for (i = 0; dirs[i] != NULL; i++)
    {
        ibond_benchmark_ensure_output_dir(dirs[i]);
        snprintf(path_out, (size_t)path_len, "%s/%s", dirs[i], fname);
        fp = fopen(path_out, "w");
        if (fp != NULL)
            return fp;
    }
    return NULL;
}

static Real ibond_benchmark_distance(CPUCORE cpucore, CPUUSER cpuuser);

static int ibond_benchmark_is_identify_only(CPUUSER cpuuser)
{
    if (cpuuser == NULL)
        return 0;
    return cpuuser->bench1_test_id == 0 || cpuuser->bench1_test_id == 2;
}

static Real ibond_benchmark_sphere_to_iface_dist(CPUCORE cpucore, CPUUSER cpuuser)
{
    Real cx, cy, cz, ax, ay, az;

    if (cpuuser == NULL)
        return R0;

    cx = cpuuser->bench1_sphere_x;
    cy = cpuuser->bench1_sphere_y;
    cz = cpuuser->bench1_sphere_z;

    if (cpuuser->nibond > 0)
        return ibond_benchmark_distance(cpucore, cpuuser);

    if (cpuuser->bench_kind == 2 && cpucore != NULL)
    {
        InterfaceEntity ent;
        if (ibond_entity_build_benchmark2_c3d4(cpucore, &ent))
            return ibond_vec3_norm(ibond_vec3(cx - ent.xc, cy - ent.yc, cz - ent.zc));
    }

    if (cpucore != NULL && cpucore->nfn > 1)
    {
        ax = cpucore->d1fnix[1];
        ay = cpucore->d1fniy[1];
        az = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[1] : R0;
        return ibond_vec3_norm(ibond_vec3(cx - ax, cy - ay, cz - az));
    }

    return R0;
}

static const char *ibond_benchmark_identify_status(CPUUSER cpuuser)
{
    if (cpuuser == NULL)
        return "FAIL";
    if (cpuuser->bench1_test_id == 0)
        return (cpuuser->nibond == 1) ? "OK_identify" : "FAIL_nibond";
    if (cpuuser->bench1_test_id == 2)
        return (cpuuser->nibond == 0) ? "OK_beyond_rcut" : "FAIL_nibond";
    return "OK_identify";
}

void ibond_benchmark_clear(CPUUSER cpuuser)
{
    if (cpuuser == NULL)
        return;
    cpuuser->bench_kind = 0;
    cpuuser->bench1_test_id = -1;
    cpuuser->bench1_sphere_x = R0;
    cpuuser->bench1_sphere_y = R0;
    cpuuser->bench1_sphere_z = R0;
    cpuuser->bench1_particle_du_n = R0;
    cpuuser->bench1_anchor_ux = R0;
}

int ibond_benchmark_is_active(CPUUSER cpuuser)
{
    if (cpuuser == NULL)
        return 0;
    return cpuuser->bench_kind >= 1 && cpuuser->bench1_test_id >= 0;
}

int ibond_benchmark_get_kind(CPUUSER cpuuser)
{
    if (cpuuser == NULL)
        return 0;
    return cpuuser->bench_kind;
}

int ibond_benchmark_load_from_file(CPUUSER cpuuser, const char *filename)
{
    FILE *fp;
    char line[256];
    int found = 0;
    int tid;
    double sx, sy, sz, du_n, anchor_ux;

    ibond_benchmark_clear(cpuuser);
    if (cpuuser == NULL || filename == NULL)
        return 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
        return 0;

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strncmp(line, "*Benchmark1", 11) == 0)
            cpuuser->bench_kind = 1;
        else if (strncmp(line, "*Benchmark2", 11) == 0)
            cpuuser->bench_kind = 2;
        else
            continue;
        if (fgets(line, sizeof(line), fp) == NULL)
            break;
        if (sscanf(line, "%d,%lf,%lf,%lf,%lf,%lf",
                   &tid, &sx, &sy, &sz, &du_n, &anchor_ux) >= 5)
        {
            cpuuser->bench1_test_id = tid;
            cpuuser->bench1_sphere_x = (Real)sx;
            cpuuser->bench1_sphere_y = (Real)sy;
            cpuuser->bench1_sphere_z = (Real)sz;
            cpuuser->bench1_particle_du_n = (Real)du_n;
            cpuuser->bench1_anchor_ux = (Real)anchor_ux;
            found = 1;
            printf("[ibond_benchmark] loaded Benchmark-%d test_id=%d sphere=(%.4f,%.4f,%.4f) du_n=%.6e anchor_ux=%.6e\n",
                   cpuuser->bench_kind, tid, sx, sy, sz, du_n, anchor_ux);
        }
        break;
    }

    fclose(fp);
    return found;
}

static Real ibond_benchmark_distance(CPUCORE cpucore, CPUUSER cpuuser)
{
    BondTable *t;
    Real cx, cy, cz, ax, ay, az;

    if (cpucore == NULL || cpuuser == NULL || cpuuser->nibond <= 0)
        return R0;

    t = &cpuuser->ibond_mgr.table;
    if (t->nbond <= 0 || t->particles == NULL)
        return R0;

    {
        Particle *p = &t->particles[t->bonds[0].sphere_index];
        cx = p->x0;
        cy = p->y0;
        cz = p->z0;

        if (t->bonds[0].entity_index >= 0 && t->entities != NULL)
        {
            InterfaceEntity *ent = &t->entities[t->bonds[0].entity_index];
            ax = ent->xc;
            ay = ent->yc;
            az = ent->zc;
        }
        else if (t->anchors != NULL)
        {
            BondAnchor *a = &t->anchors[t->bonds[0].anchor_index];
            int n = a->node_id;

            ax = cpucore->d1fnix[n];
            ay = cpucore->d1fniy[n];
            az = (cpucore->d1fniz != NULL) ? cpucore->d1fniz[n] : R0;
        }
        else
            return R0;

        return ibond_vec3_norm(ibond_vec3(cx - ax, cy - ay, cz - az));
    }
}

static void ibond_benchmark_du_fn(CPUCORE cpucore, CPUUSER cpuuser,
                                  Real *du_n_out, Real *fn_out)
{
    BondTable *t;
    IbondVec3 du, n;
    Real dun;

    *du_n_out = R0;
    *fn_out = R0;
    if (cpuuser == NULL || cpuuser->nibond <= 0)
        return;

    t = &cpuuser->ibond_mgr.table;
    if (t->nbond <= 0 || t->bonds == NULL)
        return;

    if (t->bonds[0].entity_index >= 0 && t->entities != NULL)
    {
        InterfaceEntity *ent = &t->entities[t->bonds[0].entity_index];
        ibond_relative_displacement_entity(cpucore, cpuuser, ent,
                                           t->bonds[0].sphere_index, &du);
        n = ibond_vec3(ent->nx, ent->ny, ent->nz);
    }
    else if (t->anchors != NULL)
    {
        ibond_relative_displacement(cpucore, cpuuser, &t->anchors[t->bonds[0].anchor_index],
                                    t->bonds[0].sphere_index, &du);
        n = ibond_vec3(t->anchors[t->bonds[0].anchor_index].nx,
                       t->anchors[t->bonds[0].anchor_index].ny,
                       t->anchors[t->bonds[0].anchor_index].nz);
    }
    else
        return;

    dun = ibond_vec3_dot(du, n);
    *du_n_out = dun;
    *fn_out = t->bonds[0].kn * dun;
}

void ibond_benchmark_write_log(CPUCORE cpucore, CPUUSER cpuuser)
{
    FILE *fp;
    char path[512];
    char fname[64];
    BondTable *t;
    Real du_n, fn, dist, sx, sy, sz;
    int nibond, nsph, identify_only;

    if (!ibond_benchmark_is_active(cpuuser))
        return;

    const char *prefix = (cpuuser->bench_kind == 2) ? "benchmark2" : "benchmark1";
    const char *bname = (cpuuser->bench_kind == 2) ? "Benchmark-2" : "Benchmark-1";

    identify_only = ibond_benchmark_is_identify_only(cpuuser);
    sprintf(fname, "%s_test%d_log.txt", prefix, cpuuser->bench1_test_id);
    fp = ibond_benchmark_fopen_output(cpuuser->bench_kind, fname, path, (int)sizeof(path));
    if (fp == NULL)
    {
        printf("[ibond_benchmark] cannot open %s\n", fname);
        return;
    }

    nibond = (cpuuser != NULL) ? cpuuser->nibond : 0;
    nsph = (cpucore != NULL) ? cpucore->nsph : 0;
    t = &cpuuser->ibond_mgr.table;

    fprintf(fp, "benchmark=%s\n", bname);
    fprintf(fp, "test_id=%d\n", cpuuser->bench1_test_id);
    fprintf(fp, "verify_case=0\n");
    fprintf(fp, "nsph=%d\n", nsph);
    fprintf(fp, "meta_sphere=(%.6e,%.6e,%.6e)\n",
            (double)cpuuser->bench1_sphere_x,
            (double)cpuuser->bench1_sphere_y,
            (double)cpuuser->bench1_sphere_z);
    fprintf(fp, "meta_particle_du_n=%.6e\n", (double)cpuuser->bench1_particle_du_n);
    fprintf(fp, "meta_anchor_ux=%.6e\n", (double)cpuuser->bench1_anchor_ux);

    if (nsph <= 0 && cpuuser != NULL && cpuuser->bench1_test_id >= 0)
    {
        fprintf(fp, "Bond Active=%s\n", (nibond > 0) ? "Yes" : "No");
        fprintf(fp, "nibond=%d\n", nibond);
        fprintf(fp, "provider=%s_meta (nsph=0 synthetic particle)\n",
                (cpuuser->bench_kind == 2) ? "Benchmark2" : "Benchmark1");

        if (identify_only)
        {
            dist = ibond_benchmark_sphere_to_iface_dist(cpucore, cpuuser);
            fprintf(fp, "stage=identify_only\n");
            fprintf(fp, "Distance=%.6e\n", (double)dist);
            if (cpuuser->bench_kind == 2)
                fprintf(fp, "representation=R2_FaceCentroid\n");
            fprintf(fp, "status=%s\n", ibond_benchmark_identify_status(cpuuser));
            fclose(fp);
            printf("[ibond_benchmark] wrote %s (identify only)\n", path);
            return;
        }

        if (nibond > 0)
        {
            dist = ibond_benchmark_distance(cpucore, cpuuser);
            ibond_benchmark_du_fn(cpucore, cpuuser, &du_n, &fn);
            fprintf(fp, "Distance=%.6e\n", (double)dist);
            fprintf(fp, "Delta_u_n=%.6e\n", (double)du_n);
            fprintf(fp, "Fn=%.6e\n", (double)fn);
            if (t->forces != NULL)
            {
                BondForce *bf = &t->forces[0];
                sx = bf->fem_fx + bf->dem_fx;
                sy = bf->fem_fy + bf->dem_fy;
                sz = bf->fem_fz + bf->dem_fz;
                fprintf(fp, "FEM Force=(%.6e,%.6e,%.6e)\n",
                        (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
                fprintf(fp, "Particle Force=(%.6e,%.6e,%.6e)\n",
                        (double)bf->dem_fx, (double)bf->dem_fy, (double)bf->dem_fz);
                fprintf(fp, "SigmaF=(%.6e,%.6e,%.6e)\n", (double)sx, (double)sy, (double)sz);
                if (cpuuser->bench_kind == 2 &&
                    t->bonds[0].entity_index >= 0 && t->entities != NULL)
                {
                    InterfaceEntity *ent = &t->entities[t->bonds[0].entity_index];
                    Real sum_fx = R0, sum_fy = R0, sum_fz = R0;
                    int j;
                    fprintf(fp, "representation=R2_FaceCentroid\n");
                    fprintf(fp, "FaceForce=(%.6e,%.6e,%.6e)\n",
                            (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
                    for (j = 0; j < ent->nnodes; j++)
                    {
                        Real ni = ent->shape_n[j];
                        Real nfx = ni * bf->fem_fx;
                        Real nfy = ni * bf->fem_fy;
                        Real nfz = ni * bf->fem_fz;
                        fprintf(fp, "Node%d N=%.6e Force=(%.6e,%.6e,%.6e)\n",
                                ent->node_ids[j] + 1, (double)ni,
                                (double)nfx, (double)nfy, (double)nfz);
                        sum_fx += nfx;
                        sum_fy += nfy;
                        sum_fz += nfz;
                    }
                    fprintf(fp, "sum_NodeForce=(%.6e,%.6e,%.6e)\n",
                            (double)sum_fx, (double)sum_fy, (double)sum_fz);
                }
            }
            fprintf(fp, "status=PARTIAL_meta_only_need_real_DEM\n");
        }
        else if (cpuuser->bench1_test_id == 2)
        {
            dist = ibond_benchmark_sphere_to_iface_dist(cpucore, cpuuser);
            fprintf(fp, "Distance=%.6e\n", (double)dist);
            fprintf(fp, "status=OK_beyond_rcut\n");
        }
        else
            fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
        fclose(fp);
        printf("[ibond_benchmark] wrote %s (meta mode nsph=0)\n", path);
        return;
    }

    if (nsph <= 0)
    {
        fprintf(fp, "Bond Active=No\n");
        fprintf(fp, "status=BLOCKED_need_FEM_DEM_inp\n");
        fclose(fp);
        printf("[ibond_benchmark] wrote %s (BLOCKED nsph=0)\n", fname);
        return;
    }

    fprintf(fp, "Bond Active=%s\n", (nibond > 0) ? "Yes" : "No");
    fprintf(fp, "nibond=%d\n", nibond);
    dist = ibond_benchmark_distance(cpucore, cpuuser);
    ibond_benchmark_du_fn(cpucore, cpuuser, &du_n, &fn);
    fprintf(fp, "Distance=%.6e\n", (double)dist);
    fprintf(fp, "Delta_u_n=%.6e\n", (double)du_n);
    fprintf(fp, "Fn=%.6e\n", (double)fn);

    if (nibond > 0 && t->forces != NULL)
    {
        BondForce *bf = &t->forces[0];
        sx = bf->fem_fx + bf->dem_fx;
        sy = bf->fem_fy + bf->dem_fy;
        sz = bf->fem_fz + bf->dem_fz;
        fprintf(fp, "FEM Force=(%.6e,%.6e,%.6e)\n",
                (double)bf->fem_fx, (double)bf->fem_fy, (double)bf->fem_fz);
        fprintf(fp, "Particle Force=(%.6e,%.6e,%.6e)\n",
                (double)bf->dem_fx, (double)bf->dem_fy, (double)bf->dem_fz);
        fprintf(fp, "SigmaF=(%.6e,%.6e,%.6e)\n", (double)sx, (double)sy, (double)sz);
        fprintf(fp, "status=OK\n");
    }
    else
    {
        fprintf(fp, "status=NO_BOND\n");
    }

    fclose(fp);
    printf("[ibond_benchmark] wrote %s nibond=%d\n", fname, nibond);
}
