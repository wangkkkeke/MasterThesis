# A 2D discrete heat transfer model considering the thermal resistance effect of fractures for simulating the thermal cracking of brittle

## Extracted Text (First Pages)

```
ActaGeotechnica
https://doi.org/10.1007/s11440-019-00821-x
(0123456789().,-volV)(0123456789().,-volV)
RESEARCH PAPER
A 2D discrete heat transfer model considering the thermal resistance
effect of fractures for simulating the thermal cracking of brittle
materials
Chengzeng Yan1,2 • Yu-Yong Jiao1,2
Received:16October2018/Accepted:20May2019
(cid:2)Springer-VerlagGmbHGermany,partofSpringerNature2019
Abstract
A concise, two-dimensional discrete heat transfer model is presented, which considers the thermal resistance effects of
cracks. The discrete heat transfer model discretizes the continuum into individual triangular elements, and the adjacent
triangularelements transfer heat through corresponding joint elements.Then,the principleofselecting the heatexchange
coefficient of the joint element is determined through a parameter sensitivity analysis. Moreover, the 2D discrete heat
transfer model is combined with the finite discrete element method to build a thermomechanical coupled model for
simulating brittle material thermal cracking. The thermal stress and thermal shock problems are studied by using the
thermomechanical coupled model, and the numerical results are compared with either the analytical solution or experi-
mental results to validate the 2D discrete heat transfer model and thermomechanical coupled model. The discrete heat
transfer model and thermomechanical coupled model provide a powerful tool for solving heat transfer problems in
discontinuous media as well as the thermal cracking problem in brittle materials.
Keywords FDEM(cid:2)Heattransferindiscontinuousmedia(cid:2)Rockfracture(cid:2)Thermalcracking(cid:2)Thermomechanicalcoupling
List of symbols e Two-dimensional permutation tensor
ij
q Heat flow rate along the i direction q Heat flow rate along the x direction
i x
k Thermal conductivity tensor q Heat flow rate along the y direction
ij y
T Temperature nðnÞ Outward normal unit vector
i
t Time LðnÞ Length of the edge opposite to node n
Q Total heat flow into the mass M per unit time
total Q Heat flow flowing into node 1 from triangular
D123!1
C Specific heat
p element D123
M Mass
T Temperature at node i
i
A Area of the triangular element
h Heat exchange coefficients of the joint element
j
n Outward normal unit vector
i Q Heat flow flowing into node 1 from triangular
T(cid:2)m Average temperature of edge m D456!1
element D456
Dxm Coordinatedifferencebetweenthetwonodesof
j Q D789!1 Heat flow flowing into node 1 from triangular
edge m
element D789
TtþDt Temperature of node 1 at tþDt
1
Tt Temperature of node 1 at t
& Yu-YongJiao 1
k Thermal conductivity coefficient of triangular
yyjiao@cug.edu.cn
element
ChengzengYan
L Element size
yancz@cug.edu.cn;yanchengzheng86@gmail.com e
r Reduction coefficient
T
1 FacultyofEngineering,ChinaUniversityofGeosciences, Dr Stress increment
ij
Wuhan430074,China K Bulk modulus
2 InternationalJointResearchCenterforDeepEarthDrilling G Shear modulus
andResourceDevelopment,ChinaUniversityof a Thermal expansion coefficient
Geosciences,Wuhan430074,China
123
--- PAGE BREAK ---
ActaGeotechnica
K(cid:3) Plane strain problem K(cid:3) ¼K, plane stress proposed a discrete element thermomechanical model for
problem K(cid:3) ¼6KG=ð3Kþ4GÞ simulating diffuse damage induced by the thermal
n Outward normal unit vector of the triangular expansion mismatch of two-phase materials. Bouhala
j
element edges et al. [2] investigated the thermal and thermomechanical
T Temperature at the left boundary influence on crack propagation using an extended mesh-
1
T Temperature at the right boundary free method. Li and Salah [15], Li et al. [16] and Jiang
2
j Thermal diffusion coefficient (j¼k=qC when et al. [11] investigated the formation mechanism of crack
p
k ¼k ) patterns in ceramics subjected to thermal shock based on
x y
W Width the finite element method. Tang et al. [30] developed a
L Length finite element-based numerical model to simulate the
x The distance from the left boundary thermal cracking behavior of brittle
```
