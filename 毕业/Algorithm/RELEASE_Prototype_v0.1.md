# Release Definition — Prototype_v0.1

```
Release: Prototype_v0.1
Status: Verified

Freeze:
  Architecture Freeze v1.0

Verification:
  Case01 PASS
  Case02 PASS
  Case03 PASS

Capability:
  Automatic Symbiotic Model Construction

Not Included:
  - Cell Linked List
  - Bond Fracture
  - Contact
  - Dynamic FEM Solver
  - Wave Propagation
  - Beam Benchmark

Date: 2026-07-13
```

## Meaning

This release freezes the first verified prototype of the mentor's symbiotic FEM–DEM coupling idea:

**Global Sphere Embedding + Host-Tet Region Inheritance + Motion Mode + Automatic Proxy–Free Bond Topology.**

## Policy

- Do **not** modify `Prototype_v0.1` after tagging.
- All later work branches from this release:
  - `Prototype_v0.1` → branch → `Prototype_v0.2`
- Neighbor / Cell Linked List / physical benchmarks belong to later phases, not this tag.

## Artifacts

| Artifact | Path |
|----------|------|
| Spec | `Algorithm Specification v1.0.md` |
| Code | `Prototype/` |
| Case01 report | `Prototype/VerificationReport_Case01` (CSV: `output/verify_case01.csv`) |
| Case02 report | `Prototype/VerificationReport_Case02.md` |
| Case03 report | `Prototype/VerificationReport_Case03.md` |
| Algorithm note | `Algorithm_Note_01.md` |
| ADR | `ADR002_GlobalSphereEmbedding.md` |
| Concept model | `CONCEPT_MODEL_AutomaticSymbioticTopology.md` |
| Algorithm definition | `AlgorithmSpecification_v1.0.md` |

## Capability Q&A (frozen)

**Q1 — What capability does Case03 add?**  
Automatic construction of the symbiotic model from mesh input only.

**Q2 — What is lost if Case03 is removed?**  
The code can still run, but every Sphere must be assigned manually. Automation of symbiotic topology is lost.
