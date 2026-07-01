# A 2D discrete moisture diffusion model for simulating desiccation cracking

## Extracted Text (First Pages)

```
EngineeringAnalysiswithBoundaryElements138(2022)42–64
Contents lists available at ScienceDirect
Engineering Analysis with Boundary Elements
journal homepage: www.elsevier.com/locate/enganabound
A 2D discrete moisture diffusion model for simulating desiccation
fracturing of soil
Chengzeng Yana,*, Zhiqiang Luoa, Yucheng Zhenga, Wenhui Keb
aFaculty of Engineering, China University of Geosciences, Wuhan, China
bWuhan Municipal Construction Group Co., Ltd., Wuhan, Hubei, China
A R T I C L E I N F O A B S T R A C T
Keywords: The desiccation fracturing of soil is widespread, which affects the migration of rainwater in the soil, and the
FDEM stability of slopes or other projects. This paper proposes a simple two-dimensional (2D) discrete moisture
FDEM-moisture diffusion model considering the influence of fractures on moisture migration. The moisture diffusion model is
Moisture diffusion
used in conjunction with the finite discrete element method (FDEM) to create a 2D discrete moisture diffusion-
Soil desiccation fracturing
fracture coupling model, which is implemented in a GPU parallel multiphysics finite-discrete element software,
namely MultiFracS. The coupled model is made up of three parts: a 2D discrete moisture diffusion model that
takes into account the influence of fractures on moisture migration, a shrinkage deformation and stress
computation, and an FDEM fracture mechanical computation. First, the moisture distribution in the system is
analyzed using the moisture diffusion model. The shrinkage stress resulting from the moisture change is then
computed. Finally, the shrinkage stress is added to the governing equation of FDEM to perform the fracture
mechanical computation. Desiccation fracturing of the soil can be modeled using the processes outlined above.
The paper firstly verifies the correctness of the 2D discrete moisture diffusion model to deal with the moisture
migration in a continuous media, a media with impervious fractures or permeable fractures. Then, we give a
principle that is used to determine the moisture exchange coefficient of the unbroken joint element through the
parameter sensitivity analysis. Moreover, typical shrinkage deformation and stress problems and soil desiccation
fracturing experiments are simulated. The simulation results are in good agreement with the analytical solutions
and experiment results, verifying the effectiveness of the 2D discrete moisture diffusion-fracture coupling model
to deal with shrinkage deformation and stress problems and the desiccation fracturing of soil. The coupled model
provides a powerful solution tool to study the desiccation fracturing of soil.
1. Introduction desiccation of soil are usually important factors that cause slope slip-
page. In recent years, extreme arid climates occur frequently, and en-
The desiccation fracturing of soil caused by evaporation and mois- gineering or environmental problems caused by soil desiccation
ture loss is very common in nature. The fractures destroy the continuity fracturing gradually increase. The desiccation fracturing of soil has
of the soil and affect the mechanical properties of the soil and the attracted more and more attention.
moisture migration in the soil. Therefore, the desiccation fractures in the Scholars have conducted a large number of indoor experiments to
soil can directly or indirectly induce many engineering problems. For study the mechanism of soil desiccation fracturing. For example, Peron
example, in foundation engineering Rogers et al. [1], desiccation frac- et al. [8,9] conducted free drying experiments, constrained drying ex-
turing may cause uneven settlement of the foundation, and even incline periments, and fracture morphology experiments on three fine-grained
or fracturing of the building structure. In hydraulic engineering [2–4], soils (Bioley, Sion, and La Frasse) to study the characteristics of frac-
the desiccation fractures of soil may induce dam leakage or even failure. ture morphology in the soi
```
