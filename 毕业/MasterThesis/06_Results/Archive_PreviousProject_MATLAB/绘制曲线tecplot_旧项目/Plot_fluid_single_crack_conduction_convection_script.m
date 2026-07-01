%---2017-11-13Ìí¼Ó
% ro=1000;Cv=4200;lamda_f=0.6;T0=80;dP=10;u=0.001;a=1e-4;L=4;x=0:0.001:4;t=200000;
% outfilename='fluid_in_single_crack-200000.dat';
% hold on
% Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )

ro=1000;Cv=4200;lamda_f=0.6;T0=80;dP=10;u=0.001;a=1e-4;L=4;x=0:0.001:4;t=400000;
outfilename='fluid_in_single_crack-400000.dat';
hold on
Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )

ro=1000;Cv=4200;lamda_f=0.6;T0=80;dP=10;u=0.001;a=1e-4;L=4;x=0:0.001:4;t=600000;
outfilename='fluid_in_single_crack-600000.dat';
hold on
Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )

ro=1000;Cv=4200;lamda_f=0.6;T0=80;dP=10;u=0.001;a=1e-4;L=4;x=0:0.001:4;t=800000;
outfilename='fluid_in_single_crack-800000.dat';
hold on
Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )

ro=1000;Cv=4200;lamda_f=0.6;T0=80;dP=10;u=0.001;a=1e-4;L=4;x=0:0.001:4;t=1000000;
outfilename='fluid_in_single_crack-1000000.dat';
hold on
Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )