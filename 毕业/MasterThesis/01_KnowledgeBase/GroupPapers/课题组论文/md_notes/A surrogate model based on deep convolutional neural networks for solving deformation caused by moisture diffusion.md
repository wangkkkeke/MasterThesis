# A surrogate model based on deep convolutional neural networks for solving deformation caused by moisture diffusion

## Abstract

Keywords: Moisture diffusion is a common phenomenon in geotechnical engineering, and its induced deformation seriously Deep convolutional neural networks affects the stability of the engineering structure, such as embankment slope instability and tunnel surrounding Moisture diffusion-deformation coupling rock deformation. Numerical simulation is an effective method for moisture diffusion-deformation coupling Finite discrete element method (FDEM) computation, but it has a large computational cost and a high learning threshold for ordinary engineers. In this MultiFracS paper, a surrogate model based on deep convolutional neural networks is presented for moisture diffusion- deformation coupling computation. First, designing the neural network structure includes the dense blocks and transition layers, and hyperparameters. Then, the moisture diffusion-deformation coupling model in the finite discrete element method (FDEM) software package MultiFracS is used to obtain the high-fidelity simul

## Extracted Text (First Pages)

```
EngineeringAnalysiswithBoundaryElements157(2023)353–373
Contents lists available at ScienceDirect
Engineering Analysis with Boundary Elements
journal homepage: www.elsevier.com/locate/enganabound
A surrogate model based on deep convolutional neural networks for solving
deformation caused by moisture diffusion
Zhiqiang Luoa, Chengzeng Yana,b,*, Wenhui Kec, Tie Wanga, Mingzhao Xiaoc
aFaculty of Engineering, China University of Geosciences, Wuhan 430074, China
bNational Center for International Research on Deep Earth Drilling and Resource Development, China University of Geosciences, Wuhan 430074, China
cWuhan Municipal Construction Group Co., Ltd., Wuhan, Hubei 430023, China
A R T I C L E I N F O A B S T R A C T
Keywords: Moisture diffusion is a common phenomenon in geotechnical engineering, and its induced deformation seriously
Deep convolutional neural networks affects the stability of the engineering structure, such as embankment slope instability and tunnel surrounding
Moisture diffusion-deformation coupling rock deformation. Numerical simulation is an effective method for moisture diffusion-deformation coupling
Finite discrete element method (FDEM)
computation, but it has a large computational cost and a high learning threshold for ordinary engineers. In this
MultiFracS
paper, a surrogate model based on deep convolutional neural networks is presented for moisture diffusion-
deformation coupling computation. First, designing the neural network structure includes the dense blocks
and transition layers, and hyperparameters. Then, the moisture diffusion-deformation coupling model in the
finite discrete element method (FDEM) software package MultiFracS is used to obtain the high-fidelity simulation
data for the moisture diffusion-deformation examples. The simulation data and the key parameter (elastic
modulus and Poisson’s ratio) are processed into the image data structure (matrix) for training the surrogate
model. Finally, the root means square error and the correlation coefficient are used to evaluate the effectiveness
of the surrogate model. The results reveal that, rather than taking several hours to run a numerical model, the
surrogate model only takes a few seconds to obtain the deformation and stress under a given moisture field and
material parameters, which significantly improves prediction efficiency. Using this surrogate model, the engi-
neers can obtain the deformation law just only modifying key parameters. Moreover, the surrogate model can be
packaged into a mobile app to provide support for rapid decision-making on the project site.
1. Introduction surrounding rocks based on the theory of moisture stress field and
elastoplastic theory. Liu et al. [4] deduced an analytical solution for the
Moisture diffusion is a common coupling problem in geotechnical non-stationary moisture diffusion process according to Fick’s second law
engineering, and it may cause some engineering problems. For example, and consider the swelling phenomenon of soft rock induced by the
in tunnel engineering [1], moisture diffusion induces time-dependent moisture diffusion. Tang et al. [5] proposed a coupled mechanical and
deformation of the tunnel. In subgrade engineering [2], non-uniform diffusion model to determine the instantaneous and time-dependent
settlement and shear failure of the contact surface between layers are elastoplastic behaviors of an excavation-damaged zone (EDZ) under
common consequences of moisture diffusion. The moisture high moisture conditions. For soil, Peron et al. [6] conducted free drying
diffusion-deformation coupling problem in engineering practice has tests, restrained drying tests, and crack morphology tests on three kinds
become increasingly prominent because of the extreme arid climates in of fine-grained soils to study the drying characteristics of the initial
recent years. saturated soil layer.
To deeply study the moisture diffusion-deformation coupling Compared to theoretical derivation and experiments, nume
```
