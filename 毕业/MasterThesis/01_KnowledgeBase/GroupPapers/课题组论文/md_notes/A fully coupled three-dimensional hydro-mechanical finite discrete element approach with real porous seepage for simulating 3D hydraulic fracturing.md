# A fully coupled three-dimensional hydro-mechanical finite discrete element approach with real porous seepage for simulating 3D hydraulic fracturing

## Abstract

Keywords: A fully coupled 3D hydro-mechanical model with real porous seepage is presented for simulating hydraulic 3Dfinitediscreteelementmethod(FDEM3D) fracturing.Inthismodel,fluidflowinafractureisexpressedby2Dfractureseepageinthebrokenjointelements Hydro-mechanicalcoupling basedontheCubiclaw,whilefluidflowintherockmatrixisrepresentedby3Dporousseepageinthetetra- Rockfracture hedralelementsbasedonDarcy'slaw.Severalproblemsthathaveclosed-formsolutionsanda3Dfracturing Porousseepage problemaregiventoverifythemodel.Thesimulationresultsshowthatthemodelcancapturecrackinitiation Fractureseepage andpropagation,andthefluidpressureevolutionduringhydraulicfracturing. Hydraulicfracturing

## Keywords

A fully coupled 3D hydro-mechanical model with real porous seepage is presented for simulating hydraulic

## Extracted Text (First Pages)

```
Computers and Geotechnics 96 (2018) 73–89
ContentslistsavailableatScienceDirect
Computers and Geotechnics
journal homepage: www.elsevier.com/locate/compgeo
Research Paper
fi
A fully coupled three-dimensional hydro-mechanical nite discrete element
T
approach with real porous seepage for simulating 3D hydraulic fracturing
Chengzeng Yana, Yu-Yong Jiaoa,b,⁎ , Hong Zhengc
aFacultyofEngineering,ChinaUniversityofGeosciences,Wuhan,Hubei430074,China
bStateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRockandSoilMechanics,ChineseAcademyofSciences,Wuhan430071,China
cKeyLaboratoryofUrbanSecurityandDisasterEngineering,BeijingUniversityofTechnology,MinistryofEducation,China
A R T I C L E I N F O A B S T R A C T
Keywords: A fully coupled 3D hydro-mechanical model with real porous seepage is presented for simulating hydraulic
3Dfinitediscreteelementmethod(FDEM3D) fracturing.Inthismodel,fluidflowinafractureisexpressedby2Dfractureseepageinthebrokenjointelements
Hydro-mechanicalcoupling basedontheCubiclaw,whilefluidflowintherockmatrixisrepresentedby3Dporousseepageinthetetra-
Rockfracture hedralelementsbasedonDarcy'slaw.Severalproblemsthathaveclosed-formsolutionsanda3Dfracturing
Porousseepage
problemaregiventoverifythemodel.Thesimulationresultsshowthatthemodelcancapturecrackinitiation
Fractureseepage andpropagation,andthefluidpressureevolutionduringhydraulicfracturing.
Hydraulicfracturing
1. Introduction fracturing,suchasthefiniteelementmethod(FEM),theextendedfinite
element method (XFEM), the displacement discontinuity method
Hydraulicfracturingisthekeytechnologyinpetroleum,shalegas (DDM), the discontinuous deformation analysis method (DDA), the
andenhancedgeothermalsystems.Itinvolvesnotonlythedeformation discreteelementmethod(DEM),andthefinitediscreteelementmethod
ofasolidundertheeffectoffluidpressurebutalsothefracturingofthe (FDEM).
solid.Manyresearchershavestudiedhydraulicfracturingandputfor- Forexample,Fuetal.[20]andSettgastetal.[21]builtanexplicit
wardseveraltheoreticalmodels,suchasthePKNmodel[1,2],theKGD 2D/3Dhydrauliccouplingmodeltosimulatehydraulicfracturingwith
model[3,4],theradialorpenny-shapedmodel[5],andsomepseudo- arbitrary fracture networks based on FEM. Hunsweck et al. [22] pre-
3Dmodelsandplanar-3Dmodels[6–8].Later,ratherthandeveloping sented a finite element approach to simulate plane-strain hydraulic
new analytical models for hydraulic fracturing with complex fracture fractureswithlag.GuptaandDuarte[23]presentedsimulationsofnon-
networks,researchershavebeenfocusedonthepropertiesofclassical planar three-dimensional hydraulic fracture propagation. Chen [24]
hydraulic fracturing models. For example, a scaling and asymptotic proposed a 3D finite element model based on existing pore pressure
frameworkwasdevelopedbyDetournayetal.[9,10],whorecognized cohesive finite elements to simulate the propagation of viscosity-
thatthehydraulicfractureisgovernedbytwocompetingenergy(i.e., dominated hydraulic fracture in an infinite, impermeable elastic
viscous flow and the creation of surface area in the solid) and fluid medium. Wangen [25] suggested a finite element approach for the
storagemechanisms(i.e.,thestorageoffluidinthefractureandfluid modelingofhydraulicfracturingin3D.Yaoetal.[26]developeda3D
leak-offintothepermeablesolid).Later,manyfruitfulsemi-analytical pore pressure cohesive zone model for simulation of hydraulic frac-
and numerical solutions have been obtained for different asymptotic turinginquasi-brittlerocks.However,FEMneedsremeshing(withhigh
regimes[11–18],suchaszerotoughnessimpermeable,smalltoughness computationcost)asfracturescontinuallypropagate[27–29].
impermeable, finite toughness impermeable, large toughness im- Inordertoovercomethelimitationsofthefiniteelementmethod,
permeable, zero toughness permeable regime, and finite toughness someresearchershaveusedXFEMtosimulatehydraulicfracturing.For
permeableregimesolutions[19].Althoughthesetheoreticalmodelsor example,SalimzadehandKhalili[36]proposedafullycoupled
```
