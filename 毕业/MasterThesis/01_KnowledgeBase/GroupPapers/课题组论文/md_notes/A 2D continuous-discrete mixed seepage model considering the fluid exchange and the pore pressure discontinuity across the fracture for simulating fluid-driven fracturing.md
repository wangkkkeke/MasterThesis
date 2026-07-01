# A 2D continuous-discrete mixed seepage model considering the fluid exchange and the pore pressure discontinuity across the fracture for simulating fluid-driven fracturing

## Keywords

Finite discrete element method (FDEM) (cid:2) Fluid-driven fracturing (cid:2) Fracture-pore mixed seepage (cid:2) Hydraulic fracturing (cid:2) KGD

## Extracted Text (First Pages)

```
ActaGeotechnica
https://doi.org/10.1007/s11440-023-01974-6
(0123456789().,-volV)(0123456789,-().volV)
RESEARCH PAPER
A 2D continuous-discrete mixed seepage model considering the fluid
exchange and the pore pressure discontinuity across the fracture
for simulating fluid-driven fracturing
Chengzeng Yan1,2 • Yuxin Wang1 • Xin Xie1 • Sajid Ali1 • Zhigang Sheng3
Received:28April2022/Accepted:9June2023
(cid:2)TheAuthor(s),underexclusivelicencetoSpringer-VerlagGmbHGermany,partofSpringerNature2023
Abstract
Basedonthefinite-discreteelementmethod(FDEM),thispaperproposesacontinuous-discretemixedseepagemodelthat
considersthefluidexchangeandtheporepressurediscontinuityacrossthefracture.Thecontinuous-discreteseepagemodel
usesthecubiclawtoexpressthefluidflowinthefractureandDarcy’slawtodescribetheporeseepageintherockmatrix.
Combining the continuous-discrete mixed seepage model with the FDEM, a hydro-mechanical coupling model is con-
structed to solve fluid-driven fracturing of a rock mass. The continuous-discrete seepage model and hydro-mechanical
coupling model update the node sharing relationship of triangular elements on two sides of the fracture during fracture
propagation which sufficiently consider the influence of the fracture propagation on the pore seepage. In this paper, the
analytical solutions are used to verify the model’s accuracy with the help of four examples. In addition, the hydro-
mechanicalcouplingmodelisusedtosimulateahydraulicfracturingproblemforrockmassinvolvingacomplexfracture
network. According to the simulation results, this hydro-mechanical coupling model can catch fracture initiation, propa-
gation, the interaction between hydraulic fractures and discrete fracture, as well as the evolution of pore pressure and
fracture pressure.
Keywords Finite discrete element method (FDEM) (cid:2) Fluid-driven fracturing (cid:2) Fracture-pore mixed seepage (cid:2)
Hydraulic fracturing (cid:2) KGD
1 Introduction problems in soil consolidation and foundation subsidence.
Sincethen,thetheoryhasbeenappliedtostudytheopenor
The coupling of two processes means that one process close of fractures or joints in the rock mass, hydraulic
affectstheoccurrenceanddevelopmentofanotherprocess. fracturing, and earthquakes triggered by fluid injection.
The research on the hydro-mechanical coupling of porous Many problems in geotechnical engineering are related
media began in the 1940s, and Terzaghi first proposed the tohydro-mechanicalcoupling.Forexample,landslidesand
concept of effective stress when studying soil mechanics. slopes failure, dam foundations failure, stability of under-
Then, Biot studied the hydro-mechanical coupling ground excavation, stability of boreholes in oil and gas
extraction, hydraulic fracturing, geothermal mining, and
coal mining are all related to rock fracturing under the
& ChengzengYan effectofhydro-mechanicalcoupling.Therefore,buildinga
yancz@cug.edu.cn seepageandhydro-mechanicalcouplingmodelconsidering
rock fracturing is of great significance for solving the
1 FacultyofEngineering,ChinaUniversityofGeosciences,
engineering problems related to hydro-mechanical cou-
Wuhan430074,China
pling that widely exist in geotechnical engineering.
2 NationalCenterforInternationalResearchonDeepEarth
Moreover, many authors have investigated this issue,
DrillingandResourceDevelopment,ChinaUniversityof
which is summarized in three parts below: (1) computa-
Geosciences,Wuhan430074,China
tionalmethodforseepageincomplexfracturedrockmass;
3 InstituteofDisasterPrevention,CollegeStreetinYanjiao
Quarter,EastofBeijing101601,China
123
--- PAGE BREAK ---
ActaGeotechnica
(2) hydro-mechanical coupling analytical model; (3) therefore, it is more suitable for the formation of fractures
hydro-mechanical coupling numerical model. whose heightis muchgreater than the fracture length.The
asymptotic solution of the KGD model shows that the
1.1 Computational method for seepage fluid-driven fracture propagation process is mainly con-
in a complex fractured r
```
