# Algorithm Note 01 — Symbiotic FEM–DEM Coupling Prototype

**Version:** aligned with Prototype_v0.1  
**Date:** 2026-07-13  
**Audience:** thesis Chapter 3 draft (algorithm), not a user manual  

---

## 1 Background

Explicit continuum–discontinuum coupling is widely used for fracture and fragmentation. Classical strategies often split the domain into an FEM subdomain and a DEM subdomain, then introduce an **interface treatment** (mortar, bridging domain, ghost particles, embedded particles, etc.) to transfer kinematics and forces across the partition.

The present work targets a **homogeneous continuum member** that is only **numerically** partitioned (e.g. FEM–DEM–FEM) for computational convenience. There is no physical material interface and no contact surface between two bodies. Therefore, coupling should be expressed as a **symbiotic coexistence** of continuum elements (Tet) and discrete spheres (Sphere) on one member, rather than as a bolted-on interface between two solvers.

---

## 2 Motivation

Traditional interface-based coupling tends to:

1. Introduce an extra algorithmic object (interface element / ghost set / overlapping domain).  
2. Couple through special-case logic that knows both FEM and DEM.  
3. Make verification difficult: interface bugs mix with FEM bugs and DEM bugs.

The mentor’s idea rejects “DEM-only spheres + interface gadget” as the primary construction. Instead:

- Spheres exist **globally** on the member.  
- Tets exist on FEM regions.  
- Coupling emerges from shared topology (bonds) and kinematic roles (motion modes), not from a separate interface species.

Motivation in one sentence: **remove the interface object; keep one continuum idea; let Proxy/Free roles and bonds carry the coupling.**

---

## 3 Core Algorithm

**Objects (SoA, ANSI C):** Node, Tet, Sphere, Bond.

**Roles (not types):** controlled by `sphere_motion_mode`

- `MOTION_PROXY`: no independent integration; position/velocity from host tet shape functions.  
- `MOTION_FREE`: explicit DEM update `F=ma` (no rotation in v0.1).

**Time loop order (frozen):**

`clear_force → (driver_)fem → proxy_update → bond_force → dem_step → force_mapping_proxy_to_tet → I/O`

**Architecture Freeze highlights:**

- Bond never branches on Proxy/Free at force evaluation time (`bond_active` only).  
- Mapping only writes Node Force.  
- DEM only integrates FREE.  
- FEM does not see Sphere arrays except through Mapping.

See also: `ADR002_GlobalSphereEmbedding.md`, `CONCEPT_MODEL_AutomaticSymbioticTopology.md`.

---

## 4 Automatic Symbiotic Model Construction

From mesh input alone (Case03 capability):

```
Tet Mesh
   → Global Sphere Generation
   → Host Tet Identification
   → Region Inheritance
   → Motion Mode Assignment
   → Bond Generation
   → Automatic Symbiotic Topology
```

Classification is **not** “paint by coordinates”. It is:

`Host Tet → tet_region → motion_mode`

Spheres without a host tet (e.g. DEM gap with no tets) become FREE. Proxy–Free bonds appear wherever distance criteria connect Proxy and Free neighbors—**boundary coupling without Interface Elements**.

---

## 5 Kinematic Coupling

Proxy spheres are kinematically enslaved to the continuum:

\[
\mathbf{x}_p = \sum_{i=1}^{4} N_i \mathbf{x}_i,\quad
\mathbf{v}_p = \sum_{i=1}^{4} N_i \mathbf{v}_i
\]

with \(N_i\) stored from host-tet barycentric coordinates at construction (no repeated host search in the time loop in v0.1).

Case01 uses Driver FEM (prescribed nodal motion) so that interpolation/mapping can be verified without a full FEM integrator.

---

## 6 Force Transfer Mechanism

1. Bonds compute linear spring forces and write action–reaction into sphere force arrays.  
2. On Proxy, that force is the **Reaction**.  
3. Mapping distributes Reaction to tet nodes:

\[
\mathbf{F}_i \mathrel{+}= N_i \mathbf{R}
\]

Because \(\sum N_i = 1\), nodal force sums recover the proxy reaction (verified in Case01/02). Multi-proxy contributions accumulate on shared nodes (Case02 V5).

---

## 7 Current Verification Status

| Phase | Case | Question answered | Status |
|-------|------|-------------------|--------|
| I Mathematical | Case01 | Single coupling loop correct? | PASS |
| I Mathematical | Case02 | Multi-pair superposition / independence? | PASS |
| II Algorithm Capability | Case03 | Automatic symbiotic construction from mesh? | PASS |

Release: **Prototype_v0.1 (Verified)**.

---

## 8 Current Limitations

Prototype_v0.1 intentionally does **not** include:

- Cell Linked List / optimized neighborhood  
- Bond fracture  
- Contact, rolling, rotation  
- Full dynamic FEM central-difference as default Case01 path  
- Wave propagation benchmarks  
- Beam structural benchmarks  

These are deferred by phase (see Section 9), not forgotten.

---

## 9 Next Development Stage

**Phase III — Computational Capability**

- Case04: Automatic Neighborhood Construction (O(N²) vs CLL consistency)  
- Case05: Computational Efficiency  

**Phase IV — Physical Capability**

- Beam / crack / benchmark  

Branching rule: all work starts from tag `Prototype_v0.1`, never silently edits the frozen release.
