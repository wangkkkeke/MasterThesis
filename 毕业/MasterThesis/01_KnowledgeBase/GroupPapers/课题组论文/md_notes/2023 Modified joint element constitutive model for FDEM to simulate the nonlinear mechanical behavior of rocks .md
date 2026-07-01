# 2023 Modified joint element constitutive model for FDEM to simulate the nonlinear mechanical behavior of rocks 

## Abstract

Keywords: The closure behavior of fractured rock, which is a crucial characteristic, is challenging to simulate accurately Finite-discrete element method using commonly employed numerical models. To address this issue and accurately replicate the nonlinear me- Modified joint element constitutive chanical behavior of rock, we propose a modified joint element constitutive model for the finite-discrete element Rock compression simulation method (FDEM). The modified model resolves the stress on both sides of the crack by considering the aperture of Nonlinear mechanical behavior the broken joint element instead of contact. Additionally, Joint elements with virtual opening, which are referred to as preprocessed joint elements (Pre-JEs), are implemented in this model. We extensively discuss two pa- rameters associated with Pre-JEs to elucidate their impact on the nonlinear mechanical behavior of rock. Our findings demonstrate that the incorporation of Pre-JEs leads to a reduction in the compr

## Extracted Text (First Pages)

```
ComputersandGeotechnics164(2023)105831
Contents lists available at ScienceDirect
Computers and Geotechnics
journal homepage: www.elsevier.com/locate/compgeo
Modified joint element constitutive model for FDEM to simulate the
nonlinear mechanical behavior of rocks
Yuchen Zhenga, Chengzeng Yana,b,*, Hong Zhengc
aFaculty of Engineering, China University of Geosciences, Wuhan 430074, China
bNational Center for International Research on Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan 430074, China
cKey Laboratory of Urban Security and Disaster Engineering, Ministry of Education, Beijing University of Technology, Beijing 100124, China
A R T I C L E I N F O A B S T R A C T
Keywords: The closure behavior of fractured rock, which is a crucial characteristic, is challenging to simulate accurately
Finite-discrete element method using commonly employed numerical models. To address this issue and accurately replicate the nonlinear me-
Modified joint element constitutive chanical behavior of rock, we propose a modified joint element constitutive model for the finite-discrete element
Rock compression simulation
method (FDEM). The modified model resolves the stress on both sides of the crack by considering the aperture of
Nonlinear mechanical behavior
the broken joint element instead of contact. Additionally, Joint elements with virtual opening, which are referred
to as preprocessed joint elements (Pre-JEs), are implemented in this model. We extensively discuss two pa-
rameters associated with Pre-JEs to elucidate their impact on the nonlinear mechanical behavior of rock. Our
findings demonstrate that the incorporation of Pre-JEs leads to a reduction in the compressive strength of rock.
Furthermore, increasing the thickness of Pre-JEs results in the softening of the elastic modulus. Moreover, we
have made improvements to the conventional calibration procedure for input parameters in FDEM. By employing
our enhanced methodology, we successfully reproduce the crack closure behavior and peak strength of Lac du
Bonnet granite using the proposed model.
1. Introduction been employed to examine the impact of microcracks and heterogeneity
on rock mechanical behavior. For instance, Malan et al. (Malan and
The mechanical behaviors and failure processes of rock have always Napier, 1995; Malan et al., 1994) successfully simulated extension tests
been a prominent area of interest in the field of rock mechanics. Among by modeling initial through-grain microcracks in quartzite using a
various methods employed to investigate the mechanical properties of displacement discontinuity approach. Blair et al. (Blair and Cook, 1998;
rock, the uniaxial or triaxial compression test stands out as the most Blair et al., 1993) proposed a non-linear rule-based model to analyze the
fundamental and straightforward approach. By analyzing the stress–- post-peak behavior of heterogeneous rock under compressive loading.
strain curve, one can gain intuitive insights into the deformation and The utilization of heterogeneity model has proven to be an effective
strength characteristics of rock. means of simulating the nonlinear mechanical behavior of rock. One
To comprehend the damage process of brittle rocks under compres- approach involves incorporating random distribution function, such as
sion, Wawersik and Fairhurst (1970) categorized stress–strain paths into the Weibull distribution (Tang et al., 1998) and the normal distribution
several distinct regions. Building upon this foundation, Martin (1993) (Manouchehrian and Cai, 2016), to assign materials parameters.
and Cai (2010) made further advancements by refining these regions Another method entails modeling the polycrystalline characteristics of
into the following stages: crack closure, elastic to stable crack growth, rock, such as establishing an image-based heterogeneous model (Liu
and initiation of macro-scale shear failure/unstable crack growth. et al., 2004; Mahabadi et al., 2014) or i
```
