# A 2D coupled hydro-thermal model for the combined finite-discrete element method

## Extracted Text (First Pages)

```
ActaGeotechnica
https://doi.org/10.1007/s11440-018-0653-6
(0123456789().,-volV)(0123456789().,-volV)
RESEARCH PAPER
A 2D coupled hydro-thermal model for the combined finite-discrete
element method
Chengzeng Yan1 • Yu-Yong Jiao1 • Shengqi Yang2
Received:9December2017/Accepted:28March2018
(cid:2)Springer-VerlagGmbHGermany,partofSpringerNature2018
Abstract
Based on the combined finite-discrete element method (FDEM), a two-dimensional coupled hydro-thermal model is
proposed. This model can simulate fluid flow and heat transfer in rock masses with arbitrary complex fracture networks.
The model consists of three parts: a heat conduction model of the rock matrix, a heat-transfer model of the fluid in the
fracture(includingtheheatconductionandconvectionoffluid),andaheatexchangemodelbetweenthefluidandrockat
the fracture surface. Three examples with analytical solutions are given to verify the correctness of the coupled model.
Finally, the coupled model is applied to hydro-thermal coupling simulations of a rock mass with a fracture network. The
temperature field evolution, the effect of thermal conductivity of the rock matrix thermal conductivity and the fracture
aperture on the outlet temperature are studied. The coupled model presented in this paper will enable the application of
FDEM to study rock rupture driven by the effect of hydro-thermo-mechanical coupling in geomaterials such as in
geothermal systems, petroleum engineering, environmental engineering and nuclear waste geological storage.
Keywords Finite-discrete element method (FDEM) (cid:2) Fracture flow (cid:2) Heat conduction and convection (cid:2) Hydro-thermal
coupling (cid:2) Numerical simulation
List of symbols T(cid:2)m Average temperature of edge m
q Heat flow rate in the i direction Dxm Difference between the coordinate components
i j
k Thermal conductivity tensor of rock matrix of the two vertices at edge m
ij
T Temperature 2 Two-dimensional permutation tensor
ij
M Mass q Heat flow rate along the x direction
x
Q Net heat flowing into mass M per unit time q Heat flow rate along the y direction
net y
t Time nðnÞ Outernormalunitvectoroftheedge oppositeto
i
C Specific heat of rock matrix node n
s
A Area of a triangular element LðnÞ Length of the edge opposite to node n
n Outer normal vector Q Heat flow flowing into node 1 from triangular
D123
element D123
Q Total heat flow into node 1 per unit time
s
Ts Nodal temperature at t
t
Ts Nodal temperature at tþDt and t
tþDt
q Mass density of rock matrix
s
& Yu-YongJiao V s Rock matrix volume of node 1
yyjiao@cug.edu.cn Dx Size of the smallest element
h Convective heat-transfer coefficient
ChengzengYan
yancz@cug.edu.cn;yanchengzheng86@gmail.com j Thermal diffusion coefficient (k=qC p when
k ¼k )
x y
1 FacultyofEngineering,ChinaUniversityofGeosciences,
DT Temperature difference between node 1 and
Wuhan430074,China
node 2
2 StateKeyLaboratoryforGeomechanicsandDeep
T Temperature at node 1
UndergroundEngineering,ChinaUniversityofMiningand 1
T Temperature at node 2
Technology,Xuzhou21116,China 2
123
--- PAGE BREAK ---
ActaGeotechnica
k Thermal conductivity of fluid the coupling effect between seepage field, stress field, and
f
Q Total heat flow rate due to heat conduction temperature field of rock mass. Rutqvist [34] linked the
f1
q Fluid flow rate between node 1 and node 2 toughfamilymultiphasefluidandheattransportcodeswith
f
p Pressure at node 1 the commercial FLAC3D geomechanical simulator for
1
p Pressure at node 2 modeling coupled multiphase flow, heat transport, and
2
Dp Pressure difference between node 1 and node 2 geomechanics. Sun et al. [38] presented a mathematical
l Dynamic viscosity of fluid model incorporating the thermal–hydraulic-mechanical
a Aperture of fractures (THM) coupling effect to simulate a fractured enhanced
Q Total heat flow rate of node 1 due to heat geothermal systems (EGS) reservoir in which the
f2
convection geothermalreservoirisregardedasfracturedporousmedia
Tf Temperature of node 1 at t consistingofroc
```
