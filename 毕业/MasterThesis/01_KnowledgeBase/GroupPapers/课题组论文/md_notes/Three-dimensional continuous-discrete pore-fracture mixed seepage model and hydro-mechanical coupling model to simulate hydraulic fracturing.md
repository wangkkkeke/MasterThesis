# Three-dimensional continuous-discrete pore-fracture mixed seepage model and hydro-mechanical coupling model to simulate hydraulic fracturing

## Abstract

Keywords: A three-dimensional (3D) continuous-discrete seepage mixed model is presented, which considers the fluid ex- Pore-fracture mixed seepage change and the pore pressure discontinuity at the fracture. In this model, both the fracture seepage and pore Hydro-mechanical coupling seepage are considered simultaneously. Moreover, the node sharing connection of the neighboring elements near Hydraulic fracturing the fracture are dynamically updated during fracture propagation. The pore pressure discontinuity and fluid Finite-discrete element method (FDEM) exchange at the fracture can be well considered but the virtual joint element and its very large exchange co- efficient do not need to be introduce. The mixed model is coupled with finite discrete element method (FDEM) to create a hydro-mechanical coupling model for simulating hydraulic fracturing. Three examples are given to verify the mixed seepage model and hydro-mechanical coupling model. Finally, a hydraulic fracturing experi- ment

## Extracted Text (First Pages)

```
JournalofPetroleumScienceandEngineering215(2022)110510
Contents lists available at ScienceDirect
Journal of Petroleum Science and Engineering
journal homepage: www.elsevier.com/locate/petrol
Three-dimensional continuous-discrete pore-fracture mixed seepage model
and hydro-mechanical coupling model to simulate hydraulic fracturing
Chengzeng Yana,b, Hui Guoa, Zhicheng Tanga,*
aFaculty of Engineering, China University of Geosciences, Wuhan, 430074, China
bInternational Joint Research Center for Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan, 430074, China
A R T I C L E I N F O A B S T R A C T
Keywords: A three-dimensional (3D) continuous-discrete seepage mixed model is presented, which considers the fluid ex-
Pore-fracture mixed seepage change and the pore pressure discontinuity at the fracture. In this model, both the fracture seepage and pore
Hydro-mechanical coupling seepage are considered simultaneously. Moreover, the node sharing connection of the neighboring elements near
Hydraulic fracturing
the fracture are dynamically updated during fracture propagation. The pore pressure discontinuity and fluid
Finite-discrete element method (FDEM)
exchange at the fracture can be well considered but the virtual joint element and its very large exchange co-
efficient do not need to be introduce. The mixed model is coupled with finite discrete element method (FDEM) to
create a hydro-mechanical coupling model for simulating hydraulic fracturing. Three examples are given to
verify the mixed seepage model and hydro-mechanical coupling model. Finally, a hydraulic fracturing experi-
ment is simulated by using the coupling model. The simulation results demonstrate that the differences in in-situ
stress and approach angle are the most important factors controlling the fracture propagation behavior, and the
shear strength of natural fractures also affects the intersection mode.
1. Introduction discrete fracture network model to describe the fracture seepage
accurately.
Many instability and damage problems in geotechnical engineering The hydro-mechanical models mainly include analytical models and
are related to water, which involves two issues. The first is the law of numerical models. The primary purpose of these models is proposed to
water seepage. The Second is the interaction between water and rock solve hydraulic fracturing problems. In analytical models, Perkins and
mass. In order to solve the above problems, a series of models are pro- Kern [9] and Nordgren [10] built a 2D plane strain PKN model to
posed including (1) Computational model of seepage in complex frac- consider the effect of fluid loss. Under some simplified assumptions,
tured rock mass; (2) Hydro-mechanical coupling model. Khristianovic and Zheltov (1955), Geertsma and De Klerk (Geertsma and
Many researchers have studied the seepage in fractured rock masses De Klerk, 1969) proposed a fracture propagation model in continuous,
and built different seepage models. Among, Long et al. (1982) built a uniform, isotropic and linear elastic media, namely the KGD model.
two-dimensional (2D) fracture system model based on the continuum Sneddon (1946) proposed a penny-shaped model in which the fluid
seepage theory. Warren and Root (1963) first proposed a dual-media pressure is constant. Settari and Cleary (1986) developed a
seepage model, which simultaneously considers the permeability of pseudo-three-dimensional (P3D) model to describe the evolution of the
fractures and rock matrices. However, the rock matrices on both sides of geometry of 3D hydraulic fractures created by injecting fluid into the
the fracture in this model share pore nodes, the pore pressure across the reservoir. Later, researchers no longer emphasized presenting new
fracture are continuous. In addition, very fine meshes are required in the analytical models but focused on studying the relevant parameters of
model because the fracture is usually narrow. Zhao et al. (2021) pro- exist
```
