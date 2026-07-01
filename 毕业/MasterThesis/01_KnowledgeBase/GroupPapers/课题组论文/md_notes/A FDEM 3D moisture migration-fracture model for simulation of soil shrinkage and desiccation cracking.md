# A FDEM 3D moisture migration-fracture model for simulation of soil shrinkage and desiccation cracking

## Abstract

Keyword: This paper proposes a three-dimensional moisture migration model, which can simulate the moisture migration FDEM process in soil. A simple moisture transport example with analytic solutions is given to verify the correctness of Moisture migration the 3D moisture migration model. Combining the moisture migration model with the combined finite discrete Desiccation cracking element method (FDEM), a moisture migration-fracture model that simulates soil shrinkage and cracking is Clayey soil shrinkage constructed and implemented in an in-house GPU parallel multiphysics finite element-discrete element software, namely MultiFracs. The calculation process of the three-dimensional moisture migration-fracture model is: first obtain the moisture field distribution of the solution domain through the moisture migration model; then obtain the shrinkage stress in all tetrahedral elements according to the change of the moisture field; finally, apply the shrinkage stress as a load to perform th

## Extracted Text (First Pages)

```
ComputersandGeotechnics140(2021)104425
Contents lists available at ScienceDirect
Computers and Geotechnics
journal homepage: www.elsevier.com/locate/compgeo
A FDEM 3D moisture migration-fracture model for simulation of soil
shrinkage and desiccation cracking
Chengzeng Yana,b, Yuchen Zhenga, Wenhui Kec, Gang Wangb,*
aFaculty of Engineering, China University of Geosciences, Wuhan, China
bDepartment of Civil and Environmental Engineering, Hong Kong University of Science and Technology, Clear Water Bay, Hong Kong Special Administrative Region
cWuhan Municipal Construction Group Co., Ltd., Wuhan, Hubei, China
A R T I C L E I N F O A B S T R A C T
Keyword: This paper proposes a three-dimensional moisture migration model, which can simulate the moisture migration
FDEM process in soil. A simple moisture transport example with analytic solutions is given to verify the correctness of
Moisture migration the 3D moisture migration model. Combining the moisture migration model with the combined finite discrete
Desiccation cracking
element method (FDEM), a moisture migration-fracture model that simulates soil shrinkage and cracking is
Clayey soil shrinkage
constructed and implemented in an in-house GPU parallel multiphysics finite element-discrete element software,
namely MultiFracs. The calculation process of the three-dimensional moisture migration-fracture model is: first
obtain the moisture field distribution of the solution domain through the moisture migration model; then obtain
the shrinkage stress in all tetrahedral elements according to the change of the moisture field; finally, apply the
shrinkage stress as a load to perform the deformation and fracture calculations of FDEM. The 3D moisture
migration-fracture model is used to simulate an experiment of clayey soil shrinkage cracking. Image recognition
technology is used to carry out quantitative statistics and analysis of desiccation crack patterns. The simulation
results show high consistency with the laboratory experiment. Moreover, the influences of shrinkage parameter,
water evaporation rate, and layer thickness on clayey soil desiccation cracking are studied comprehensively.
1. Introduction driven cracks provide evidences of the existence of water on Mars (El-
Maarry et al., 2015; Rapin et al., 2019; Stein et al., 2018). In summary,
In recent years, drought events occurred more frequently due to soil desiccation cracking involves various fields, and it is necessary to
global warming and water shortages (Bordoloi et al., 2020). Desiccation study it.
cracks may occur in clayey soils due to water loss. Many problems are Many researchers have studied the shrinkage and cracking of soil
closely related to the dry-driven shrinkage and cracking of the clayey through experiments. Al-Jeznawi et al. (2019) studied on curling
soil. Desiccation cracks result in loss of cohesive force inside the clay and development of soils with drying. Konrad and Ayad (2011) pointed out
significantly reduce the soil’s strength (Tang et al., 2020; Tang et al., that desiccation cracking is related to soil type, and no crack was
2015). Desiccation cracks also provide a channel for surface water observed in the cohesionless soil. Some researchers (Hirobe and Oguni,
infiltration, which aggravates the instability of the slope (Tichavský 2016; Li and Zhang, 2011; Nahlawi and Kodikara, 2006; Peron et al.,
et al., 2019), increases riverbank erosion (McMahon et al., 2020), and 2009b) have focused on the initiation conditions, evolution laws, and
harms the geotechnical engineering infrastructures and green in- network forms of dry-driven cracks. Others (Huo et al., 2019; Nahlawi
frastructures (Lai et al., 2019). At the same time, loss of nutrition and Kodikara, 2006; Shepidchenko et al., 2020; Tang et al., 2008; Wei
through desiccation cracks inhibits crop growth (Lechner et al., 2016; et al., 2016) have systematically investigated the mechanism of desic-
Pardow and Lakatos, 2013). Some cracked soils are consolidated
```
