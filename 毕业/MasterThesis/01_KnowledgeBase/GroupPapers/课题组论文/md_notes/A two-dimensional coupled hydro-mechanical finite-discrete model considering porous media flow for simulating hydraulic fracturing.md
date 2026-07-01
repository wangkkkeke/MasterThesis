# A two-dimensional coupled hydro-mechanical finite-discrete model considering porous media flow for simulating hydraulic fracturing

## Abstract

Articlehistory: In this study, we propose a new coupled hydro-mechanical model considering porous media flow Received16August2015 (FDEM-flow)for simulating hydraulic fracturing, whichmakes full use of the unique topologicalcon- Receivedinrevisedform nection between joint elements and solid elements in the combined finite-discrete element method 7July2016 (FDEM).Thejointelementsformtheflowchannelforfluid,throughwhichflowobeysthecubiclaw.In Accepted24July2016 addition,viscousforcesoffluidaretakenintoaccountinFDEM-flow.Asimpleexamplewithanalytical Availableonline1August2016 solutionisgiventoverifythemodel.Then,theeffectsoffluidviscosityonhydraulicfracturingarein-

## Extracted Text (First Pages)

```
InternationalJournalofRockMechanics&MiningSciences88(2016)115–128
ContentslistsavailableatScienceDirect
International Journal of
Rock Mechanics & Mining Sciences
journal homepage: www.elsevier.com/locate/ijrmms
A two-dimensional coupled hydro-mechanical finite-discrete model
considering porous media flow for simulating hydraulic fracturing
Chengzeng Yana, Hong Zhengb,n
aStateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRockandSoilMechanics,ChineseAcademyofSciences,Wuhan430071,
China
bKeyLaboratoryofUrbanSecurityandDisasterEngineering(BeijingUniversityofTechnology),MinistryofEducation,Beijing100124,China
a r t i c l e i n f o a b s t r a c t
Articlehistory: In this study, we propose a new coupled hydro-mechanical model considering porous media flow
Received16August2015 (FDEM-flow)for simulating hydraulic fracturing, whichmakes full use of the unique topologicalcon-
Receivedinrevisedform nection between joint elements and solid elements in the combined finite-discrete element method
7July2016 (FDEM).Thejointelementsformtheflowchannelforfluid,throughwhichflowobeysthecubiclaw.In
Accepted24July2016 addition,viscousforcesoffluidaretakenintoaccountinFDEM-flow.Asimpleexamplewithanalytical
Availableonline1August2016
solutionisgiventoverifythemodel.Then,theeffectsoffluidviscosityonhydraulicfracturingarein-
Keywords: vestigatedbythismodel.Thesimulatedresultsshowthatwhenalowviscosityfluidisinjected,thefluid
Combinedfinite-discreteelementmethod infiltrates the fracture rapidly. The initiation pressure is lower than the theoretical value and the
(FDEM) breakdownpressureisslightlylargerthantheinitiationpressure.Whenhighviscosityfluidisinjected,
H
Po
y
r
d
o
r
u
o
s
-m
m
e
e
c
d
h
i
a
a
n
fl
ic
o
a
w
lcoupling fluidinfiltrateintothecracksveryslowly.Theinitiationpressureisclosetothetheoreticalvalueandthe
breakdownpressureismuchlargerthantheinitiationpressure.
Hydraulicfracturing
Fluidviscosity
&2016ElsevierLtd.Allrightsreserved.
1. Introduction kinds: (1) continuum-based methods; (2) discontinuum-based
methods.
Hydraulic fracturing is a core technology used in oil and gas A representative in the continuum-based methods is the see-
wells to increase production, and has been widely used in low- page-stress-damage coupled model.16–18 Later, the model was
permeabilityreservoirsandshalegasexploration.Itisessentiallya extended tothree dimensions by Li et al.,19 which indicated that
rock rupture phenomenon involving hydro-mechanical coupling, the initiation pressure does not coincide with the breakdown
whichcoversawide rangeofissues.The studyofhydraulicfrac- pressure. Pan et al.20 combined rock discontinuum cellular auto-
turingisofgreatimportanceinboththeoryandpractice. matawithTOUGHcodetorealiseacouplinganalysisofsolidde-
Some hydraulic fracturing models were developed to assist formable and fluid flow in fractures. Keshavarzi and
operationdesign.Forexample,PerkinsandKern1contributedthe Mohammadi,21 and Chen22 simulated hydraulic fracturing using
firstmodel,whichwasfurtherdevelopedbyNordgren.2Geertsma an extended finite element method. Wu et al.23 extends the nu-
andKlerk3developedKGDmodel.Later,Fungetal.4andClearyet mericalmanifoldmethod(NMM)toincludethehydro-mechanical
model to simulate crack initiation, propagation, block formation
al.5 proposed some semi-analytical methods to solve hydraulic
and sliding due to water effect. Xie et al.,24 Zhang et al.25 and
fracturing problems. Other models include the pseudo-3D (P3D)
Zhangetal.26useddisplacementdiscontinuitymethodtosimulate
and planar-3D (PL3D) models.6,7 More examples of the analytical
of hydraulic fracturing and its interactions with a pre-existing
modelcanbefoundin.8–15
fracture. Carrier and Granet,27 and Chen28 used finite element
Although these analytical models are widely used, a common methodtomodellingfluid-drivenfractureinpermeablemedium.
limitationofwhichisthattheycanonlybeusedinsimulatingthe
In the discontinuum-based methods, the traditional discrete
propagation o
```
