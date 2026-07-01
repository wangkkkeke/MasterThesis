# A FDEM-based 2D coupled thermal-hydro-mechanical model for multiphysical simulation of rock fracturing

## Abstract

Keywords: A coupled thermal-hydro-mechanical (THM) model based on the combined finite-discrete element method Combined finite-discrete element method (FDEM) is presented for simulating rock cracking driven by multi-physics. The THM model contains three parts: a Thermal-hydro-mechanical (THM) coupling fracture-pore mixed seepage model, a heat transfer model, and a fracture mechanics calculation model. By Rock cracking combining any two of the above three models, a coupled thermal-mechanical (TM) model, a coupled hydro- Hydraulic fracturing thermal (TH) model, and a coupled hydromechanical (HM) model are constructed. Then, the TM model, TH Enhanced geothermal system (EGS) model, and HM model are combined to build the THM model, which is implemented in a GPU parallel multi- physics finite-discrete element software, namely MultiFracs. Finally, we use this THM model to study the hy- draulic fracturing process of hot dry rock. The simulation results indicate that in addition to the primary f

## Extracted Text (First Pages)

```
InternationalJournalofRockMechanics&MiningSciences149(2022)104964
Contents lists available at ScienceDirect
International Journal of Rock Mechanics and Mining Sciences
journal homepage: www.elsevier.com/locate/ijrmms
A FDEM-based 2D coupled thermal-hydro-mechanical model for
multiphysical simulation of rock fracturing
Chengzeng Yana,b,*, Xin Xiea, Yuhang Rena, Wenhui Kec, Gang Wangb,**
aFaculty of Engineering, China University of Geosciences, Wuhan, 430074, China
bDepartment of Civil and Environmental Engineering, Hong Kong University of Science and Technology, Clear Water Bay, Hong Kong SAR, China
cWuhan Municipal Construction Group Co., Ltd., Wuhan, Hubei, China
A R T I C L E I N F O A B S T R A C T
Keywords: A coupled thermal-hydro-mechanical (THM) model based on the combined finite-discrete element method
Combined finite-discrete element method (FDEM) is presented for simulating rock cracking driven by multi-physics. The THM model contains three parts: a
Thermal-hydro-mechanical (THM) coupling fracture-pore mixed seepage model, a heat transfer model, and a fracture mechanics calculation model. By
Rock cracking
combining any two of the above three models, a coupled thermal-mechanical (TM) model, a coupled hydro-
Hydraulic fracturing
thermal (TH) model, and a coupled hydromechanical (HM) model are constructed. Then, the TM model, TH
Enhanced geothermal system (EGS)
model, and HM model are combined to build the THM model, which is implemented in a GPU parallel multi-
physics finite-discrete element software, namely MultiFracs. Finally, we use this THM model to study the hy-
draulic fracturing process of hot dry rock. The simulation results indicate that in addition to the primary fracture
perpendicular to the direction of the minimum in situ stress, branching fractures along the direction of the
minimum in situ stress are also produced during the hydraulic fracturing process. The proposed THM model can
simulate heat and fluid transfer in fractured reservoirs, crack initiation, propagation, and intersection.
1. Introduction rock. In this process, not only can hydromechanical coupling cause rock
cracks,5 but the injected low-temperature fluid can also cause shrinkage
For many geotechnical problems, it is necessary to analyze thermal, deformation and the thermal cracking of high-temperature rocks.
hydraulic, and mechanical processes in rocks individually or in coupled Therefore, it is necessary to develop a numerical model that can consider
form. Over the past two decades, there has been an increasing interest in both THM coupling and rock cracking.
analyzing hydro-thermal-mechanical coupling processes in porous Numerical models for THM modeling in geomechanics can be clas-
geological media.1 It is crucial in the disposal of underground radioac- sified into two types: coupled THM models that include rock cracking
tive nuclear waste, the exploitation of natural gas and oil, geothermal and models that do not include rock cracking.
energy utilization et al. For example, to study the multiphysics coupling For coupled THM models that do not consider cracking, Sun et al.6
problems in nuclear waste disposal, international researchers initiated and Yao et al.7 proposed a coupled THM model in which the fractured
the DECOVALEX
project.2–4
The project has made outstanding rock mass is regarded as a dual-medium composed of a discrete fracture
achievements in verifying various computer codes and comparing THM network and a rock matrix. Bazant and Ohtsubo8 investigated the vari-
modeling methods. However, most of these THM coupling models are ation of fluid flow, heat advection, and fracture aperture in an EGS using
based on continuum mechanics, which cannot consider rock cracking the finite element method (FEM). Cao et al.9 proposed a novel model for
caused by various coupling effects. modeling the heat extraction process in an EGS. Feng et al.10 developed
Recently, the extraction of hot dry rock geothermal energy through a new heat conducti
```
