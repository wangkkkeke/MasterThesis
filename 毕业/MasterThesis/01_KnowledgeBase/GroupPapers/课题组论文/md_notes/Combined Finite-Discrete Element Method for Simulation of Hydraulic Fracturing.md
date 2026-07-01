# Combined Finite-Discrete Element Method for Simulation of Hydraulic Fracturing

## Keywords

FDEM (cid:2) Y-flow (cid:2) Hydro-mechanical s Saturation of current time step coupling (cid:2) Fracture network connectivity (cid:2) Seepage (cid:2) s Saturation of previous time step

## Extracted Text (First Pages)

```
RockMechRockEng(2016)49:1389–1410
DOI10.1007/s00603-015-0816-9
ORIGINAL PAPER
Combined Finite-Discrete Element Method for Simulation
of Hydraulic Fracturing
Chengzeng Yan1 • Hong Zheng2 • Guanhua Sun2 • Xiurun Ge2
Received:16August2014/Accepted:10August2015/Publishedonline:22September2015
(cid:2)Springer-VerlagWien2015
Abstract Hydraulic fracturing is widely used in the Abbreviations
exploitation of unconventional gas (such as shale gas).- M Lumped mass diagonal matrices
Thus, the study of hydraulic fracturing is of particular C Damping diagonal matrices
importance for petroleum industry. The combined finite- F Nodal force vector
discrete element method (FDEM) proposed by Munjiza is X Vector of nodal coordinates
an innovative numerical technique to capture progressive Dp Pressure differential between two adjacent nodes
damage and failure processes in rock. However, it cannot p Pressure of Node 1
1
model the fracturing process of rock driven by hydraulic p Pressure of Node 2
2
pressure. In this study, we present a coupled hydro-me- q Mass density of fluid
w
chanical model based on FDEM for the simulation of g Gravitational acceleration
hydraulicfracturingincomplexfracturegeometries,where y Vertical coordinate of Node 1
1
an algorithm for updating hydraulic fracture network is y Vertical coordinate of Node 2
2
proposed. The algorithm can carry out connectivity sear- q Flow rate
ches for arbitrarily complex fracture networks. Then, we l Dynamic coefficient of viscosity
develop a new combined finite-discrete element method a Average aperture of crack element
numerical code (Y-flow) for the simulation of hydraulic a Initial value of aperture
0
fracturing.Finally,severalverificationexamplesaregiven, a Minimum value of aperture
res
andthesimulation results agree well withthe analyticalor a Maximum value of aperture
max
experimental results, indicating that the newly developed u Normal displacement of crack element
n
numerical code can capture hydraulic fracturing process L Length of crack element
correctly and effectively. f Function of saturation
s
f Total fluid pressure on edge of triangular element
n
Keywords FDEM (cid:2) Y-flow (cid:2) Hydro-mechanical s Saturation of current time step
coupling (cid:2) Fracture network connectivity (cid:2) Seepage (cid:2) s Saturation of previous time step
0
Hydraulic fracturing Q Total flow rate
q Flow rate from Node 1 to 2
21
q Flow rate from Node 3 to 2
23
& HongZheng q 24 Flow rate from Node 4 to 2
hzheng@whrsm.ac.cn p Pressure of the node at the current time step
p Pressure of the node at the previous time step
1 KeyLaboratoryofUrbanSecurityandDisasterEngineering, 0
K Bulk modulus of the fluid
MinistryofEducation,BeijingUniversityofTechnology, w
k Permeability factor of the ith crack element
Beijing100124,China i
Dt Time step
2 StateKeyLaboratoryofGeomechanicsandGeotechnical
Dt Critical time step
Engineering,InstituteofRockandSoilMechanics,Chinese f
AcademyofSciences,Wuhan430071,China V Volume of the node at the current time step
123
--- PAGE BREAK ---
1390 C.Yanetal.
V Volume of the node at the previous time step way for tackling hydraulic fracturing (Al-Busaidi et al.
0
DV Volume change 2005; Han and Cundall 2011, 2013; Shimizu et al. 2011).
V Average volume A theoretical model named FSD has also been com-
m
V Volume of Node 2 monly used to simulate hydraulic fracturing (Tang et al.
2
V Volume of crack element j21 2002; Yang et al. 2004). For example, Wang et al. (2009)
j21
V Volume of crack element j23 introduced a numerical model (F-RFPA2D) that can con-
j23
V Volume of crack element j24 sider the coupling effect of seepage and deformation, to
j24
h Height of free surface investigate the mechanism of crack initiation and propa-
h Water level on the left gationarounda2Dcylindricalcavityinheterogeneousstiff
1
h Water level on the right soils during hydraulic fracturing. Li et al. (2012) applied a
2
x X-axis coordinate component three-dimensional(3D)finiteelementmodelthatsimulates
B Width o
```
