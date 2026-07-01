# FDEM‐TH3D A three‐dimensional coupled hydrothermal model for fractured rock

## Keywords

3Dfinitediscreteelementmethod,fracturedrock,heatexchangebetweenfluidandrock,heat transfer,hydrothermalcoupling,seepage

## Extracted Text (First Pages)

```
Received:24December2017 Revised:22September2018 Accepted:25September2018
DOI:10.1002/nag.2869
RESEARCH ARTICLE
‐ ‐
FDEM TH3D: A three dimensional coupled hydrothermal
model for fractured rock
Chengzeng Yan | Yu‐Yong Jiao
FacultyofEngineering,ChinaUniversity
Summary
ofGeosciences,Wuhan,China
This paper proposes a three‐dimensional coupled hydrothermal model for
Correspondence fractured rock based on the finite‐discrete element method to simulate fluid
Yu‐YongJiao,FacultyofEngineering,
flow and heat transport. The 3D coupled hydrothermal model is composed of
ChinaUniversityofGeosciences,Wuhan
430074,China. three main parts: a heat conduction model for the rock matrix,a heat transfer
Email:yyjiao@cug.edu.cn;yancz@cug. model for the fluid in the fractures (including heat conduction and heat
edu.cn;yanchengzheng86@gmail.com
convection),andaheatexchangemodelbetweentherockmatrixandthefluid
Fundinginformation inthefractures.Fourexampleswithanalyticalsolutionsareprovidedtoverify
NationalNaturalScienceFoundationof
the model. A heat exchange experiment of circulating water in a cylindrical
China,Grant/AwardNumbers:11872340,
granite sample with one fracture is simulated. The simulation results agree
11602006and41731284;BeijingNatural
ScienceFoundation,Grant/AwardNum- well with the experimental results. The effects of the fracture aperture, fluid
ber:1174012;ChaoyangDistrictPostdoc-
viscosity, and pressure difference on the heat exchange between the fluid and
toralScienceFoundation,Grant/Award
Number:2016ZZ‐01‐08;ChinaUniversity rock are studied. Finally, an application concerned with heat transport and
ofGeosciences(Wuhan),Grant/Award fluid flow in fractured rock is presented. The simulation results indicate that
Number:CUG170657
the 3D fully coupled hydrothermal model can capture the fluid flow and
temperature evolution of rocks and fluids.
KEYWORDS
3Dfinitediscreteelementmethod,fracturedrock,heatexchangebetweenfluidandrock,heat
transfer,hydrothermalcoupling,seepage
1 | INTRODUCTION
Many applications inenvironmental andenergyengineeringinvolveheatflowandtransportduetofluidflowthrough
fracturedrock.1-9Heattransportinfracturedrockisstronglyinfluencedbyfluidflow,andthechangeintemperatureof
the fluid also affects the fluid flow in the fracture. The mutual influence between the heat transport and fluid flow is
calledhydrothermalcoupling.Fluidflowinfracturesaffectstheheattransferinfracturedrockthroughheatconvection
and ultimately affects the temperature distribution, and the temperature alters the fluid viscosity and thus affects the
fluid flow in the fracture.
Duetotheimportanceofhydrothermalcouplinginfracturedrock,severalcoupledmodelsoralgorithmshavebeen
proposed. For example, Jiang et al10 developed a novel three‐dimensional transient model for studying the subsurface
heatexchangeprocessinEGS.ChenandJiang11proposedanonequilibriumthermalmodelforheattransferinaporous
subsurface‐heated reservoir, in which the EGS reservoir is considered as an equivalent porous medium. Cui et al12
performedanumericalanalysisofcoupledhydrothermalproblemsingeotechnicalengineering.However,thesemodels
are mainly based on a continuous medium, which cannot consider the effects of fractures on fluid flow and heat
transport, especially in rock with sparse fractures or large faults.
IntJNumerAnalMethodsGeomech.2018;1–26. wileyonlinelibrary.com/journal/nag ©2018JohnWiley&Sons,Ltd. 1
--- PAGE BREAK ---
2 YANANDJIAO
Therefore, other models based on a discontinuous medium or a dual porosity medium have been proposed to per-
form coupled hydrothermal analyses. For example, Xu et al13 proposed a simplified coupled hydrothermal model for
enhanced geothermal systems. Tomac and Gutierrez2 presented a coupled convective‐conductive heat flow and trans-
port model using the discrete element method (DEM). Luo et al14 studied the effect of fracture surface roughness on
fluidflowandheattransferprocessesinfracturedrocksusingadiscretefracturenetworkmodel.HeinzeandHamidi15
studied fluid 
```
