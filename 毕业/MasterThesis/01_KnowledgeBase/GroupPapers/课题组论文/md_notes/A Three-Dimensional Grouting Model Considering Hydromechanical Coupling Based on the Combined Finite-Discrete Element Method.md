# A Three-Dimensional Grouting Model Considering Hydromechanical Coupling Based on the Combined Finite-Discrete Element Method

## Abstract

:Inthispaper,wepresentathree-dimensional(3D)groutingmodelbasedonthecombinedfinite-discreteelementmethod(FDEM). The3Dgroutingmodeldiscretizestheproblemdomainintotetrahedralelementsandjointelements,andthegroutflowsonlyinthebrokenjoint elements,which satisfiestheplanarPoiseuilleflow.Bycombininggroutmigration,FDEMmechanicalcrackingcomputation,andstress-in- ducedfractureaperturevariationinagraphicsprocessingunit(GPU)parallelmultiphysicsFDEMsoftware,calledMultiFracS,the3Dgrouting modelcanmodelrockcrackingandtheeffectofhydromechanical(HM)coupling.First,agroutingexamplewithanalyticalsolutionsispre- sentedtovalidatethe3Dgroutingmodel.Then,weinvestigatetheinfluenceofseveralkeyparametersongroutpenetrationinfracturedrock masses.Theresultsrevealthatthe3Dgroutingmodelcanmodelgroutmigration,pressuredistribution,grout–rockmassinteraction,rockde- formation,andcrackinitiationandpropagation.Finally,theevolutionoffracturegeometryinducedbygroutingunderdifferentinsitustressesis studied.Thenumericalresultspr

## Extracted Text (First Pages)

```
A Three-Dimensional Grouting Model Considering
Hydromechanical Coupling Based on the Combined
Finite-Discrete Element Method
Chengzeng Yan1; Tie Wang2; Yakun Gao3; Wenhui Ke, Ph.D.4; and Gang Wang5
Abstract:Inthispaper,wepresentathree-dimensional(3D)groutingmodelbasedonthecombinedfinite-discreteelementmethod(FDEM).
The3Dgroutingmodeldiscretizestheproblemdomainintotetrahedralelementsandjointelements,andthegroutflowsonlyinthebrokenjoint
elements,which satisfiestheplanarPoiseuilleflow.Bycombininggroutmigration,FDEMmechanicalcrackingcomputation,andstress-in-
ducedfractureaperturevariationinagraphicsprocessingunit(GPU)parallelmultiphysicsFDEMsoftware,calledMultiFracS,the3Dgrouting
modelcanmodelrockcrackingandtheeffectofhydromechanical(HM)coupling.First,agroutingexamplewithanalyticalsolutionsispre-
sentedtovalidatethe3Dgroutingmodel.Then,weinvestigatetheinfluenceofseveralkeyparametersongroutpenetrationinfracturedrock
masses.Theresultsrevealthatthe3Dgroutingmodelcanmodelgroutmigration,pressuredistribution,grout–rockmassinteraction,rockde-
formation,andcrackinitiationandpropagation.Finally,theevolutionoffracturegeometryinducedbygroutingunderdifferentinsitustressesis
studied.Thenumericalresultspresenthighcoincidencewiththeinsituexperimentalresults,demonstratingthatthe3Dgroutingmodelisef-
fectiveindealingwithfracturegrouting.DOI:10.1061/(ASCE)GM.1943-5622.0002448.©2022AmericanSocietyofCivilEngineers.
Authorkeywords:Finite-discreteelementmethod;Grouting;Fracturedrockmasses;Rockcracking;Discreteelementmethod.
Introduction Fransson(2006)designedfieldtestsusingsilicasolasagroutingma-
terialtostudythegroutabilityoflow-permeablerocks;Liangetal.
Groutingisoneofthemostcommonlyusedmethodstodealwith (2019) carried out grouting tests in an inclined fracture with sand
incomplete geological structures such as fractured fault zones in and water flow and studied the migration of chemical grout, and
undergroundexcavation.Itcaneffectivelyimprovethemechanical Suietal.(2015)usedagroutingsystemwithatransparentfracture
propertiesoffractured zones,reducewater inflow, and ensure the replica to conduct experimental research on the chemical grouting
stability of rock walls during excavation (Gustafson and Stille inafracturewithflowingwater.However,itisstilldifficulttoobserve
1996;Hässleretal.1992;Yangetal.2002).However,currentthe- groutmigrationandfracturenetworkevolutiondirectlyinthefield.
oreticalresearchongroutinglagsfarbehindengineeringpractice.It Therefore, scholars (Amadei and Savage 2001; Funehag and
isnecessarytostudythemigrationmechanismoffracturegrouting Gustafson 2008; Funehag and Thörn 2018; Gustafson et al.
and develop appropriate grouting theories to guide grouting engi- 2013; Pedrotti et al. 2017; Zhang et al. 2018) have studied the
neeringpractice. groutingprocessfromtheperspectiveofanalyticalsolutions.Fune-
In the past few decades, many research studies have been con- hagandGustafson(2008)deducedanalyticalsolutionsofthepen-
ducted on the grout flow mechanism in fractured rock masses. In etration length of a Newtonian fluid in one-dimensional channel
terms of experiments (Funehag and Fransson 2006; Liang et al. flow and two-dimensional radial flow. Gustafson and Stille
2019; Sui et al. 2015; Yang et al. 2016a, 2018a), Funehag and (2005)obtainedanalyticalsolutionsofthegroutpenetrationlength
of Bingham fluid in one-dimensional channel flow and two-
1Professor,FacultyofEngineering,ChinaUniversityofGeosciences, dimensional radial flow. However, these analytical solutions are
Wuhan430074,China;HongKongUniversityofScienceandTechnology, usuallyapplicableonlytogroutinginsimplefractures.
Hong Kong SAR, China; International Joint Research Center for Deep Withtherapiddevelopmentofnumericalcalculationtheories,a
Earth Drilling and Resource Development, China University of large number of numerical methods (Chen et al. 2014; Eriksson
Geosciences,Wuhan430074,China.ORCID:https://orcid.org/0000-0002
et al. 2000; Fidelibus and Lenti 2012; Kim et al. 2009; Sun et 
```
