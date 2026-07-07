#!/usr/bin/env python3
"""Generate Benchmark-2 inp files (single C3D4 tet + Benchmark metadata).

Geometry:
  Node 1: apex (0,0,0) fixed
  Nodes 2,3,4: interface face at x=L
  Sphere: interface centroid + d0 along +x normal
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

OUT_DIR = Path(__file__).resolve().parents[1] / "Input"
L = 0.05
H = 0.05
YC = H / 3.0
ZC = H / 3.0
RCUT = 0.02
KN = 1e8

SPHERE_IN = (L + 0.01, YC, ZC)
SPHERE_FAR = (1.0, YC, ZC)


@dataclass
class BenchTest:
    fname: str
    test_id: int
    title: str
    sphere: tuple[float, float, float]
    particle_du_n: float = 0.0
    anchor_ux: float = 0.0


TESTS = [
    BenchTest("benchmark2_test0.inp", 0, "Initialization", SPHERE_IN),
    BenchTest("benchmark2_test1.inp", 1, "Normal Loading", SPHERE_IN, particle_du_n=0.001),
    BenchTest("benchmark2_test2.inp", 2, "Beyond rcut", SPHERE_FAR),
    BenchTest("benchmark2_test3.inp", 3, "Reverse Loading", SPHERE_IN, particle_du_n=-0.001),
    BenchTest("benchmark2_test4a.inp", 40, "Relative Motion (sphere moves)", SPHERE_IN, particle_du_n=0.001),
    BenchTest("benchmark2_test4b.inp", 41, "Relative Motion (anchor moves)", SPHERE_IN, anchor_ux=-0.001),
]


def footer_lines() -> list[str]:
    return [
        "*UpdateMonitorDataFrequency",
        "100",
        "*CalulationType",
        "1",
        "*NumTHMpStep",
        "0,0,1",
        "*SmallMove",
        "0",
        "*StrengthReductionMethod",
        "1,0",
        "*CentrifugalLoadingMethod",
        "1,0",
        "*IFlagTest0UCS1UT",
        "0,-0.025,0,0.025,0.05",
        "*IFlagTestBD",
        "0,0,0,0.025,-1",
        "*UpdateBasicTestMointorFrequency",
        "100",
        "*OutRestoreFileFrequency",
        "100000000",
        "*OutResultFileFrequency",
        "1000",
        "*OutApertFileFrequency",
        "100000000",
        "*OutContinuumStresFileFrequency",
        "100000000",
        "*UpdateConsoleResultFrequency",
        "100",
        "*setAccuracy",
        "1e-6",
        "*Begin",
        "*solve",
        "*End",
    ]


def build_inp(test: BenchTest) -> str:
    sx, sy, sz = test.sphere
    lines = [
        "*Heading",
        f" Benchmark-2 {test.title} (auto-generated)",
        f" test_id={test.test_id}  verify_case=0  rcut={RCUT}",
        "*NODE",
        "1, 0.0, 0.0, 0.0",
        f"2, {L}, 0.0, 0.0",
        f"3, {L}, {H}, 0.0",
        f"4, {L}, 0.0, {H}",
        "******* E L E M E N T S *************",
        "*ELEMENT, type=C3D4, ELSET=fem_zone",
        "1, 1, 2, 3, 4",
        "*ELSET,ELSET=fem_zone",
        "1,",
        "*NSET,NSET=fix_nodes",
        "1,",
        "*NSET,NSET=fem_interface",
        "2, 3, 4,",
        "*Material=fem_zone",
        "1,2300,2e9,0.3,200e9,200e9,30,-7,1e-12,1e-12,1e-12,0,0,0,-14,1.0,0.2,1.0,0,-19,3.0,3.0,3.0,0,0,0,-26,800,5e-6,1000,-30,3,3,3,0,0,0,-37,0.6e-6,-39,-40,-41,-42,-43,-44,",
        "0,20e6,30,10e6,1e15,200e9,200e9,2,10,-9,1e-4,0.1e-4,5e-4,-13,1000,-15,20000,0.001,-18,20000,10,-21,1000,0.001,-24,30,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,",
        "*FixBoundary=fix_nodes",
        "1,0,-1,-2,-3,-4,-5,",
        "*InterfaceBond",
        f"{KN:.6e}, 4e7, 1e5, 1e5, 0.5, {RCUT}",
        "*Benchmark2",
        f"{test.test_id}, {sx}, {sy}, {sz}, {test.particle_du_n}, {test.anchor_ux}",
    ]
    lines.extend(footer_lines())
    return "\n".join(lines) + "\n"


def main() -> None:
    OUT_DIR.mkdir(parents=True, exist_ok=True)
    for test in TESTS:
        path = OUT_DIR / test.fname
        path.write_text(build_inp(test), encoding="utf-8")
        print(f"Wrote {path}")

    base = BenchTest("benchmark2.inp", 0, "Base (identify only)", SPHERE_IN)
    base_path = OUT_DIR / base.fname
    base_path.write_text(build_inp(base), encoding="utf-8")
    print(f"Wrote {base_path}")
    print(f"Generated {len(TESTS) + 1} Benchmark-2 inp files in {OUT_DIR}")


if __name__ == "__main__":
    main()
