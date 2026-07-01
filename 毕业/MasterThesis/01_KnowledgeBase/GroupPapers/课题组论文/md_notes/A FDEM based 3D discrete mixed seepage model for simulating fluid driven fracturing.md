# A FDEM based 3D discrete mixed seepage model for simulating fluid driven fracturing

## Abstract

Keywords: This paper presents a 3D discrete mixed seepage model that considers the effect of fracture on pore seepage. We Fracture seepage unify the 3D fracture-pore mixed seepage model and finite-discrete element method (FDEM) to build a coupled Pore seepage hydro-mechanical model to simulate the fluid-driven deformation and fracturing, which can also consider the Hydro-mechanical coupling influence of fracture propagation on fracture seepage and pore seepage. The model has been implemented in a Hydraulic fracturing GPU parallel multiphysics finite-discrete element software MultiFracS. For the continuum seepage problem, we Combined finite-discrete element method (FDEM) conduct a parameter sensitivity analysis for the fluid exchange coefficient and propose the criterion for selecting the coefficient. Then, we verify the model to deal with 3D pore seepage in a continuum media, fracture-pore seepage in discontinuous media with a single fracture, and fracture-pore seepage in discontinuous

## Extracted Text (First Pages)

```
EngineeringAnalysiswithBoundaryElements140(2022)447–463
Contents lists available at ScienceDirect
Engineering Analysis with Boundary Elements
journal homepage: www.elsevier.com/locate/enganabound
A FDEM based 3D discrete mixed seepage model for simulating fluid
driven fracturing
Chengzeng Yana,b,*, Yakun Gaoa, Hui Guoa
aFaculty of Engineering, China University of Geosciences, Wuhan, Hubei 430074, China
bInternational Joint Research Center for Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan 430074, China
A R T I C L E I N F O A B S T R A C T
Keywords: This paper presents a 3D discrete mixed seepage model that considers the effect of fracture on pore seepage. We
Fracture seepage unify the 3D fracture-pore mixed seepage model and finite-discrete element method (FDEM) to build a coupled
Pore seepage hydro-mechanical model to simulate the fluid-driven deformation and fracturing, which can also consider the
Hydro-mechanical coupling
influence of fracture propagation on fracture seepage and pore seepage. The model has been implemented in a
Hydraulic fracturing
GPU parallel multiphysics finite-discrete element software MultiFracS. For the continuum seepage problem, we
Combined finite-discrete element method
(FDEM) conduct a parameter sensitivity analysis for the fluid exchange coefficient and propose the criterion for selecting
the coefficient. Then, we verify the model to deal with 3D pore seepage in a continuum media, fracture-pore
seepage in discontinuous media with a single fracture, and fracture-pore seepage in discontinuous media with
multi-fractures. Finally, the coupled hydro-mechanical model is employed to study a one-dimensional consoli-
dation and a hydraulic fracturing problem. The research shows that the simulation results are in good agreement
with the analytical solutions and the experimental results, which verifies the effectiveness of the method for
solving the 3D fracture-pore mixed seepage and the coupled hydro-mechanical model for dealing with seepage
problems in fractured porous media and fluid-driven fracturing.
1. Introduction Both the equivalent continuum model and the dual-continuum
model are continuum-based models and cannot characterize fractures
In the past few decades, hydraulic fracturing has gradually become explicitly. In the equivalent continuum model, fractured rocks are usu-
an important technology to increase the productivity of oil and natural ally converted into equivalent porous media. However, because there is
gas reservoirs in the energy industry [1,2]. The hydraulic fracturing no distinction between the fracture network and the rock matrix, the
technology increases the permeability of reservoirs by injecting equivalent continuum model cannot represent the high permeability of
high-pressure fluids into the reservoirs to form fractures in the fracture explicitly. The dual-continuum model was originally pro-
low-permeability rocks [3]. During this process, in addition to the posed by Warren and Root and Barenblatt et al. [6,7], which assumes
deformation and fracture of rocks and the fluid flow in fractures, fluid that both rock matrices and fractures have porosity and permeability
will also infiltrate into the rock matrix from the fracture. Thus, hydraulic [8–11]. The model can be considered as the superposition of the con-
fracturing involves the initiation and propagation of fractures but also servation equations and constitutive relations of two homogenized
involves fracture-pore mixed seepage. Therefore, it is necessary to continuum media by a transfer function [12]. However, the transfer
establish a mixed model for describing pore seepage and fracture function depends on shape factors, which is difficult to be described
seepage in fractured porous media. accurately. The dual-continuum model is not suitable when there is a
To simulate the fluid flow in fractured porous media accurately and localized preferential flow path in the fracture system [13].
effic
```
