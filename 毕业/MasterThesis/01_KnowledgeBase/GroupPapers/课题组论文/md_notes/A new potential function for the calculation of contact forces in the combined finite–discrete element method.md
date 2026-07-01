# A new potential function for the calculation of contact forces in the combined finite–discrete element method

## Keywords

combinedfinite–discreteelementmethod(FDEM);contactforce;discreteelementmethod (DEM);potentialfunction

## Extracted Text (First Pages)

```
INTERNATIONALJOURNALFORNUMERICALANDANALYTICALMETHODSINGEOMECHANICS
Int.J.Numer.Anal.Meth.Geomech.2017;41:265–283
Publishedonline8August2016inWileyOnlineLibrary(wileyonlinelibrary.com).DOI:10.1002/nag.2559
A new potential function for the calculation of contact forces in the
fi –
combined nite discrete element method
C.Z. Yan1,2 and H. Zheng2,*,†
1StateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRockandSoilMechanics,Chinese
AcademyofSciences,Wuhan430071,China
2KeyLaboratoryofUrbanSecurityandDisasterEngineering(BeijingUniversityofTechnology),MinistryofEducation,
Beijing100124,China
SUMMARY
Although the potential contact force proposed by Munjiza overcomes the difficulties inherent in the tradi-
tionaldiscreteelementmethods,thephysicalmeaningofthepotentialisnotclearandthecontactforcede-
rivedfromtheoriginalpotentialfunctionisstronglydependentonthemeshconfiguration.Inthisstudy,we
redefine a potential function and propose a new contact force calculation method based on a unified stan-
dard.Moreover, thenewpotential function retainsalltheadvantages oftheoriginalpotential function but
haslessmeshdependency.Copyright©2016JohnWiley&Sons,Ltd.
Received7September2015;Revised18June2016;Accepted5July2016
KEYWORDS: combinedfinite–discreteelementmethod(FDEM);contactforce;discreteelementmethod
(DEM);potentialfunction
1. INTRODUCTION
The rupture phenomenon of brittle rock has been a hot spot of experimental and theoretical studies.
Many problems in rockmechanics and rockengineering are related to the rock fracture closely.
Some knowledge of complex rock fracture has been accumulated based on experimental
observations [1–4]. However, the mechanisms related to rock fracture, such as a crack initiation and
propagation, remain unclear owing to huge difficulties in tracking crack initiation and propagation
during experiment [5]. Classic fracture mechanics is another means to study rock fracture. In most
of the literature, research is limited to a single crack [6, 7] or a small number of cracks [8]. Thus,
classic fracture mechanics is hard to deal with the propagation or interference of multiple cracks in
rockmass [9].
There are some numerical methods for studying multiple crack propagation [5, 10, 11]. For
example, Tang [10] proposed the rock failure process analysis system based on the finite element
method together with the material rupture algorithm, which can simulate crack initiation,
propagation, and intersection. Later, Liang et al. [5, 11] conducted a three-dimensional numerical
simulation of rock fracture. Potyondy and Cundall [12] proposed a bonded particle model, which
reproduced many mechanic characteristics of rocks, including elasticity, fracture, acoustic emission,
material anisotropy caused by cumulative damage, dilatancy, softening, and strength increase with
increased confining pressure.
*Correspondenceto:H.Zheng,StateKeyLaboratoryofGeomechanicsandGeotechnicalEngineering,InstituteofRock
andSoilMechanics,ChineseAcademyofSciences,Wuhan430071,China.
†E-mail: hzheng@whrsm.ac.cn
Copyright©2016JohnWiley&Sons,Ltd.
--- PAGE BREAK ---
266 C.YANANDH.ZHENG
In addition, Munjiza proposed the combined finite–discrete element method (FDEM) to simulate
continuum fracture and obtained some good results [13–16]. In FDEM, a continuum is discretized
as a mesh consisting of triangular solid elements and joint elements with cohesive behaviors. The
movement of each triangular solid element is determined by the imbalance force acting on the
triangular solid elements, which is similar to the discrete element method (DEM). By the breakage
of joint elements, the crack initiation and propagation in the rock mass are simulated [17]. Before
fracture, the deformation of continuum can be represented by those solid elements and joint
elements. This method has some advantages over the particle flow method in simulating rock
fracture, such as the following aspects: there is no gap between solid elements in the initial model,
solid elements are d
```
