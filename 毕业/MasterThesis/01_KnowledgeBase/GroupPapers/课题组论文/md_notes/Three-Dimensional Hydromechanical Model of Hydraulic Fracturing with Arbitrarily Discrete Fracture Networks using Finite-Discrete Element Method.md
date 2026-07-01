# Three-Dimensional Hydromechanical Model of Hydraulic Fracturing with Arbitrarily Discrete Fracture Networks using Finite-Discrete Element Method

## Abstract

: This study presents a hydromechanical model, finite-discrete element method with fluid flow in three dimensions (FDEM- flow3D),thatcansimulatethree-dimensionalhydraulicfracturingofjointedrockmasswithcomplexfracturenetworks.Bytakingfulladvant- age of a unique topological connection between joint elements and solid elements in three-dimensional combined finite-discrete element method(FEMDEM)togetherwiththecubiclaw,theauthorsbuiltathree-dimensionalfluidflowmodel.Inaddition,aconnectivitysearch algorithmforarbitrarilycomplexthree-dimensionalfracturenetworksisproposed,whichcanbeusedtosearchtheconnectivityofarbitrarily complex three-dimensional fracture networks. Combining the connectivity search algorithm and the mechanical calculations of three- dimensionalFEMDEM,theauthorsbuiltthethree-dimensionalhydromechanicalcouplingmodelFDEM-flow3D,whichdirectlyimple- mentshydromechanicalcouplingandcansimulatefluid-drivenfracturinginrockwitharbitrarilycomplexthree-dimensionalfracturenet- works. Final

## Extracted Text (First Pages)

```
Three-Dimensional Hydromechanical Model of Hydraulic
Fracturing with Arbitrarily Discrete Fracture Networks using
Finite-Discrete Element Method
ChengzengYan1andHongZheng2
Abstract: This study presents a hydromechanical model, finite-discrete element method with fluid flow in three dimensions (FDEM-
flow3D),thatcansimulatethree-dimensionalhydraulicfracturingofjointedrockmasswithcomplexfracturenetworks.Bytakingfulladvant-
age of a unique topological connection between joint elements and solid elements in three-dimensional combined finite-discrete element
method(FEMDEM)togetherwiththecubiclaw,theauthorsbuiltathree-dimensionalfluidflowmodel.Inaddition,aconnectivitysearch
algorithmforarbitrarilycomplexthree-dimensionalfracturenetworksisproposed,whichcanbeusedtosearchtheconnectivityofarbitrarily
complex three-dimensional fracture networks. Combining the connectivity search algorithm and the mechanical calculations of three-
dimensionalFEMDEM,theauthorsbuiltthethree-dimensionalhydromechanicalcouplingmodelFDEM-flow3D,whichdirectlyimple-
mentshydromechanicalcouplingandcansimulatefluid-drivenfracturinginrockwitharbitrarilycomplexthree-dimensionalfracturenet-
works. Finally, the authors give five examples to validate FDEM-flow3D in dealing with the problems of steady flow, unsteady flow,
hydromechanicalcoupling,connectivitysearchofdiscretefracturenetworks,andhydraulicfracturing.Thesimulationresultsagreewell
withthetheoreticalorexperimentalresults.Themodelprovidesapowerfultoolforsimulationofhydraulicfracturinginshalegasexploi-
tationandgeothermalextraction.DOI:10.1061/(ASCE)GM.1943-5622.0000819.©2016AmericanSocietyofCivilEngineers.
Author keywords: Combined finite-discrete element method (FEMDEM); Hydraulic fracturing; Hydromechanical coupling; Discrete
fracturenetworks;Connectivityoffracturenetworks;Fluid-drivenfracture.
Introduction
whichtakesintoaccountthechangesofflowalongcracks,known
asthePKNmodel.GeertsmaandDeKlerk(1969)introducedthe
Hydraulicfracturingisacoretechnologyinshalegasexploitation conceptofcrackdynamicequilibriumbalancingandbuiltamodel
andgeothermalextraction.Byfluid-driving,cracksaregeneratedin of crackpropagationandextensionbasedon thework of Zheltov
thelow-permeabilityreservoir,whichenhancethepermeabilityof (1955),calledtheKGDmodel.Sneddon(1946)proposedaradial
rockmassandimprovetheproductionofshalegasandgeothermal or penny-shaped model, in which fluid pressure is constant. In
energy. However, the conventional studies of hydromechanical addition, some scholars proposed quasi-three-dimensional (3D)
coupling focus on the seepage problem in complex fracture net- modelsor3Dmodelsofhydraulicfracturingonthebasisoftwo-
works(AnderssonandDverstorp1987;Cacasetal.1990;Jianget dimensional(2D)models,suchasVanEekelen(1982),Settariand
al.2013;Koudinaetal.1998;Longetal.1985;Mourzenkoetal. Cleary(1984,1986),PalmerandCarroll(1983),andSiebritsetal.
2011;PerattaandPopov2006;RouleauandGale1987;Wilsonand (2001).Crackpropagationinthesetheoreticalmodelsishandled
Witherspoon1974).Eveninthehydromechanicalcouplinganaly- by a quasi-static way, and the mechanic behavior of rock is
sis, crack initiation and propagation are not taken into account assumed to be linear elastic. Moreover, because the fracture-
(BowerandZyvoloski1997;Ivars2006;Kimetal.1999;Minkoff propagationcriterionofthosemodelsisbasedonfracturetough-
etal.2003;Rutqvistetal.2002;Samieretal.2003;Thomasetal. ness, the effect of natural fractures on the hydraulic fractures is
2002;ZhangandYin2014;ZhangandSanderson2002). notconsidered,andtheeffectoftheinertialterminequationsof
Regardingrockfracturedrivenbyfluid,researchersstudiedthe crack opening and fluid flowing on fluid movement is also
problemfromtheviewofanalyticalmodelsandnumericalsimula- ignored.Thus,thosemodelscannotbeusedtodirectlyguidehy-
tions.Intermsofanalyticalmodels,PerkinsandKern(1961)and draulicfracturingwithcomplexnaturalfracturenetworksatpro-
Nordgren (1972) established a vertical crack–propagation model, ject sites. Co
```
