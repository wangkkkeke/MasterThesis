# A 3D thermal cracking model for rockbased on the combined finite–discrete element method

## Keywords

Finite–discrete element method (FDEM) · FDEM-TM3D · Thermomechanical coupling · Thermal stress · Thermal cracking

## Extracted Text (First Pages)

```
Computational Particle Mechanics
https://doi.org/10.1007/s40571-019-00281-w
A 3D thermal cracking model for rockbased on the combined
finite–discrete element method
Chengzeng Yan1,2 · Yuhang Ren1 · Yongtao Yang3
Received: 22 February 2019 / Revised: 17 June 2019 / Accepted: 30 August 2019
© OWZ 2019
Abstract
A three-dimensional coupled thermomechanical model is proposed which can simulate crack initiation, propagation and
coalescence, as well as the distribution of stress and temperature during thermal cracking. The model consists of two parts:
The temperature distribution of the system is calculated according to the heat conduction equation, the thermal stress caused
by temperature is applied to the system equation and a mechanical calculation considering cracking is performed. Three
examples are given to verify the model regarding the problems of heat conduction, thermomechanical coupling and thermal
cracking. This model has the potential to be applied to geothermal or oil exploitation and nuclear waste disposal.
Keywords Finite–discrete element method (FDEM) · FDEM-TM3D · Thermomechanical coupling · Thermal stress ·
Thermal cracking
1 Introduction
rate, outlet water temperature and heat recovery efficiency
of the enhanced geothermal system (EGS).
The thermal cracking of rock is a very common phenomenon In the past, extensive laboratory experiments have been
that occurs in both nature and engineering activities. Ther- conducted to study the thermomechanical behavior or
mal cracking increases the fracture length, density and con- thermal cracking of brittle material [1–7]. However, large
nectivity within a rock, which greatly improves its transport expense and limitation in simple cases of such experiments
characteristics. In nuclear waste storage, the decay of nuclear led to an increased interest in using numerical methods to
waste produces heat and significantly increases the tempera- study thermal cracking [8–11]. For example, Fu et al. [12]
ture of the surrounding rock. This temperature change results and Tang et al. [13, 14] proposed a thermomechanical cou-
in the thermal cracking of rock, leading to radionuclide dif- pled model in a realistic failure process analysis system
fusion and groundwater pollution eventually. In oil devel- (RFPA) for simulating the thermal cracking of brittle mate-
opment, thermal cracking increases the permeability of the rial [15, 16]. Jiao et al. [17] proposed a thermomechani-
reservoir and raises oil production. In the geothermal devel- cal coupled model in discontinuous deformation analysis
opment of hot dry rock, rock contraction occurs when cold method for simulating rock fracturing induced by thermal
water is injected into the reservoir and influences the flow stress. Wanne and Young [18], Xia [19] and Andre et al. [20]
simulated the thermal cracking of rock based on the bonded
particle model (BPM). Nechnech et al. [21] presented an
elastoplastic damage model for the thermomechanical analy-
*
Chengzeng Yan sis of concrete. Sun and Liew [22] studied the thermome-
yancz@cug.edu.cn; yanchengzheng86@gmail.com
chanical coupling fracture behavior of materials based on the
1 Faculty of Engineering, China University of Geosciences, cohesive segment model. Tenchev and Purnell [23] extended
Wuhan 430074, Hubei, China a damage constitutive model to account for the effect of high
2 International Joint Research Center for Deep Earth temperature on concrete.
Drilling and Resource Development, China University The aforementioned numerical methods can be clas-
of Geosciences, Wuhan 430074, China sified into two categories: methods based on continu-
3 State Key Laboratory of Geomechanics and Geotechnical ous mechanics and approaches based on discontinu-
Engineering, Institute of Rock and Soil Mechanics, Chinese ous mechanics. For the methods based on continuous
Academy of Sciences, Wuhan 430071, China
Vol.:(0112 33456789)
--- PAGE BREAK ---
Computational Particle Mechanics
mechanics, crack initiation, p
```
