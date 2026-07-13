# ADR002 — Global Sphere Embedding

**Status:** Accepted  
**Release:** Prototype_v0.1  
**Date:** 2026-07-13  
**Context:** Prototype Architecture Freeze v1.0 + Case01–Case03 verified

This ADR records **why** the design is as it is. It is not a tutorial of formulas.

---

## ADR002-1 — Why Global Sphere Embedding (not DEM-only spheres)

**Decision:** Generate spheres over the **entire** continuum domain, including FEM regions.

**Rejected alternative:** Place spheres only inside the DEM subdomain and couple through a dedicated interface layer.

**Rationale:**

- The physical object is one homogeneous continuum; FEM|DEM|FEM is a **numerical partition**, not a material interface.
- Global embedding makes Proxy spheres first-class citizens of the same particle topology as Free spheres.
- Interface bonds (Proxy–Free) then arise as ordinary bonds of the same Bond object, without inventing a second “interface particle” species.
- This matches the mentor’s symbiotic-coupling idea: coexistence of Tet and Sphere over the domain, with different kinematic roles.

---

## ADR002-2 — Why Proxy does not integrate (Host-Tet interpolation)

**Decision:** `MOTION_PROXY` spheres do not solve `F=ma`. Position/velocity are interpolated from the host tet: `u = Σ Ni ui`.

**Rejected alternative:** Give Proxy independent DEM DOFs and constrain them weakly to the continuum.

**Rationale:**

- Proxy has **no independent continuum DOF**; it is a kinematic slave of the FEM field.
- Interpolation enforces consistency with the tet displacement field by construction.
- Separating kinematics (Proxy update) from kinetics (Bond/DEM/Mapping) keeps Case01-style verification modular: one module, one responsibility (Architecture Freeze).

---

## ADR002-3 — Why Motion Mode inherits Tet Region (not coordinate classification)

**Decision:** Classification chain is:

`Host Tet → tet_region → sphere_region / motion_mode`

**Rejected alternative:** Classify by comparing sphere-center coordinates against geometric FEM/DEM boxes.

**Rationale:**

- Region is a property of the **mesh entity** (tet), not of an ad-hoc coordinate predicate.
- Inheritance keeps Sphere classification consistent with Host Tet search (single source of truth).
- Spheres with no host tet (e.g. DEM gap without tets) become `MOTION_FREE` naturally.
- Case03 V9 (Region Consistency) exists specifically to guard this decision.

---

## ADR002-4 — Why Proxy–Free Bonds exist naturally (no Interface Element)

**Decision:** Do not introduce Interface Elements / mortar / ghost-particle coupling objects. Use the same Bond type; Proxy–Free pairs become ACTIVE bonds when distance < rcut.

**Rejected alternative:** A dedicated interface element between FEM face and DEM particles.

**Rationale:**

- Under global embedding, the FEM–DEM numerical interface is occupied by neighboring Proxy and Free spheres.
- Distance-based Bond generation already connects them; the “interface” is an emergent subgraph.
- This avoids a second physics object and a second force pathway, reducing algorithmic surface area for bugs and papers’ conceptual load.

---

## ADR002-5 — Why Bond does not know Proxy; Mapping does not know DEM

**Decision (module duty):**

- **Bond** only sees `sphereA`, `sphereB`, `bond_active`. It writes ±F to sphere force arrays. No `if (proxy)`.
- **Mapping** only reads Proxy forces as Reaction and writes **Node Force**. It does not update sphere motion.
- **DEM** only integrates `MOTION_FREE`.
- **FEM/Driver** only updates nodes; spheres enter FEM solely through Mapping.

**Rationale:**

- Prevents circular module calls and hidden coupling (Architecture Freeze ①–⑦).
- Enables Case02 V8 (Bond Independence): deleting one bond must not change other bonds’ `fn`.
- Enables future replacement of neighbor search (O(N²) → Cell Linked List) without rewriting Bond force or Mapping.

---

## Consequences

**Positive**

- One Sphere SoA, one Bond type, clear data flow (Concept Model v0.1).
- Case01–Case03 can verify math, superposition, and automatic construction separately.

**Negative / deferred**

- Neighbor efficiency (CLL) not in v0.1.
- No fracture/contact/rolling; no full FEM central-difference in Case01 path.
- Physical beam/wave benchmarks deferred to Phase IV.

**Follow-up ADRs (expected)**

- ADR003: Automatic Neighborhood Construction (Cell Linked List)
- ADR004: Physical Capability (beam / crack / benchmark)
