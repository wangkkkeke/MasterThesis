# A three‐dimensional heat transfer and thermal cracking model considering the effect of cracks on heat transfer

## Keywords

FDEM,heatconduction,thermalcracking,thermalstress,thermo‐mechanicalcouplingmodel

## Extracted Text (First Pages)

```
Received:6July2018 Revised:4January2019 Accepted:5March2019
DOI:10.1002/nag.2937
RESEARCH ARTICLE
‐
A three dimensional heat transfer and thermal cracking
model considering the effect of cracks on heat transfer
Chengzeng Yan1,2 | Yu‐Yong Jiao1 | Hong Zheng3
1FacultyofEngineering,ChinaUniversity
Summary
ofGeosciences,Wuhan430074,China
A simple three‐dimensional heat transfer model is developed to consider the
2InternationalJointResearchCenterfor
DeepEarthDrillingandResource hinderingeffectofcracksonheattransfer.The3Dheattransfermodelcanalso
Development,ChinaUniversityof beappliedto numerical methods such asthecombined finite‐discreteelement
Geosciences,Wuhan430074,China
method (FDEM), discrete element method (DEM), discontinuous deformation
3TheKeyLaboratoryofUrbanSecurity
analysis (DDA), the numerical manifold method (NMM), and the finite
andDisasterEngineering,Beijing
UniversityofTechnology,Ministryof element method (FEM) to construct thermo‐mechanical coupling models that
Education,Beijing,China
allow these methods to solve thermal cracking problems and dynamically
Correspondence considerthehinderingeffectofcracksonheattransfer.Inthe3Dheattransfer
Yu‐YongJiao,FacultyofEngineering, model, the continuous‐discontinuous medium is discretized into independent
ChinaUniversityofGeosciences,Wuhan
tetrahedralelements,andjointelementsareinsertedbetweenadjacenttetrahe-
430074,China.
Email:yancz@cug.edu.cn; dral elements. Heat transfer calculations for continuous‐discontinuous media
yanchengzheng86@gmail.com; are converted to heat conduction in tetrahedral elements and the heat
yyjiao@cug.edu.cn
exchangebetweentheadjacenttetrahedralelementsthroughthejointelement.
Fundinginformation If the joint element between adjacent tetrahedral elements breaks (ie, a crack
NationalNaturalScienceFoundationof
generates), the heat exchange coefficient of the joint element is reduced to
China,Grant/AwardNumbers:11602006,
accountforthehinderingeffectofcracksonheatconduction.Thenthemodel
11872340and41731284;theFundamental
ResearchFundsfortheCentralUniversi- andtheFDEMarecombinedtobuildathermo‐mechanicalcouplingmodelto
ties,ChinaUniversityofGeosciences
simulate thermal cracking. The thermally induced deformation, stress, and
(Wuhan),Grant/AwardNumber:
CUG170657;BeijingNaturalScience cracking are investigated by the thermo‐mechanical coupling model, and the
Foundation,Grant/AwardNumber: numerical results are compared with analytical solutions or experimental
1174012
results.The3Dheattransfermodelandthermo‐mechanicalmodelcanprovide
a powerful tool for simulating heat transfer and thermal cracking in a
continuous‐discontinuous medium.
KEYWORDS
FDEM,heatconduction,thermalcracking,thermalstress,thermo‐mechanicalcouplingmodel
1 | INTRODUCTION
Under the effect of temperature and a temperature gradient, a local thermal stress concentration will occur between
mineral particles because of the anisotropy and heterogeneity of the thermal expansion of the rock mineral particles.
Ifthestressconcentrationexceedsthetensilestrengthoftherock,thermalcrackingwilloccur,andafracturenetwork
will eventually form. Unlike hydraulic fracturing, which often generates cracks that extend along a certain direction,1
IntJNumerAnalMethodsGeomech.2019;1–29. wileyonlinelibrary.com/journal/nag ©2019JohnWiley&Sons,Ltd. 1
--- PAGE BREAK ---
2 YANETAL.
thermal cracking creates a fracture network, which can increase both the fracture length and fracture density simulta-
neously. Therefore,thermalcracking hassignificant applicationprospectsforincreasingthe permeabilityofreservoirs.
To understand the thermal cracking mechanism of rocks, many scholars use numerical models to study thermal
crackingbehavior.Forexample,Tangetal2developedamesostructure‐baseddamagemodelbasedonrockfailurepro-
cess analysis (RFPA)3 to simulate the thermal cracking behavior of ceramics. Jiang et al4 and Li et al5 investigated the
formation mechanism of crack patterns in ceramics subjected to thermal shock based on the finit
```
