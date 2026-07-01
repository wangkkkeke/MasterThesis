# A three-dimensional thermal-hydro-mechanical coupling model for simulation of fracturing driven by multiphysics

## Abstract

Keywords: Geothermal mining, nuclear waste disposal, and other projects involve rock fracturing under the multiphysics finite-discrete element method (FDEM) effect. There is an urgent need for a numerical analysis tool that can consider both thermal-hydro-mechanical Thermal-hydro-mechanical coupling coupling (THM) effects and rock fracturing to analyze such projects. This paper presents a three-dimensional Solid fracturing thermal-hydro-mechanical coupling model that can consider rock fracturing, which incorporates the advan- Hydromechanical coupling Thermal–mechanical coupling tages of the combined finite discrete element method (FDEM) for simulating fracture and fragmentation. The 3D Hydrothermal coupling thermal-hydro-mechanical coupling model includes three parts: fracture-pore mixed seepage model, heat transfer model (including heat conduction in solid and fluid, heat advection, heat exchange between solid and fluid), and FDEM fracture mechanics calculation model. Some examples wi

## Extracted Text (First Pages)

```
ComputersandGeotechnics155(2023)105162
Contents lists available at ScienceDirect
Computers and Geotechnics
journal homepage: www.elsevier.com/locate/compgeo
A three-dimensional thermal-hydro-mechanical coupling model for
simulation of fracturing driven by multiphysics
Chengzeng Yana,b,*, Ziheng Zhaoa, Yu Yanga, Hong Zhengc
aFaculty of Engineering, China University of Geosciences, Wuhan 430074, China
bNational Center for International Research on Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan 430074, China
cKey Laboratory of Urban Security and Disaster Engineering, Ministry of Education, Beijing University of Technology, Beijing 100124, China
A R T I C L E I N F O A B S T R A C T
Keywords: Geothermal mining, nuclear waste disposal, and other projects involve rock fracturing under the multiphysics
finite-discrete element method (FDEM) effect. There is an urgent need for a numerical analysis tool that can consider both thermal-hydro-mechanical
Thermal-hydro-mechanical coupling coupling (THM) effects and rock fracturing to analyze such projects. This paper presents a three-dimensional
Solid fracturing
thermal-hydro-mechanical coupling model that can consider rock fracturing, which incorporates the advan-
Hydromechanical coupling
Thermal–mechanical coupling tages of the combined finite discrete element method (FDEM) for simulating fracture and fragmentation. The 3D
Hydrothermal coupling thermal-hydro-mechanical coupling model includes three parts: fracture-pore mixed seepage model, heat
transfer model (including heat conduction in solid and fluid, heat advection, heat exchange between solid and
fluid), and FDEM fracture mechanics calculation model. Some examples with the analytical solution for seepage,
hydromechanical, thermal–mechanical, hydrothermal, and thermal-hydro-mechanical coupling problems are
used to verify the correctness of the FDEM based 3D THM model in detail. In addition, an example of rock
fracturing caused by the thermal-hydro-mechanical coupling effect is also given. The simulation results show that
the FDEM based 3D thermal-hydro-mechanical coupling model can simulate the complex fractures initiation,
propagation, and extension caused by multiphysics effects, such as heat, fluid, and mechanics.
1. Introduction barrier for nuclear waste disposal. Caulk et al. (2016) developed an
experimental approach to analyze the fracture permeability in the pro-
In the field of underground space, the failure and instability of rock cess of multiphysics coupling, such as the conditions of in-situ EGS.
are closely related to the interaction of the seepage field, temperature In addition, many scholars have also established some THM coupling
field, and stress field. Evaluating and predicting the safety and stability numerical models and achieved fruitful results in this field, especially
of the rock under the thermal-hydro-mechanical (THM) coupling effect promoted by the international cooperative research program (DECO-
is of great practical significance to many projects (Armand et al., 2017; VALEX) in nuclear waste disposal (Collin et al., 2002; Hicks et al., 1996;
Dao et al., 2015; Sun et al., 2019; Xie et al., 2014). The effect of THM Hudson et al., 2005; Liu et al., 2019.) These THM coupling models
coupling on rock has become an important research topic in under- include: (1) thermal-hydro-mechanical coupling models based on con-
ground engineering. tinuum mechanics; (2) thermal-hydro-mechanical coupling models
To deeply explore the failure mechanism of rock under the effect of based on discontinuous mechanics.
THM, many scholars have conducted a large number of experimental In applying the continuum method to carry out THM numerical
studies. Kumari et al. (2018) study the influence of reservoir depth, simulation, Cao et al. (2016) established a three-dimensional transient
temperature, heterogeneity, and microstructure on fracture propagation numerical model to simulate and analyze the hea
```
