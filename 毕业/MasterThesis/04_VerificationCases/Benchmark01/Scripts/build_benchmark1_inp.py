#!/usr/bin/env python3
"""Generate Benchmark-1 inp files (single CPS3 + Benchmark metadata).

FEM: one plane-stress triangle (2D proxy for single-tet face; see README).
DEM: sphere position in *Benchmark1 metadata (requires nsph=1 inp path from team).
"""
from __future__ import annotations

from dataclasses import dataclass
from pathlib import Path

OUT_DIR = Path(__file__).resolve().parents[1] / "Input"
Z = 0.1
L = 0.05
H = 0.05
RCUT = 0.02
KN = 1e8

# Interface anchor: node 2 at (L, 0)
SPHERE_IN = (0.06, 0.0, Z)   # d = 0.01 m
SPHERE_FAR = (1.0, 0.0, Z)   # Test 2: d >> rcut


@dataclass
class BenchTest:
    fname: str
    test_id: int
    title: str
    sphere: tuple[float, float, float]
    particle_du_n: float = 0.0
    anchor_ux: float = 0.0


TESTS = [
    BenchTest("benchmark1_test0.inp", 0, "Initialization", SPHERE_IN),
    BenchTest("benchmark1_test1.inp", 1, "Normal Loading", SPHERE_IN, particle_du_n=0.001),
    BenchTest("benchmark1_test2.inp", 2, "Beyond rcut", SPHERE_FAR),
    BenchTest("benchmark1_test3.inp", 3, "Reverse Loading", SPHERE_IN, particle_du_n=-0.001),
    BenchTest("benchmark1_test4a.inp", 40, "Relative Motion (sphere moves)", SPHERE_IN, particle_du_n=0.001),
    BenchTest("benchmark1_test4b.inp", 41, "Relative Motion (anchor moves)", SPHERE_IN, anchor_ux=-0.001),
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
        f" Benchmark-1 {test.title} (auto-generated)",
        f" test_id={test.test_id}  verify_case=0  rcut={RCUT}",
        "*NODE",
        f"1, 0.0, 0.0, {Z}",
        f"2, {L}, 0.0, {Z}",
        f"3, 0.0, {H}, {Z}",
        "******* E L E M E N T S *************",
        "*ELEMENT, type=T3D2, ELSET=Line_fix",
        "10, 1, 3",
        "*ELEMENT, type=CPS3, ELSET=fem_zone",
        "1, 1, 2, 3",
        "*ELSET,ELSET=Line_fix",
        "10,",
        "*ELSET,ELSET=fem_zone",
        "1,",
        "*NSET,NSET=fix_nodes",
        "1, 3,",
        "*NSET,NSET=fem_interface",
        "2,",
        "*Material=fem_zone",
        "1,2300,2e9,0.3,200e9,200e9,30,-7,1e-12,1e-12,1e-12,0,0,0,-14,1.0,0.2,1.0,0,-19,3.0,3.0,3.0,0,0,0,-26,800,5e-6,1000,-30,3,3,3,0,0,0,-37,0.6e-6,-39,-40,-41,-42,-43,-44,",
        "0,20e6,30,10e6,1e15,200e9,200e9,2,10,-9,1e-4,0.1e-4,5e-4,-13,1000,-15,20000,0.001,-18,20000,10,-21,1000,0.001,-24,30,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,",
        "*FixBoundary=fix_nodes",
        "1,0,-1,-2,-3,-4,-5,",
        "*FixBoundary=fix_nodes",
        "2,0,-1,-2,-3,-4,-5,",
        "*InterfaceBond",
        f"{KN:.6e}, 4e7, 1e5, 1e5, 0.5, {RCUT}",
        "*Benchmark1",
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

    base = BenchTest("benchmark1.inp", 0, "Base (identify only)", SPHERE_IN)
    base_path = OUT_DIR / base.fname
    base_path.write_text(build_inp(base), encoding="utf-8")
    print(f"Wrote {base_path}")
    print(f"Generated {len(TESTS) + 1} Benchmark-1 inp files in {OUT_DIR}")


if __name__ == "__main__":
    main()
