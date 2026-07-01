T0=80;Tin=30;
rof=1000;cf=4200;
ros=2700;cs=1000;lamdas=3;
uf=0.01;
df=0.001;

x=0:1:100;
flag=1;
t=10*24*60*60;
outfilename='TH-fluid-10day.dat';
Plot_TH_analysis_fluid( T0,Tin,rof,cf,df,uf,lamdas,ros,cs,x,t,flag,outfilename);
hold on

x=0:1:100;
flag=1;
t=25*24*60*60;
outfilename='TH-fluid-25day.dat';
Plot_TH_analysis_fluid( T0,Tin,rof,cf,df,uf,lamdas,ros,cs,x,t,flag,outfilename);
hold on

x=0:1:100;
flag=1;
t=50*24*60*60;
outfilename='TH-fluid-50day.dat';
Plot_TH_analysis_fluid( T0,Tin,rof,cf,df,uf,lamdas,ros,cs,x,t,flag,outfilename);
hold on

x=0:1:100;
flag=1;
t=100*24*60*60;
outfilename='TH-fluid-100day.dat';
Plot_TH_analysis_fluid( T0,Tin,rof,cf,df,uf,lamdas,ros,cs,x,t,flag,outfilename);