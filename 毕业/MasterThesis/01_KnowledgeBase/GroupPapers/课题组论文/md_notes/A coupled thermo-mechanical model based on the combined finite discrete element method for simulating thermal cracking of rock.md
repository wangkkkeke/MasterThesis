# A coupled thermo-mechanical model based on the combined finite discrete element method for simulating thermal cracking of rock

## Abstract

Keywords: Basedonacombinedfinite-discreteelementmethod(FDEM),thisstudybuildsacoupledthermo-mechanical Finitediscreteelementmethod(FDEM) model (termed FDEM-TM) to simulate thermal cracking of rock. The coupled thermo-mechanical model Thermal-mechanicalcoupling consistsoftwomajorparts.Inthefirstpartthetemperaturedistributionofthesystemisanalyzedbasedonthe Thermalstress heatconduction equation.Inthesecondpartthethermal stresscausedbytemperaturechangeisadded to Thermalcracking perform mechanical fracture calculation. Based on these two parts, we can model rock fracture driven by Rockfracture thermo-mechanicalcoupling.Threeexampleswithanalyticsolutionsareusedtoverifythecorrectnessofthe modelindealingwiththeproblemsofsteady-stateheatconduction,unsteady-stateconduction,andthermal- mechaniccoupling,respectively.Inaddition,anexampleofthermalcrackingisalsogivenandcomparedwith the experimental results. The simulation results are in excellent agreement with the analytical solutions or experimental

## Extracted Text (First Pages)

```
International Journal of Rock Mechanics & Mining Sciences 91 (2017) 170–178
ContentslistsavailableatScienceDirect
International Journal of
Rock Mechanics & Mining Sciences
journal homepage: www.elsevier.com/locate/ijrmms
A coupled thermo-mechanical model based on the combined finite-discretcerossmark
element method for simulating thermal cracking of rock
Chengzeng Yana, Hong Zhengb,⁎
aFacultyofEngineering,ChinaUniversityofGeosciences,Wuhan430074,Hubei,China
bStateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRockandSoilMechanics,ChineseAcademyofSciences,Wuhan,Hubei,
China
A R T I C L E I N F O A B S T R A C T
Keywords: Basedonacombinedfinite-discreteelementmethod(FDEM),thisstudybuildsacoupledthermo-mechanical
Finitediscreteelementmethod(FDEM) model (termed FDEM-TM) to simulate thermal cracking of rock. The coupled thermo-mechanical model
Thermal-mechanicalcoupling consistsoftwomajorparts.Inthefirstpartthetemperaturedistributionofthesystemisanalyzedbasedonthe
Thermalstress heatconduction equation.Inthesecondpartthethermal stresscausedbytemperaturechangeisadded to
Thermalcracking
perform mechanical fracture calculation. Based on these two parts, we can model rock fracture driven by
Rockfracture
thermo-mechanicalcoupling.Threeexampleswithanalyticsolutionsareusedtoverifythecorrectnessofthe
modelindealingwiththeproblemsofsteady-stateheatconduction,unsteady-stateconduction,andthermal-
mechaniccoupling,respectively.Inaddition,anexampleofthermalcrackingisalsogivenandcomparedwith
the experimental results. The simulation results are in excellent agreement with the analytical solutions or
experimentalresults,verifyingthecorrectnessofthecoupledthermo-mechanicalmodeltosimulatethermal
cracking.Theproposedmethodprovidesanewtoolforthermal-mechanicalcouplingproblemsingeothermal
exploitation.
1. Introduction temperature on mechanical properties of rock though experiment.1,2
Another mean of studying thermal cracking of rocks is numerical
Rockiscomposedofdifferentmineralgrainsorcrystalscemented simulation. The main numerical methods for simulating thermal
together. The thermal expansion characteristics of different mineral crackingcanbedividedintotwocategories:continuum-basedmethods
grainsaredifferent.Consequently,eveninthecaseofuniformheating, anddiscontinuum-basedmethods.
thermal stress will be produce in rock. Once the stress exceeds the Forcontinuum-basedmethods,Tangetal.3,4establishedacoupled
strength of the material, rock will generate micro-cracks. If these thermo-mechanical model in RFPA to simulate thermal cracking
micro-cracksconstitutefracturenetworks,macroscopicthermalcrack- process of brittle materials. Similarly, Li et al.5,6 built an initially
ingwillemerge.Fromgeothermalexploitation,nuclearwastestorage, thermo-mechanical-damagemodel(TMD)andatemperature-seepage-
oilexploitation,coalseamgassafetydrainageandcrustalevolution,to stress-damage(THMD)modeltoexploremeso-structuraldamageand
earthquake mechanism research, we need to consider rock thermal evolutionary mechanisms of rock under the effect of multi-physics
cracking.Forexample,inanuclearwasterepository,weshouldprevent coupling. Using Flac3D, Kwon and Cho 7 studied the effect of
rockthermalcrackinginducedbydecayheatofnuclearwaste,because excavation damage zone on rock behavior of thermo-mechanical
rock fracture will cause radionuclide migration contamination. coupling and hydraulic-mechanical coupling, but it cannot simulate
However, in geothermal extraction and petroleum exploitation, ther- thermalcrackingofrock.Ngoetal.8proposedanewthermaldamage
mal cracking can be utilized to form fracture network in rock, which modelbasedonfiniteelementmethod,itispossibletomodelsoftening
willenhancethepermeabilityofrock,therebyincreasingoilproduction behavior of brittle materials under the effect of load, including
and geothermal acquisition amount. Consequently, the study of temperature change. Dempsey et al.9 studied the stress change and
thermal cracking has important the
```
