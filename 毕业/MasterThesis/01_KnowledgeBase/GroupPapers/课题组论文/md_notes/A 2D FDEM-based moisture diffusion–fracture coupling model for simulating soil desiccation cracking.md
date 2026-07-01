# A 2D FDEM-based moisture diffusion–fracture coupling model for simulating soil desiccation cracking

## Keywords

Crack initiation (cid:2) FDEM (cid:2) Moisture diffusion (cid:2) Moisture content (cid:2) Propagation (cid:2) Soil desiccation cracking

## Extracted Text (First Pages)

```
ActaGeotechnica
https://doi.org/10.1007/s11440-021-01297-4
(0123456789().,-volV)(0123456789,-().volV)
RESEARCH PAPER
A 2D FDEM-based moisture diffusion–fracture coupling model
for simulating soil desiccation cracking
Chengzeng Yan1,2 • Tie Wang1 • Wenhui Ke3 • Gang Wang2
Received:29March2021/Accepted:27June2021
(cid:2)TheAuthor(s),underexclusivelicencetoSpringer-VerlagGmbHGermany,partofSpringerNature2021
Abstract
Basedonthecombinedfinite–discreteelementmethod(FDEM),thispaperpresentsamoisturediffusion–fracturecoupling
modeltosimulatesoildesiccationcracking.Thecouplingmodel,firstly,analyzesmoisturecontentdistributionwithinthe
soil according to a moisture diffusion model. Then, the shrinkage stress caused by the change of moisture content is
calculatedandappliedtothesystemequationofFDEM.Finally,ifanewcrackisgenerated,thenodesharingrelationship
and mesh of adjacent solid elements are updated for moisture diffusion calculation in the next time step. In this paper,
examplesof1Dmoisturemigrationinthesoiltrip,shrinkagestressanddeformationcausedbythemoisturereduceinthe
rectangularsoilarestudied.Thesimulationresultsagreewellwithanalyticalsolutions,whichverifiesthecorrectnessofthe
proposedmodel. Then,the model is used tosimulate soildesiccationcrackingprocess, andthe crack evolution patternin
the numerical results is consistent with experimental results. Besides, several main factors affecting soil desiccation
crackingarealsoinvestigated,includingtheelasticmodulus,themoistureshrinkagecoefficient,andthesoilthickness.The
moisture diffusion–fracture coupling model provides a new research tool for studying the mechanical mechanism of soil
desiccation cracking.
Keywords Crack initiation (cid:2) FDEM (cid:2) Moisture diffusion (cid:2) Moisture content (cid:2) Propagation (cid:2) Soil desiccation cracking
1 Introduction liners, triggeringofslopesliding,andeven declineincrop
yields. For example, desiccation cracks were observed in
Desiccation cracking in soil due to loss of moisture is a dikesanddamsthataffectedtheirstability[7,82].Inslope
commonly occurred natural phenomenon, which is also a engineering, soil desiccation cracking not only causes the
fundamental problem involving multiple disciplines such loss of the cohesive effect of the soil but also provides
as geotechnical engineering, environmental engineering, channels for rainwater to infiltrate into the slope and thus
mining engineering, and agricultural engineering. Soil aggravates the damage and instability of the slope
desiccationcrackingcancauseseveredamagetohydraulic [2, 9, 46, 59, 81]. Bronswijk et al. [3] indicated that soil
structures, extensive crackingin roadbeds andlandfill clay desiccation cracking controls the transport speed of mois-
ture solute and microorganism in the soil, which affects
crop growth and production significantly.
& GangWang
Withmorefrequentoccurrenceofextremearidclimates
gwang@ust.hk
recently, there are more and more engineering problems
ChengzengYan caused by soil desiccation cracking. Therefore, it is urgent
yancz@cug.edu.cn
to develop effective quantitative methods to study the
1 FacultyofEngineering,ChinaUniversityofGeosciences, fundamental mechanism of desiccation cracking in soils.
Wuhan430074,China Atpresent,thestudyofsoildesiccationcrackingmainly
2 DepartmentofCivilandEnvironmentalEngineering,Hong includes two approaches: experimental study and numeri-
KongUniversityofScienceandTechnology, cal simulation. The experimental research mainly focuses
ClearWaterBay,HongKong,SAR,China ontheshrinkageandcrackingbehaviorofsoil[16,35,41].
3 WuhanMunicipalConstructionGroupCo.,Ltd, Tang et al. [48] studied the influencing factors of surface
Wuhan430023,China
123
--- PAGE BREAK ---
ActaGeotechnica
shrinkage cracks in clayey soils, which revealed that thestressapproachcommonlyconsideredforinvestigating
sample size, boundary conditions, soil properties, temper- soil desiccation cracking.
ature, and drying conditions all affect the crack initiation Although severa
```
