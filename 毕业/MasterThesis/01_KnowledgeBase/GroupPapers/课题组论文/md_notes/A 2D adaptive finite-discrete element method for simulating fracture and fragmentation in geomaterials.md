# A 2D adaptive finite-discrete element method for simulating fracture and fragmentation in geomaterials

## Abstract

Keywords: This study proposes a new two-dimensional finite-discrete element method (FDEM) using dynamically inserted FDEM cohesive elements. Unlike the conventional FDEM, which sets up cohesive elements between adjacent solid el- Dynamically insert cohesive elements ements to simulate fracture and fragmentation in the geomaterials, the new FDEM adaptively inserts the cohesive Brazilian disc elements when the stress exceeds a critical value. The new method is consistent with the conventional FDEM Uniaxial compression except that it uses a post-peak constitutive model for cohesive elements and a new nodal updating scheme. The SHPB-Based dynamic brazilian disc accuracy and efficiency of the new method are verified through a continuum mechanics example with an analytical solution. Examples of Brazilian disc and triaxial compression tests are used to verify the performance of this new method in simulating fracturing in geomaterials. Finally, dynamic loading on the Brazilian disc by a split 

## Extracted Text (First Pages)

```
InternationalJournalofRockMechanics&MiningSciences169(2023)105439
Contents lists available at ScienceDirect
International Journal of Rock Mechanics and Mining Sciences
journal homepage: www.elsevier.com/locate/ijrmms
A 2D adaptive finite-discrete element method for simulating fracture and
fragmentation in geomaterials
Chengzeng Yana,b, Yuchen Zhenga, Gang Wangb,*
aFaculty of Engineering, China University of Geosciences, Wuhan, China
bDepartment of Civil and Environmental Engineering, Hong Kong University of Science and Technology, Clear Water Bay, Hong Kong Special Administrative Region of
China
A R T I C L E I N F O A B S T R A C T
Keywords: This study proposes a new two-dimensional finite-discrete element method (FDEM) using dynamically inserted
FDEM cohesive elements. Unlike the conventional FDEM, which sets up cohesive elements between adjacent solid el-
Dynamically insert cohesive elements ements to simulate fracture and fragmentation in the geomaterials, the new FDEM adaptively inserts the cohesive
Brazilian disc
elements when the stress exceeds a critical value. The new method is consistent with the conventional FDEM
Uniaxial compression
except that it uses a post-peak constitutive model for cohesive elements and a new nodal updating scheme. The
SHPB-Based dynamic brazilian disc
accuracy and efficiency of the new method are verified through a continuum mechanics example with an
analytical solution. Examples of Brazilian disc and triaxial compression tests are used to verify the performance
of this new method in simulating fracturing in geomaterials. Finally, dynamic loading on the Brazilian disc by a
split Hopkinson pressure bar (SHPB) system is simulated, confirming that the new method effectively simulates
dynamic fracturing problems. The study shows that computational results of the conventional FDEM highly
depend on the penalty parameters of the cohesive elements. The adaptive FDEM overcomes these limitations
with improved accuracy and efficiency by using adaptively inserted cohesive elements.
1. Introduction FDEM has been developed rapidly in recent years with numerous ap-
plications in blasting engineering,6,7 coastal engineering,8,9 rock
To simulate the transition from continuum to discontinuum and the mechanics,10–12 masonry structures,13 ancient buildings,14 hydraulic
fragmentation of solids, Munjiza1–4 proposed the finite-discrete element fracturing,15 geothermal mining,16 slopes,17 tunnels,18 particle pack-
method (FDEM) in 1989. It combines the advantages of the explicit finite ing,19 biomedical engineering,20 and other fields.
element method in solving stress and strain and the discrete element Initially, only mechanical fracture calculation was performed in
method in handling arbitrary/complex interactions between macro- FDEM, and the coupling effects of multi-physics were not considered.
scopic fracture surfaces and multi-body contact. In addition, FDEM also The FDEM only included the following modules: contact detection,
takes advantage of the cohesive zone model (CZM) in simulating the contact force calculation, deformation and stress of solid element,
fracture process. This method divides the solution domain into solid deformation and fracturing of the cohesive element, and update of nodal
finite element meshes (such as triangular elements for 2D and tetrahe- accelerations, velocity, and positions. Subsequently, researchers have
dral elements for 3D). A cohesive element (such as a four-node cohesive developed a series of new modules to further improve the FDEM simu-
element for 2D and a six-node cohesive element for 3D) is inserted be- lation. For example, Mahabadi et al.21 added new modules such as a
tween two adjacent solid elements. Therefore, crack initiation and quasi-static friction law and a dissipative impact model in the Y-code to
propagation are simulated via the breakage of cohesive elements. solve geo-mechanical problems; Yan et al.22 extended the static friction
Furthermore, the deformatio
```
