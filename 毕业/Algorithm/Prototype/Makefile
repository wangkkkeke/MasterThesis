# Architecture Freeze v1.0 — Prototype Makefile
CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -O0 -g -Iinclude
LDFLAGS = -lm

CORE = mesh/proto_soa.c mesh/proto_memory.c mesh/proto_init.c
GEOM = geometry/point_in_tet.c geometry/barycentric.c geometry/shape_function.c
SPH  = sphere/sphere_generate.c sphere/sphere_generate_regular.c \
       sphere/sphere_classify.c sphere/sphere_clear_force.c \
       sphere/sphere_find_host_tet.c sphere/sphere_proxy_update.c
BOND = bond/bond_search_neighbor.c bond/bond_create.c bond/bond_force.c
FEM  = fem/driver_fem_step.c
DEM  = dem/dem_solver.c
CPL  = coupling/force_mapping_proxy_to_tet.c
IO   = vtk/vtk_write.c csv/csv_write.c

CASE01_SRC = $(CORE) $(GEOM) $(SPH) $(BOND) $(FEM) $(DEM) $(CPL) $(IO) \
             driver/driver_case01.c

VERIFY_SRC = $(CORE) $(GEOM) $(SPH) $(BOND) $(FEM) $(DEM) $(CPL) \
             verify/verify_case01.c

VERIFY02_SRC = $(CORE) $(GEOM) $(SPH) $(BOND) $(FEM) $(DEM) $(CPL) \
               verify/verify_case02.c

VERIFY03_SRC = $(CORE) $(GEOM) $(SPH) $(BOND) $(FEM) $(DEM) $(CPL) $(IO) \
               verify/verify_case03.c

.PHONY: all stage1 stage2 case01 verify_case01 verify_case02 verify_case03 clean

all: stage1 stage2 case01 verify_case01 verify_case02 verify_case03

stage1: proto_stage1
proto_stage1: $(CORE) driver/driver_stage1.c
	$(CC) $(CFLAGS) -o $@ $(CORE) driver/driver_stage1.c $(LDFLAGS)

stage2: proto_stage2
proto_stage2: $(GEOM) driver/driver_stage2.c
	$(CC) $(CFLAGS) -o $@ $(GEOM) driver/driver_stage2.c $(LDFLAGS)

case01: proto_case01
proto_case01: $(CASE01_SRC)
	$(CC) $(CFLAGS) -o $@ $(CASE01_SRC) $(LDFLAGS)

verify_case01: proto_verify_case01
proto_verify_case01: $(VERIFY_SRC)
	$(CC) $(CFLAGS) -o $@ $(VERIFY_SRC) $(LDFLAGS)

verify_case02: proto_verify_case02
proto_verify_case02: $(VERIFY02_SRC)
	$(CC) $(CFLAGS) -o $@ $(VERIFY02_SRC) $(LDFLAGS)

verify_case03: proto_verify_case03
proto_verify_case03: $(VERIFY03_SRC)
	$(CC) $(CFLAGS) -o $@ $(VERIFY03_SRC) $(LDFLAGS)

clean:
	rm -f proto_stage1 proto_stage1.exe proto_stage2 proto_stage2.exe
	rm -f proto_case01 proto_case01.exe
	rm -f proto_verify_case01 proto_verify_case01.exe
	rm -f proto_verify_case02 proto_verify_case02.exe
	rm -f proto_verify_case03 proto_verify_case03.exe
	rm -f mesh/*.o geometry/*.o sphere/*.o bond/*.o fem/*.o dem/*.o
	rm -f coupling/*.o vtk/*.o csv/*.o driver/*.o verify/*.o
