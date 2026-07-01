function [ output_args ] = Plot_TH_tecplot( T1,T2,rof,cf,kf,L,a,p1,p2,u,outfilename )
%2017-6-13添加 绘制TH耦合的解析解并输出到tecplot
%   此处显示详细说明
q=-a^2/(12*u)*(p2-p1)/L;
pe=rof*cf*q*L/kf;
T2p=(T2-T1)/T1;
xp=0:0.01:1;
Tp=T2p*((exp(pe*xp)-1)/(exp(pe)-1));
T=Tp*T1+T1;
x=xp*L;
plot(x,T);

fidw=fopen(outfilename,'w');
fprintf(fidw,'TITLE = "Temperature along radi"\n');
fprintf(fidw,'VARIABLES = "X", "Temperature-fluid(<sup>0</sup>C)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature along x"\n');
pointTvalue=double([x; T]);
fprintf(fidw,'%e %e\n',pointTvalue);
end

