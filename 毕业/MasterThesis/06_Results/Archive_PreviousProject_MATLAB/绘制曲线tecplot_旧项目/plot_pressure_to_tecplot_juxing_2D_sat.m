function [ output_args ] = plot_pressure_to_tecplot_juxing_2D_sat(n,u,kp,Kw,L,t,outfilename )
%2016-11-20添加 juxing-2D-seepage.y 的解析解 并将曲线数据导出为tecplot文件
%   此处显示详细说明  n为孔隙率(孔隙的体积与总体积) kp为渗透率 Kw为流体体积模量
fidw=fopen(outfilename,'w');
x=0:0.025*L:L;
P1=100;
P2=0;
%k=(kp*1000*9.8/u)*Kw/n; %2016-12-20注释掉
k=(kp/u)*Kw/n;
syms n;
for i=1:size(x,2)
    P(i)=vpa(2/pi*symsum(exp(-k*n^2*pi^2*t/L^2)*((P2*cos(n*pi)-P1)/n)*sin(n*pi*x(i)/L),n,1,500));
end
P=P1+x/L*(P2-P1)+P;

%clear n; %取消符号变量定义
plot(x,P);
hold on
fprintf(fidw,'TITLE = "Pressure along x - analysis solution"\n');
fprintf(fidw,'VARIABLES = "X", "Pressure(Pa)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Pressure along x"\n');
pointTvalue=double([x; P]);
fprintf(fidw,'%e %e\n',pointTvalue);

end

