function [ output_args ] = plot_KGD_Lt_Wt_to_tecplot(E,v,u,q0,t,outfilename)
%2016-3-18添加  绘制 KGD模型 裂纹扩展长度L随时间的变化 并将曲线数据导出为tecplot文件
%   t为向量   q0为总注入量的一半  因为为半边 2016-5-10
% Example :plot_KGD_Lt_Wt_to_tecplot(20,0.19,0.001,1e-3,[0:0.2:50],'KGD模型解析解.dat')
fidw=fopen(outfilename,'w');
Ep=E/(1-v^2);
L1=2*0.539*(Ep*q0^3/u)^(1/6.0)*t.^(2/3);  
w1=2.36*(u*q0^3/Ep)^(1/6.0)*t.^(1/3);  %李世海及Fu的论文中的公式
p0=1.09*(Ep^2*u)^(1/3)*t.^(-1/3);

Q0=2*q0; %2016-5-10添加
up=12*u;
rmo=0.616;
L2=2*rmo*(Ep*Q0^3/up)^(1/6.0)*t.^(2/3);
A0=3^(1/2);
A11=-0.156;
B1=6.63e-2;
wmo=A0+A11+B1*(4+0);
w2=(up./(Ep*t)).^(1/3).*L2.*(wmo*rmo);  %E. Detournay论文中的公式


figure
plot(t,L1/2,t,L2/2,'--');%L1, L2裂纹半长度 2016-4-21
legend('李世海-公式','Detournay-公式')
title('裂纹半长');

% figure
% plot(t,w1/2,t,w2/2,'--');
% title('裂纹张开宽度的一半');
% legend('李世海-公式','Detournay-公式')

figure
plot(t,w1,t,w2,'--');
title('裂纹张开宽度');
legend('李世海-公式','Detournay-公式')

figure
plot(t,p0,'o');
title('注入点的压力');

fprintf(fidw,'TITLE = "L  and W along time "\n');
fprintf(fidw,'VARIABLES = "t", "L1-half", "W1-half", "L2-half", "W2-half"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="long and  aperture at  s"\n');
pointValue=[t; L1/2; w1/2; L2/2; w2/2];
fprintf(fidw,'%e %e %e  %e %e\n',pointValue);
end