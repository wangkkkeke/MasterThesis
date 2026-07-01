# Calibration of Microscopic Penalty Parameters in the Combined Finite–Discrete-Element Method

## Abstract

:Withuniqueadvantagesinsimulatingsolidfracture,thecombinedfinite–discrete-elementmethodhasbecomeincreasinglypop- ularintherockmechanicsfield.Nevertheless,alargenumberofmicroscopicparametersinthemethodneedtobespecifiedandmanyofthem cannotbedirectlymeasuredvialaboratorytests.Therefore,theseparametersmustbedeterminedviaacalibrationprocedure.Tocalibrate appropriatemicroscopicparameters,weshouldfindtherelationshipbetweenthemandthemacroscopicmechanicalresponse.Inthesemi- croscopic parameters, the normal and tangential penalty parameters play a very important role. Thus, in this paper we study the effect of penaltyparametersonmacroscopic mechanical parametersin thecombinedfinite–discrete-element method. Itisfoundthat asthepenalty parametersincrease,theelasticmodulusandPoisson’sratiograduallyapproachtheexperimentalvalues.However,thefurtherincreaseof penalty parameters has little effect on the elastic modulus and Poisson’s ratio when they reach 100 times the elastic modulus. Based on thisconclu

## Extracted Text (First Pages)

```
Calibration of Microscopic Penalty Parameters in the
–
Combined Finite Discrete-Element Method
Chengzeng Yan1 and Yao Tong2
Abstract:Withuniqueadvantagesinsimulatingsolidfracture,thecombinedfinite–discrete-elementmethodhasbecomeincreasinglypop-
ularintherockmechanicsfield.Nevertheless,alargenumberofmicroscopicparametersinthemethodneedtobespecifiedandmanyofthem
cannotbedirectlymeasuredvialaboratorytests.Therefore,theseparametersmustbedeterminedviaacalibrationprocedure.Tocalibrate
appropriatemicroscopicparameters,weshouldfindtherelationshipbetweenthemandthemacroscopicmechanicalresponse.Inthesemi-
croscopic parameters, the normal and tangential penalty parameters play a very important role. Thus, in this paper we study the effect of
penaltyparametersonmacroscopic mechanical parametersin thecombinedfinite–discrete-element method. Itisfoundthat asthepenalty
parametersincrease,theelasticmodulusandPoisson’sratiograduallyapproachtheexperimentalvalues.However,thefurtherincreaseof
penalty parameters has little effect on the elastic modulus and Poisson’s ratio when they reach 100 times the elastic modulus. Based on
thisconclusion,asimplemethodforthecalibrationofpenaltyparametersisproposed,whichcanbeusedtoquicklydeterminethepenalty
parametersaccordingtotheuniaxialcompressiontest.DOI:10.1061/(ASCE)GM.1943-5622.0001686.©2020AmericanSocietyofCivil
Engineers.
Authorkeywords:Combinedfinite–discrete-element;Penaltyparameter;Macro-microscopicparametersrelationship;Parametercalibra-
tion;Uniaxialcompressiontest;Braziliantest.
Introduction triangular elements. The crack initiation and propagation can be
simulatedbythebreakingofthejointelement.Thus,thecharacter-
Continuum methods [FEM, boundary-element method (BEM)] ization of the crack is very intuitive. In addition, the FDEM also
and discontinuum methods [discrete-element method (DEM)] well preserves the concepts of stress and strain in continuum
(Cundall1971;Cundall1988;CundallandStrack1979),[discon- mechanics.
tinuous deformation analysis (DDA)] (Shi 1992a, Yang et al. Based on these superiorities, the FDEM is most suitable for
2018), [numerical manifold method (NMM)] (Shi 1992b, Wu simulatingrockfracturing(Leietal.2015;Leietal.2019;Lisjak
etal.2019;Yangetal.2016)havebeencommonlyusedinstudies and Grasselli 2014; Liu and Deng 2019; Mahabadi et al. 2014;
of rock deformation and fracturing behavior (Cheng et al. 2017; Mahabadietal.2012;MunjizaandAndrews1998;Munjizaetal.
Dorren 2003; Jing 2003; Tang et al. 2019). However, although 1999b; Rougier et al. 2014; Yan and Jiao 2018; Yan and Jiao
the continuum methods can well simulate the deformation, their 2019a; Yan and Jiao 2019b; Yan and Zheng 2016; Yan and
continuity assumption makes it difficult for those methods to Zheng 2017a; Yan and Zheng 2017b; Yan and Zheng 2017c;
handlethecontactandthecomplexcrackinitiationandpropagation Yan and Zheng 2017d; Yan et al. 2016; Yan et al. 2018; Yan
(BaoquanandTannant2007;CundallandStrack1979).Meanwhile, et al. 2019a; Yan et al. 2019b; Yan et al. 2019c). Although this
discontinuummethodssuchastheDEMhavelimitationsindealing method was put forward as early as 1995 (Munjiza et al. 1995)
with deformation or crack initiation and propagation (Lisjak and and a monograph about the FDEM was published in 2004 by
Grasselli2010;WilliamsandJohn1988;WilliamsandMustoe1987). Munjiza (2004), the relevant researches and applications were
Therefore,combiningtheadvantagesofthetwodifferentmeth- still rare before 2010. After that, it became increasingly popular
ods(Ghaboussi1988),Munjizaetal.(Munjiza2004;Munjizaetal. inthefieldofrockmechanics,especiallyinrockfracturemodeling
1999b) proposed the combined finite–discrete-element method (Fukudaetal.2019;Gaoetal.2019;Lietal.2019;Vazaiosetal.
(FDEM).Itusestriangularfinite-elementmeshesfordiscretization, 2019).However,theFDEMneedsplentyofmicroscopicparame-
whichmakesthepre-processingverysimple,andtheinitialmodel ters and many of them are difficult to determine; for example, a
hasnogapscomp
```
