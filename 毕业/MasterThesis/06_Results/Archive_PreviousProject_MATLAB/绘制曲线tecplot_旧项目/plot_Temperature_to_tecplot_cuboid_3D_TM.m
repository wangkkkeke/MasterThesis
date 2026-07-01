function [ output_args ] = plot_Temperature_to_tecplot_cuboid_3D_TM(ro,cp,K,L,t,outfilename)
%2016-10-1添加  绘制 cuboid_3D_TM.y 的温度分布曲线 并将曲线数据导出为tecplot文件
%   此处显示详细说明
%plot_Temperature_to_tecplot_cuboid_3D_TM(1000,0.2,1.6,10,0.3,'cuboid-3D-TM-temperature-0.3s.dat')
fidw=fopen(outfilename,'w');
x=0:0.025*L:L;
T1=100;
T2=0;
k=K/(ro*cp);
syms n;
for i=1:size(x,2)
    T(i)=vpa(2/pi*symsum(exp(-k*n^2*pi^2*t/L^2)*((T2*cos(n*pi)-T1)/n)*sin(n*pi*x(i)/L),n,1,500));
end
T=T1+x/L*(T2-T1)+T;

%clear n; %取消符号变量定义
plot(x,T);
hold on
fprintf(fidw,'TITLE = "Temperature along radi"\n');
fprintf(fidw,'VARIABLES = "X(m)", "Temperature-d-solid(<sup>0</sup>C)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature along x"\n');
fprintf(fidw,'DT=(DOUBLE,DOUBLE)"\n');
pointTvalue=double([x; T]);
fprintf(fidw,'%e %e\n',pointTvalue);
end

% function [ T ] = Anysis_temperature_cuboid_3D_TM(ro,cp,K,L,t)
% %2016-10-1添加  绘制 cuboid_3D_TM.y 的温度分布曲线 并将曲线数据导出为tecplot文件
% %   此处显示详细说明
% x=0:0.05*L:L;
% T1=100;
% T2=0;
% k=K/(ro*cp);
% syms n;
% for i=1:size(x,2)
%     T(i)=vpa(2/pi*symsum(exp(-k*n^2*pi^2*t/L^2)*((T2*cos(n*pi)-T1)/n)*sin(n*pi*x/L)));
% end
% T=T1+x/L*(T2-T1);
% end

