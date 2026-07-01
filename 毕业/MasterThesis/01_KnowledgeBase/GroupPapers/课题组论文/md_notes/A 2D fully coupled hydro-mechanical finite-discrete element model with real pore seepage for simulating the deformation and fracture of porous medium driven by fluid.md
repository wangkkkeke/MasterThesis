# A 2D fully coupled hydro-mechanical finite-discrete element model with real pore seepage for simulating the deformation and fracture of porous medium driven by fluid

## Abstract

Articlehistory: Basedonthefinite-discreteelementmethod(FDEM),a2Dfullycoupledmodelwithrealporeseepageis Received28April2017 proposed.Thismodelcansolvetheproblemofthedeformationandfractureofporousmediumdrivenby Accepted10October2017 fluid.Inthismodel,thefluidflowinthefractureisexpressedbythecubiclaw,whilethefluidflowinthe Availableonline27October2017 rock matrix is characterized by Darcy’s law and solved by the finite volume method. The interaction betweenporeseepageandfractureseepageisrealizedatthefracture.Threeanalyticalsolutionsarepre-

## Extracted Text (First Pages)

```
ComputersandStructures196(2018)311–326
ContentslistsavailableatScienceDirect
Computers and Structures
journal homepage: www.elsevier.com/locate/compstruc
A 2D fully coupled hydro-mechanical finite-discrete element model with
real pore seepage for simulating the deformation and fracture of porous
medium driven by fluid
⇑
Chengzeng Yan, Yu-Yong Jiao
FacultyofEngineering,ChinaUniversityofGeosciences,Wuhan430074,China
a r t i c l e i n f o a b s t r a c t
Articlehistory: Basedonthefinite-discreteelementmethod(FDEM),a2Dfullycoupledmodelwithrealporeseepageis
Received28April2017 proposed.Thismodelcansolvetheproblemofthedeformationandfractureofporousmediumdrivenby
Accepted10October2017 fluid.Inthismodel,thefluidflowinthefractureisexpressedbythecubiclaw,whilethefluidflowinthe
Availableonline27October2017
rock matrix is characterized by Darcy’s law and solved by the finite volume method. The interaction
betweenporeseepageandfractureseepageisrealizedatthefracture.Threeanalyticalsolutionsarepre-
Keywords: sentedtoverifythecorrectnessoftheproposedmodel.Theresultsshowthatthenumericalsolutions
Finitediscreteelementmethod(FDEM)
agreewellwiththeanalyticalsolutions.Inaddition,ahydraulicfracturingproblemwithacomplexfrac-
Hydro-mechanicalcoupling
turenetworkisstudiedusingthismodel.Thesimulationresultsshowthatthemodelcancapturethe
Rockfracture
fractureinitiation,propagation,andintersection,theinteractionofnaturalfracturesandnewlygenerated
Poreseepage
Fractureseepage fractures,andtheevolutionoffluidpressureduringhydraulicfracturing.Themodelcanbeusednotonly
Hydraulicfracturing tosimulatehydraulicfracturinginshalegasandgeothermalminingbutalsotosolveaseriesofgeome-
chanicalproblemsrelatedtotheeffectoffluid.Thus,thismodelhasbroadapplicationprospects.
(cid:1)2017ElsevierLtd.Allrightsreserved.
1.Introduction on this theory, several enhanced hydro-mechanical coupling
formulationshavesubsequentlybeenproposedtostudythepore
Hydro-mechanicalcouplingreferstotheinteractionofseepage mechanicalresponseoffractured-porousrockmasses[4–6].
and mechanics. Many geomechanical problems are related to Another important driving force for the study of hydro-
hydro-mechanical coupling, such as landslide or slope failure, mechanicalcouplinginrockistheextensiveapplicationofhydrau-
damfoundationdamage,stabilityofexcavation,designandsafety licfracturingtechnologyinoilandshalegasexploitation.Aseries
assessment of nuclear waste underground disposal, oil and gas ofanalyticalmodelsofhydraulicfracturinghavebeenestablished,
explorationandgeothermalmining,hydraulicfracturing,compres- such as the PKN model [7,8], KGD model [9,10], the radial or
sionandsettlementofreservoirs,hydraulicfracturing,coalmining, penny-shaped model [11], and some pseudo-three dimensional
coalbedmethaneextraction,undergroundstorageoffluids,oiland (P3D)andthree-dimensional(PL3D)models[12].Recentprogress
gasgeologicalstorage,andtoxicliquidwastedisposal. in the analytical modeling of hydraulic fracturing has been
reviewedelsewhere[13].
1.1.Analyticalmethodsforhydro-mechanicalcoupling
1.2.Numericalmethodsofhydro-mechanical
Classic models of hydro-mechanical coupling of porous media
suchassoilcanbetracedtotheeffectivestressprincipleandthe Analytical methods of hydro-mechanical coupling are often
one-dimensional theory of consolidation proposed by Terzaghi oversimplified and generally consider a homogenous elastic
[1].ExtendingtheworkofTerzaghi,Biot[2,3]usedthetheoryof mediumorsimplegeometry.Experimentalmethodsarenotonly
elasticityandDarcy’slawtodescribesolidbehaviorandinterstitial expensive but also extremely tedious and time consuming. Thus,
fluid flow, respectively, denoted Biot consolidation theory. Based experimental methods are not efficient, especially for routine
industry application. Therefore, numerical methods have been
⇑ established for hydro-mechanical coupling. For example, some
Correspondingauthor.
continuumnumericalmethodshavebeenadoptedforthesimula-
E-mail addresses: yancz@cug.edu.cn, yanchengzheng86@
```
