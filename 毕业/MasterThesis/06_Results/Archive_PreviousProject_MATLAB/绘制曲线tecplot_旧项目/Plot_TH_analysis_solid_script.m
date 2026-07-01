% ----2017-9-6添加
Tr0=80;Tf0=30;kr=3;
rof=1000;cf=4200;vf=0.01;
a=0.001;ror=2700;cr=1000;

%-------y=52水平监测线 在t=10天时的岩石温度分布
flag=0; y=52-50;x=0:1:100;
t=10*24*60*60;
outfilename='TH-solid-10day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on
%-------y=52水平监测线 在t=25天时的岩石温度分布
flag=0; y=52-50;x=0:1:100;
t=25*24*60*60;
outfilename='TH-solid-25day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on
%-------y=52水平监测线 在t=50天时的岩石温度分布
flag=0; y=52-50;x=0:1:100;
t=50*24*60*60;
outfilename='TH-solid-50day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on
%-------y=52水平监测线 在t=100天时的岩石温度分布
flag=0; y=52-50;x=0:1:100;
t=100*24*60*60;
outfilename='TH-solid-100day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);

figure
%-------x=2水平监测线 在t=10天时的岩石温度分布
flag=1; x=2;y=-50:1:50;
t=10*24*60*60;
outfilename='TH-solid-x=2-10day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on

%-------x=2水平监测线 在t=25天时的岩石温度分布
flag=1; x=2;y=-50:1:50;
t=25*24*60*60;
outfilename='TH-solid-x=2-25day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on

%-------x=2水平监测线 在t=10天时的岩石温度分布
flag=1; x=2;y=-50:1:50;
t=50*24*60*60;
outfilename='TH-solid-x=2-50day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on

%-------x=2水平监测线 在t=10天时的岩石温度分布
flag=1; x=2;y=-50:1:50;
t=100*24*60*60;
outfilename='TH-solid-x=2-100day.dat';
Plot_TH_analysis_solid( Tr0,Tf0,kr,rof,cf,vf,a,ror,cr,flag,x,y,t,outfilename);
hold on
