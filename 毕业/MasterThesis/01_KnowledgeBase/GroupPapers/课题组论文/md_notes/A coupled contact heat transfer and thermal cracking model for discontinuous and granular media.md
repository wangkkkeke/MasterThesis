# A coupled contact heat transfer and thermal cracking model for discontinuous and granular media

## Abstract

In this study, a coupled contact heat transfer and thermal cracking model is proposed for discontinuous/granular media based on the computational framework of Finite-Discrete Element Method (FDEM). The model considers heat conduction within the continuum and heat transfer through contacts between discontinuous or granular materials, as well as the combined effects of contact heat transfer and thermal cracking. The numerical model is validated against theoretical solutions through several examples. Moreover, the effects of the thermal contact conductance, the influence of thermal cracks on heat transfer are investigated. Two examples of heat transfer and thermal cracking in granular/block materials are provided. A sensitivity analysis indicates that the thermal cracking model can provide statistically converged results for simulating thermal cracks. All these numerical examples demonstrate the excellent capability of the model, which can be applied to a wide range of continuous and disc

## Keywords

Combinedfinite-discreteelementmethod;Contactheattransfer;Coupledthermal–mechanicalmodel;Thermalcracking;Granular material

## Extracted Text (First Pages)

```
Available online at www.sciencedirect.com
ScienceDirect
Comput. Methods Appl. Mech. Engrg. 375 (2021) 113587
www.elsevier.com/locate/cma
A coupled contact heat transfer and thermal cracking model for
discontinuous and granular media
Chengzeng Yana,b, Yuchen Zhenga, Duruo Huangc,∗ , Gang Wangb
aFacultyofEngineering,ChinaUniversityofGeosciences,Wuhan,China
bDepartmentofCivilandEnvironmentalEngineering,HongKongUniversityofScienceandTechnology,ClearWaterBay,HongKongSpecial
AdministrativeRegion,China
cDepartmentofHydraulicEngineering,TsinghuaUniversity,Beijing,China
Received14June2020;receivedinrevisedform29October2020;accepted14November2020
Availableonline xxxx
Abstract
In this study, a coupled contact heat transfer and thermal cracking model is proposed for discontinuous/granular media
based on the computational framework of Finite-Discrete Element Method (FDEM). The model considers heat conduction
within the continuum and heat transfer through contacts between discontinuous or granular materials, as well as the combined
effects of contact heat transfer and thermal cracking. The numerical model is validated against theoretical solutions through
several examples. Moreover, the effects of the thermal contact conductance, the influence of thermal cracks on heat transfer
are investigated. Two examples of heat transfer and thermal cracking in granular/block materials are provided. A sensitivity
analysis indicates that the thermal cracking model can provide statistically converged results for simulating thermal cracks.
All these numerical examples demonstrate the excellent capability of the model, which can be applied to a wide range of
continuous and discontinuous media, such as granular materials, ceramics, concrete, rock mass, and so on.
⃝c 2020PublishedbyElsevierB.V.
Keywords:Combinedfinite-discreteelementmethod;Contactheattransfer;Coupledthermal–mechanicalmodel;Thermalcracking;Granular
material
1. Introduction
Studying heat conduction and thermal cracking in granular materials or discontinuous media has found many
important engineering applications [1], such as underground disposal of nuclear waste, exploitation of geothermal
energy resources, mass concrete construction, controlling of heat accumulation within ore heaps, etc. [2–6].
Expansion or shrinkage caused by inhomogeneous temperature distribution may cause crack initiation, prop-
agation, and coalescence under the effect of thermal–mechanical coupling, as was observed in many laboratory
tests [7–9]. On one hand, heat transfer affects the mesoscale failure mechanism within the materials; on the other
hand, thermal cracking, in turn, affects the heat transfer in these materials.
To capture the geometrical jump of displacement and the singularity of stress fields in the vicinity of cracks,
some Galerkin-based methods with enrichment technique have been used to study the heat conduction and thermal
∗ Corresponding author.
E-mail addresses: yancz@cug.edu.cn (C. Yan), huangduruo@tsinghua.edu.cn (D. Huang), gwang@ust.hk (G. Wang).
https://doi.org/10.1016/j.cma.2020.113587
0045-7825/⃝c 2020 Published by Elsevier B.V.
--- PAGE BREAK ---
C. Yan, Y. Zheng, D. Huang et al. Computer Methods in Applied Mechanics and Engineering 375 (2021) 113587
cracking in continuous media. For example, Nguyen et al. [10] proposed a consecutive-interpolation scheme in
an extended four-node quadrilateral element to study the thermal cracking in orthotropic composite materials.
Brouhala et al. [11] studied the expansion of cracks in elastic materials using the extended element free Galerkin
method. To capture discontinuity in the thermal field across cracks, Zhang et al. [12–14] presented a coupled
thermal-mechanical model on the basis of the numerical manifold method (NMM), which has the advantages of
simulatingstrongdiscontinuityusingmultiplemathematicalcovers.Periodynamics,duetoitsflexibilityinmodeling
crack propagation, has also been increasingly used recently in simulation of temperature-driven crack
```
