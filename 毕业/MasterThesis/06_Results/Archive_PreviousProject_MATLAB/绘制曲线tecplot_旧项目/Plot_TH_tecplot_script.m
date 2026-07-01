% 单条裂隙水热耦合 2017-6-13添加
T1=100;T2=0;
rof=1000;cf=0.2;kf=1.6;L=4;a=1e-4;p1=2e4;p2=0;u=0.001;
Plot_TH_tecplot( T1,T2,rof,cf,kf,L,a,p1,p2,u,'changtiao-T-state-p1=2e4.dat')

hold on
T1=100;T2=0;
rof=1000;cf=0.2;kf=1.6;L=4;a=1e-4;p1=0;p2=2e4;u=0.001;
Plot_TH_tecplot( T1,T2,rof,cf,kf,L,a,p1,p2,u,'changtiao-T-state-p2=2e4.dat')