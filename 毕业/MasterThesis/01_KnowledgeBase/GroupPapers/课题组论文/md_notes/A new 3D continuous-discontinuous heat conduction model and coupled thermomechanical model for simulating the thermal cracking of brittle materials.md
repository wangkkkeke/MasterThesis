# A new 3D continuous-discontinuous heat conduction model and coupled thermomechanical model for simulating the thermal cracking of brittle materials

## Abstract

Articlehistory: Thispaperproposesanew3Dcontinuous-discontinuousheatconductionmodeltoconsiderthethermal Received24November2020 resistanceeffectofcracksanddynamiccrackpropagationduringheattransfer.Combiningthisheatcon- Receivedinrevisedform3June2021 ductionmodelandthefinite-discreteelementmethod(FDEM),weconstructacoupledthermomechan- Accepted4June2021 icalmodelforsolvingthermalcrackingproblemsinbrittlematerials.Themechanicalfracturecalculation Availableonline6June2021 utilizes virtual joint elements between adjacent solid elements for fracture simulation. On the other hand,virtualjointelementsarenotincludedintheheatconductionmodeltoimprovenumericaleffi-

## Keywords

ciency.Whennewcracksaregenerated,thenodesharingrelationshipisdynamicallyupdatedintheheat

## Extracted Text (First Pages)

```
InternationalJournalofSolidsandStructures229(2021)111123
ContentslistsavailableatScienceDirect
International Journal of Solids and Structures
journal homepage: www.elsevier.com/locate/ijsolstr
A new 3D continuous-discontinuous heat conduction model and coupled
thermomechanical model for simulating the thermal cracking of brittle
materials
Chengzeng Yana,b, Xun Wanga, Duruo Huangc,⇑ , Gang Wangb
aFacultyofEngineering,ChinaUniversityofGeosciences,Wuhan,China
bDepartmentofCivilandEnvironmentalEngineering,HongKongUniversityofScienceandTechnology,ClearWaterBay,HongKongSAR,China
cDepartmentofHydraulicEngineering,TsinghuaUniversity,Beijing,China
a r t i c l e i n f o a b s t r a c t
Articlehistory: Thispaperproposesanew3Dcontinuous-discontinuousheatconductionmodeltoconsiderthethermal
Received24November2020 resistanceeffectofcracksanddynamiccrackpropagationduringheattransfer.Combiningthisheatcon-
Receivedinrevisedform3June2021 ductionmodelandthefinite-discreteelementmethod(FDEM),weconstructacoupledthermomechan-
Accepted4June2021
icalmodelforsolvingthermalcrackingproblemsinbrittlematerials.Themechanicalfracturecalculation
Availableonline6June2021
utilizes virtual joint elements between adjacent solid elements for fracture simulation. On the other
hand,virtualjointelementsarenotincludedintheheatconductionmodeltoimprovenumericaleffi-
Keywords:
ciency.Whennewcracksaregenerated,thenodesharingrelationshipisdynamicallyupdatedintheheat
3DFDEM
conductioncalculationtoconsiderthethermalresistanceeffectofcracks.Inthisstudy,theproposed
Coupledthermomechanical
modelsareverifiedbysimulatingheattransfer,coupledthermomechanical,andthermalcrackingprob-
Thermalcracking
Thermalresistance lemsinbrittlematerials.Thenumericalsimulationsareconsistentwithanalyticalsolutions,andacom-
Brittlematerial plexthermalcrackprocesscanberealisticallycaptured.Thesenumericalexamplesverifythecorrectness
oftheproposedmodels,whichcanbepowerfultoolsforsolvingheattransfer,coupledthermomechan-
ical,andthermalcrackingproblemsinbrittlematerials.
(cid:1)2021ElsevierLtd.Allrightsreserved.
1.Introduction Homand-EtienneandHoupert,1989;Jiangetal.,2012;Zuoetal.,
2018). Jiang et al. (2012) studied the periodicity and hierarchical
Rock,concrete,andceramicsarebrittlematerialswidelyusedin appearance of the crack morphology of ceramic materials under
high-radioactive nuclear waste storage, large-volume concrete thermalshock.Gautametal.(2019)revealedthatthechangesin
engineering, aerospace, and thermal protection structures (Laub thethermophysicalparametersofgranitearecausedbytheinitia-
and Venkatapathy, 2003; Shen et al., 2020; Yu et al., 2018; Zhao tion, expansion, and penetration of cracks. In addition, Yin et al.
et al., 2016). Thermal stress is generated inside these materials (2019)investigatedtheeffectsoftemperatureandthermalcycling
asthetemperatureoftheenvironmentchangesrapidly.Ifthether- onthefracturetoughnessandporosityofgranitethroughlabora-
malstressexceedsthestrengthlimitofthebrittlematerial,mate- tory experiments. Yang et al. (2019) used a scanning electron
rialfailurecanoccurduetothermalcracking.Therefore,thestudy microscope and an orthogonally polarized light microscope to
of thermal cracking of brittle materials is of great significance in study the thermal cracking of granite. Ghabache et al. (2016)
practicalengineering. experimentallyinvestigated thequenchingofaliquidpancaketo
Atpresent,manyexperimentsandnumericalsimulationshave study the crack patterns on the frozen pancake under thermal
been conducted to investigate the thermal cracking problem in shock.However,itisdifficulttoobservethethermalcrackingpro-
brittle materials. In terms of experiments, many scholars have cessofbrittlematerialsinrealtimethroughexperiments,andusu-
studied the initiation and propagation of cracks at different allyonlythefinalcrackconfigurationcanbeobtained.
temperatures (Gautam et al., 2019; Ghabache et al., 2016; Numerical simulation is another fundamental approach to
investigating thermal crac
```
