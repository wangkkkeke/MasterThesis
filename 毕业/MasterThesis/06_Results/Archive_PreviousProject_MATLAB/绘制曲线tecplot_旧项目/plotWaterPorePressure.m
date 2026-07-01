function [ output_args ] = plotWaterPorePressure( Kmacro,outfilename )
%绘制孔隙水压随着时间的变化 2016-5-18添加
%   此处显示详细说明
fidw=fopen(outfilename,'w');
%---------第1个时刻
a=1e-5;
bta=1/2200e6;
u=1e-3;
l=1;
t=20000*1e-7;
T=(Kmacro/u*t)/(bta*l^2);

x=0:0.05:1;
syms n;
for i=1:size(x,2)
    pp0(i)=vpa(1+4/pi*symsum(exp(-(2*n+1)^2*(T/4)*pi^2)*cos((2*n+1)*pi*x(i)/2)*((-1)^(n+1)/(2*n+1)), n,0,500));
end
plot(x,pp0);
fprintf(fidw,'TITLE = "Fluid Pressure at %f s"\n',t);
fprintf(fidw,'VARIABLES = "X", "Pressure"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Pressure along x at %f s"\n',t);
pointTvalue=double([x; pp0]);
fprintf(fidw,'%e %e\n',pointTvalue);
end

