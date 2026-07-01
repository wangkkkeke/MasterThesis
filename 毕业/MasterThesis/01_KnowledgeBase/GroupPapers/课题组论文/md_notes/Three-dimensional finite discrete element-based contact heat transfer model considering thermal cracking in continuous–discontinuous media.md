# Three-dimensional finite discrete element-based contact heat transfer model considering thermal cracking in continuous–discontinuous media

## Abstract

This paper proposes a three-dimensional heat transfer model that considers contact heat transfer and thermal cracking in continuous–discontinuous media. The 3D heat transfer model comprises the heat conduction model inside the continuum and the contact heat transfer model between discrete blocks. The model is combined with the 3D Finite Discrete Element (FDEM) forcoupledthermo-mechanicalcalculation,whichincludesthefollowingthreeparts:thetemperaturedistributionofthesystem is obtained by the 3D heat transfer model considering contact heat transfer; then, the thermal stress caused by the temperature is applied to the system equation to perform the mechanical fracture calculation; finally, the heat exchange coefficient of the newly generated broken joint element is updated for heat transfer calculation at the next time. Some examples are given to verify the 3D contact heat transfer model with analytical solutions. Moreover, the influence of the heat exchange coefficient of the joint elemen

## Keywords

3DFDEM;Contactheattransfer;Coupledthermo-mechanical;Thermalcracking;Granularmaterial;Discontinuousmedium

## Extracted Text (First Pages)

```
Available online at www.sciencedirect.com
ScienceDirect
Comput. Methods Appl. Mech. Engrg. 388 (2022) 114228
www.elsevier.com/locate/cma
Three-dimensional finite discrete element-based contact heat transfer
model considering thermal cracking in continuous–discontinuous
media
Chengzeng Yana,b,c, Dasheng Weia, Gang Wangb,∗
aFacultyofEngineering,ChinaUniversityofGeosciences,Wuhan430074,China
bDepartmentofCivilandEnvironmentalEngineering,HongKongUniversityofScienceandTechnology,ClearWaterBay,HongKongSpecial
AdministrativeRegionofChina
cInternationalJointResearchCenterforDeepEarthDrillingandResourceDevelopment,ChinaUniversityof
Geosciences,Wuhan430074,China
Received23April2021;receivedinrevisedform3August2021;accepted4October2021
Availableonline xxxx
Abstract
This paper proposes a three-dimensional heat transfer model that considers contact heat transfer and thermal cracking in
continuous–discontinuous media. The 3D heat transfer model comprises the heat conduction model inside the continuum and
the contact heat transfer model between discrete blocks. The model is combined with the 3D Finite Discrete Element (FDEM)
forcoupledthermo-mechanicalcalculation,whichincludesthefollowingthreeparts:thetemperaturedistributionofthesystem
is obtained by the 3D heat transfer model considering contact heat transfer; then, the thermal stress caused by the temperature
is applied to the system equation to perform the mechanical fracture calculation; finally, the heat exchange coefficient of the
newly generated broken joint element is updated for heat transfer calculation at the next time. Some examples are given to
verify the 3D contact heat transfer model with analytical solutions. Moreover, the influence of the heat exchange coefficient
of the joint element and the contact heat transfer coefficient is discussed. Finally, examples of contact heat conduction in 3D
granular assemblage, and thermal cracking caused by contact heat transfer are demonstrated. These examples demonstrated
excellent capacity of the model in simulating contact heat transfer and thermal cracking in continuous–discontinuous media.
⃝c 2021ElsevierB.V.Allrightsreserved.
Keywords:3DFDEM;Contactheattransfer;Coupledthermo-mechanical;Thermalcracking;Granularmaterial;Discontinuousmedium
1. Introduction
Heat conduction and thermo-mechanical coupling in discontinuous and granular materials have important
applications in geothermal energy exploitation, oil extraction, nuclear waste storage etc. [1–3]. As discrete element
method (DEM)has distinct advantage to modelgranular particles, many contactheat conduction models havebeen
developedbasedonparticle-DEM.Forexample,Chenetal.[4]studiedtheeffectivethermalconductivityofapacked
bed under three heat transfer mechanisms, i.e., solid contact heat transfer, solid–fluid–solid heat conduction, and
∗ Corresponding author.
E-mail addresses: yancz@cug.edu.cn (C. Yan), gwang@ust.hk (G. Wang).
https://doi.org/10.1016/j.cma.2021.114228
0045-7825/⃝c 2021 Elsevier B.V. All rights reserved.
--- PAGE BREAK ---
C. Yan, D. Wei and G. Wang Computer Methods in Applied Mechanics and Engineering 388 (2022) 114228
radiationheatconductionusingDEM.Liuetal.[5]simulatedthetransientheatconductionofapebblelayerusinga
2DparticleheatconductionmodelbasedonaDEM-embeddedfiniteelementmethod.YazdaniandHashemabadi[6]
simulated heat transfer of binary-sized particles in a horizontal rotating drum using DEM. Cui et al. [7] established
theradiationheatconductionmodeloflunarrocksimulantsusingDEMandstudiedthethermalproblemofdrilling
in lunar rocks. For example, Oschmann and Kruggel-Emden [8] proposed a particle–wall heat transfer coupling
algorithm to solve the particle–wall contact heat transfer and inner wall heat conduction. Feng et al. [9] simulated
thetransientheatconductionofgranularmaterialsusingtheradialtemperaturemodelinparticle-DEM.Thismethod
has high computational efficiency and avoids the assumption of uniform temperature distribution in the particles.
Kiani-Oshtorjani 
```
