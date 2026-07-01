# FDEM-flow3D A 3D hydro-mechanical coupled model considering the pore seepage of rock matrix for simulating three-dimensional hydraulic fracturing

## Abstract

Articlehistory: Ahydro-mechanicalcoupledmodelthatcansimultaneouslyconsidertheporeseepageofarockmatrix Received25February2016 and the fracture seepage is proposed to simulate three-dimensional hydraulic fracturing. This model Receivedinrevisedform15July2016 appropriatelytakesintoaccountthefluidleak-offintothesurroundingrockmatrixfromthefracture. Accepted17August2016 Severalexamplesaregiventovalidatetheseepagealgorithmsandthecoupledmodel.Theresultssuggest Availableonline29August2016 thatthismodelcansolveproblemsinvolvingporeseepageandfractureseepagethroughsimplepure fracture seepage. Moreover, it can reproduce the fluid pressure distribution and the crack initiation

## Keywords

andpropagationandconsiderthefluidlossduringhydraulicfracturing. Finitediscreteelementmethod(FEMDEM) (cid:1)2016ElsevierLtd.Allrightsreserved. Hydraulicfracturing Hydro-mechanicalcoupling Poreseepage C

## Extracted Text (First Pages)

```
ComputersandGeotechnics81(2017)212–228
ContentslistsavailableatScienceDirect
Computers and Geotechnics
journal homepage: www.elsevier.com/locate/compgeo
Research Paper
FDEM-flow3D: A 3D hydro-mechanical coupled model considering the
pore seepage of rock matrix for simulating three-dimensional hydraulic
fracturing
Chengzeng Yana,⇑ , Hong Zhengb
aKeyLaboratoryofUrbanSecurityandDisasterEngineering(BeijingUniversityofTechnology),MinistryofEducation,Beijing100124,China
bStateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRockandSoilMechanics,ChineseAcademyofSciences,Wuhan430071,China
a r t i c l e i n f o a b s t r a c t
Articlehistory: Ahydro-mechanicalcoupledmodelthatcansimultaneouslyconsidertheporeseepageofarockmatrix
Received25February2016 and the fracture seepage is proposed to simulate three-dimensional hydraulic fracturing. This model
Receivedinrevisedform15July2016 appropriatelytakesintoaccountthefluidleak-offintothesurroundingrockmatrixfromthefracture.
Accepted17August2016
Severalexamplesaregiventovalidatetheseepagealgorithmsandthecoupledmodel.Theresultssuggest
Availableonline29August2016
thatthismodelcansolveproblemsinvolvingporeseepageandfractureseepagethroughsimplepure
fracture seepage. Moreover, it can reproduce the fluid pressure distribution and the crack initiation
Keywords:
andpropagationandconsiderthefluidlossduringhydraulicfracturing.
Finitediscreteelementmethod(FEMDEM) (cid:1)2016ElsevierLtd.Allrightsreserved.
Hydraulicfracturing
Hydro-mechanicalcoupling
Poreseepage
Calibrationaperture
Fluid-drivenfractures
1.Introduction phologies, and most of them consider only the fluid flow in the
fracturebutnotthefluidleak-offintothereservoirfromthefrac-
Hydraulic fracturing is widely used in the energy industry to ture, i.e., they may not also consider pore seepage in the rock
improve the exploitation of oil, gas and geothermal energy. This matrix during hydraulic fracturing. Given the limitations of the
technique is a typical rock fracture phenomenon driven by fluid analyticalmodels,manyscholarshavestudiedhydraulicfracturing
that involves not only hydro-mechanical coupling but also crack using numericalsimulation technology. The research in this field
initiationandpropagationandinteractionsbetweennaturalfrac- canbedividedintotwocategories,themethodsbasedoncontin-
tures and hydraulic fractures [1]. In this process, in addition to uum mechanics and the approaches based on discontinuous
the fluid flow within the fracture (i.e., fracture seepage), there is mechanics.
alsofluidthatleaksintotherockmatrix(i.e.,poreseepage).There- Withinthemethodsbasedoncontinuummechanics,Panetal.
fore,thesimulationofhydraulicfracturingisbelievedtobeoneof [15] combined discontinuous cellular automata and the multi-
themostchallengingproblemsinthefieldofgeomechanics.Con- phaseflowsoftware‘‘Tough”tosimulatetheinteractionofmulti-
ventionalresearchhasfocusedonthehydro-mechanicalcoupling ple fractures in the injection process of CO . Zhang et al. [16]
2
in the existing complex fracture network without regard for the studiednaturalreservoirfracturedrivenbyfluidusingthediscon-
crackinitiationandpropagationandwithoutconsideringfractur- tinuous displacement method. They assumed that closed natural
ingfluidleakageintothefracturedrock[2–8](i.e.,theporeseep- fracturesallowfluidinflow,wherebythefluidleakingintothenat-
ageintherockmatrixisnotconsidered). ural fracture from newly generated fractures can be considered.
Within the analytical models of hydraulic fracturing, there is However, the rock matrix is still impervious, and therefore the
themainPKNmodel[9,10],theKGDmodel[11,12],andtheradial fluidleak-offintotherockmatrixfromthefracturesisnotconsid-
or penny-shaped model [13], as well as some quasi three- ered. Fu et al. [17] proposed a two-dimensional explicit hydro-
dimensional (P3D) and three-dimensional models (PL3D) [14]. mechanical coupled model to simulate hydraulic fracturing with
However,thesemodelsaremainlyappliedtosimplefracture
```
