function [ output_args ] = plot_Point_Temperature_to_tecplot( k,c,ro,Th,Tc,len,t,outfilename)
%2015-9-6添加  绘制 矩形板两侧温度固定 juxing-TM.y 温度分布曲线 并将曲线数据导出为tecplot文件
%   此处显示详细说明
T0=Th-Tc;
x=0:0.01:1;
x=x*len;
a=k/(c*ro);
%outfilename='abc-new.dat';
fidw=fopen(outfilename,'w');
syms n;
for i=1:size(x,2)
T(i)=vpa(4*T0/pi*symsum(exp(-a*(2*n+1)^2*pi^2*t/len^2)*sin((2*n+1)/len*pi*x(i))/(2*n+1),n,0,500));
end
%clear n; %取消符号变量定义
plot(x,T);
hold on
fprintf(fidw,'TITLE = "Temperature at %f s"\n',t);
fprintf(fidw,'VARIABLES = "X", "Temperature"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature at %f s"\n',t);
pointTvalue=double([x; T]);
fprintf(fidw,'%e %e\n',pointTvalue);
end

