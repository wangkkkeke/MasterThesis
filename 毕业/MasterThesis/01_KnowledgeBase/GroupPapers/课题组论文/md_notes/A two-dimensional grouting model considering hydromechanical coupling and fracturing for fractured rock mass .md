# A two-dimensional grouting model considering hydromechanical coupling and fracturing for fractured rock mass 

## Abstract

Keywords: A two-dimensional grouting model considering hydromechanical coupling and fracturing in fractured rock is Grouting proposed and implemented in an GPU parallel multiphysics finite element-discrete element software named Combined finite-discrete element method MultiFracs. The model can simulate the grout flows in existing and induced fractures in the rock media. The (FDEM) fracture network is represented by broken joint elements, which is updated to simulate fracture initiation and Hydromechanical coupling propagation during grouting. Therefore, both the hydromechanical coupling effect and rock fracturing are Fractured rock mass considered in the grouting model. A single-fracture grouting example is presented to verify the grouting model. Rock fracturing Finally, the model is used to simulate the grouting process in a rock mass with a complex fracture network. The effects of grout yield stress, amount of injection holes, injection pressure, aperture, and especially hydrome- cha

## Extracted Text (First Pages)

```
EngineeringAnalysiswithBoundaryElements133(2021)385–397
Contents lists available at ScienceDirect
Engineering Analysis with Boundary Elements
journal homepage: www.elsevier.com/locate/enganabound
A two-dimensional grouting model considering hydromechanical coupling
and fracturing for fractured rock mass
Chengzeng Yana,b,d, Yao Tonga, Zhiqiang Luoa, Wenhui Kec, Gang Wangb,*
aFaculty of Engineering, China University of Geosciences, Wuhan 430074, China
bDepartment of Civil and Environmental Engineering, Hong Kong University of Science and Technology, Clear Water Bay, China Hong Kong Special Administrative
Region
cWuhan Municipal Construction Group Co., Ltd., Wuhan, Hubei 430023, China
dInternational Joint Research Center for Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan 430074, China
A R T I C L E I N F O A B S T R A C T
Keywords: A two-dimensional grouting model considering hydromechanical coupling and fracturing in fractured rock is
Grouting proposed and implemented in an GPU parallel multiphysics finite element-discrete element software named
Combined finite-discrete element method MultiFracs. The model can simulate the grout flows in existing and induced fractures in the rock media. The
(FDEM)
fracture network is represented by broken joint elements, which is updated to simulate fracture initiation and
Hydromechanical coupling
propagation during grouting. Therefore, both the hydromechanical coupling effect and rock fracturing are
Fractured rock mass
considered in the grouting model. A single-fracture grouting example is presented to verify the grouting model.
Rock fracturing
Finally, the model is used to simulate the grouting process in a rock mass with a complex fracture network. The
effects of grout yield stress, amount of injection holes, injection pressure, aperture, and especially hydrome-
chanical coupling on grout penetration are studied. The results show that the grouting model can simulate the
interaction between grouting-induced fractures and pre-existed fractures.
1. Introduction the opening, and closing of the fractures, the initiation, and the expan-
sion of fractures are not considered. For instance, Xiao et al. [17] pro-
Grouting has been widely used for reinforcing fractured rock mass, posed a simplified grouting model including the inertia force that can
water sealing, and prevention of foundation leakage in underground greatly improve the computational efficiency of a grouting simulation in
engineering [1–9]. Grouting is a complex process as it involves many a complex fracture network. Zhang et al. [18] built a cement-water glass
disciplines, such as materials, chemistry, and fluid mechanics [10–13]. (c-s) model considering the grout penetration in a plane fracture to study
Scholars have studied the grouting process through various experiments. the influence of injection pressure, fluid velocity, fracture width, and
For example, Lu et al. [14] studied viscosity changes and setting times in other factors on the rheological characteristics of this model. Pedrotti
the grouting process in laboratory tests using water glass in loose coal et al. [19] proposed an analytical grouting model that considers changes
seams. Based on a cement grouting permeability model, Eriksson [15] in pH, electrolyte concentration, cation valency and molar mass, silica
successfully predicted the grout penetration length. By using a fracture particle size, and silica concentration giving predictive capability
model, Funehag and Tho¨rn [16] studied the grout penetration lengths of without the need for site-specific calibration. Zou et al. [20] proposed a
mortar runoff under different pore sizes and discovered that the grout two-phase flow model for Bingham fluids flow in saturated networks to
penetration length increases if the pore size rises. investigate the influence of fracture network geometry and aperture
Nevertheless, these experiments have been typically limited to distribution on cement gro
```
