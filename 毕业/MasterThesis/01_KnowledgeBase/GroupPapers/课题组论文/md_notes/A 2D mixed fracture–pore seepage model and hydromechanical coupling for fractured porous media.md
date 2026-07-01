# A 2D mixed fracture–pore seepage model and hydromechanical coupling for fractured porous media

## Keywords

Finite-discrete element method (cid:2) Fluid-driven fracturing (cid:2) Fracture seepage (cid:2) Fractured porous media (cid:2) Hydromechanical coupling (cid:2) Pore seepage

## Extracted Text (First Pages)

```
ActaGeotechnica
https://doi.org/10.1007/s11440-021-01183-z
(0123456789().,-volV)(0123456789().,-volV)
RESEARCH PAPER
A 2D mixed fracture–pore seepage model and hydromechanical
coupling for fractured porous media
Chengzeng Yan1,2 • Hongwei Fan1 • Duruo Huang3 • Gang Wang2
Received:18September2020/Accepted:6March2021
(cid:2)Springer-VerlagGmbHGermany,partofSpringerNature2021
Abstract
Anoveltwo-dimensionalmixedfracture–poreseepagemodelforfluidflowinfracturedporousmediaispresentedbasedon
thecomputationalframeworkoffinite-discreteelementmethod(FDEM).Themodelconsistsofaporousseepagemodelin
triangularelementsbondedbyunbrokenjointelements,aswellasafractureseepagemodelinbrokenjointelements.The
principle for determining the fluid exchange coefficient of the unbroken joint element is provided to ensure numerical
accuracyandefficiency.Themixedfracture–poreseepagemodelprovidesasimplebuteffectivetoolforsolvingfluidflow
in fractured porous media. In this paper, examples of 1D and 2D seepage flow in porous media and porous media with a
single fracture ormultiplefracturesarestudied.Thesimulationresults ofthemodelmatch wellwith theoretical solutions
or results obtained by commercial software, which verifies the correctness of the mixed fracture–pore seepage model.
Furthermore, combining FDEM mechanical calculation and the mixed fracture–pore seepage model, a coupled
hydromechanicalmodelisbuilttosimulatefluid-drivendynamicpropagationofcracksintheporousmedia,aswellasits
influence on pore seepage and fracture seepage.
Keywords Finite-discrete element method (cid:2) Fluid-driven fracturing (cid:2) Fracture seepage (cid:2) Fractured porous media (cid:2)
Hydromechanical coupling (cid:2) Pore seepage
1 Introduction rockmatrixismuchsmallerthanthatoffractures.However,
in many engineering applications, such as oil and gas
The fluid flow in the rock mass includes seepage through exploitation, deep underground disposal of nuclear waste
fractures and pore space in the rock matrix. For many rock andundergroundstorageofoilandgas,fluidflowinporous
mechanicsproblems,thefractureseepageplaysamajorrole rock matrix should be considered. In other words, the rock
andcontrolsthemechanicalresponseofrockmass.Thepore massinthisconditionneedstobeconsideredasafractured
seepage is often neglected because the permeability of the porous media. Therefore, establishing an effective seepage
modelforfracturedporousmediaisahottopicinthefieldof
petroleumoilextractionandrockhydraulics[5,7,9,11,33].
& DuruoHuang
Currently, the seepage models for fractured porous
huangduruo@tsinghua.edu.cn
media mainly include the following three types: the
ChengzengYan
equivalent continuum model, dual-porosity model and
yancz@cug.edu.cn
discretefracturemodel.Intheequivalentcontinuummodel
GangWang [29, 30, 52, 53], both rock matrix and fractures are con-
gwang@ust.hk
sidered as a homogenized porous media. Thus, it cannot
1 FacultyofEngineering,ChinaUniversityofGeosciences, modelrealfracturedistributionandhaslowaccuracywhen
Wuhan,430074,China solving seepage flow in rock masses with strong water-
2 DepartmentofCivilandEnvironmentalEngineering,Hong conducting fractures. To this end, Barenblatt et al. [4]
KongUniversityofScienceandTechnology, proposed a dual-porosity seepage model, in which the
ClearWaterBay,HongKong,SAR,China fractureandmatrixareconsideredasindependentsystems.
3 DepartmentofHydraulicEngineering,TsinghuaUniversity, The matrix on both sides of the fracture shares the same
Beijing,China
123
--- PAGE BREAK ---
ActaGeotechnica
nodes,andtheporepressureonbothsidesofthefractureis solid elements. In recent years, the method has been
continuous. In recent years, to consider the seepage of extended to solve multi-physics-driven fracture problems.
fracturedrockwithasmallnumberoflarge-scalefractures, For example, Yan et al. [54, 56, 60, 61, 64] proposed a
the discrete fracture–matrix (DFM) model has attracted coupled thermo-mechanical model (FDEM-TM) and a
more attention [18, 21, 23]. In DFM, both o
```
