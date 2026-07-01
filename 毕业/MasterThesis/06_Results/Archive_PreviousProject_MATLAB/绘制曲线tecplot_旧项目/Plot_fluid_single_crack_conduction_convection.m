function [ output_args ] = Plot_fluid_single_crack_conduction_convection( ro,Cv,lamda_f,T0,dP,u,a,L,x,t,outfilename )
%2017-11-13添加 流体在单挑裂缝内的热传导和热对流
%2018-5-6 增加了解析解的第二项，最初的公式丢掉了第二项。
%   x为向量 t为常量
vx=1/(12*u)*dP/L*a^2; %裂缝内的流速
Pe=ro*Cv*vx*L/lamda_f
D=lamda_f/(ro*Cv);
T=T0/2*erfc((x-vx*t)/(2*(D*t)^0.5))+T0/2*exp(x*vx/D).*erfc((x+vx*t)/(2*(D*t)^0.5)); %2018-5-6增添了第二项+T0/2*exp(x*vx/D)*erfc((x+vx*t)/(2*(D*t)^0.5));
plot(x,T)
outfilename = strcat(outfilename(1:end-4),'-fluid-T-with-x.dat');
fidw=fopen(outfilename,'w');
fprintf(fidw,'TITLE = "Temperature with x at %f s"\n',t);
fprintf(fidw,'VARIABLES = "X(m)", "Temperature-fluid(<sup>0</sup>C)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature with X at %f s"\n',t);
pointTvalue=double([x; T]);
fprintf(fidw,'%e %e\n',pointTvalue);
plot(x,T);
end

