function [outputArg1,outputArg2] = plot_v91_ex3_flow_around_cylinder(p1,p2,a,L,ro,g)
%2018-10-12添加
%   plot_v91_ex3_flow_around_cylinder(2e6,0,1,4,1000,9.8)
h1=p1/(ro*g);
h2=p2/(ro*g);
h1=1;
h2=0;
sita=0;
r=a:0.1*(0.5*L-a):0.5*L;
% sita=180;
% r=-0.5*L:0.1*(0.5*L-a):-a;

h=(h1-h2)/L*(r+a^2./r)*cos(sita/180*pi)+0.5;
plot(r,h);
%plot(r,ro*g*h);
write_curve_To_teclplot( 'x(m)','Pore-Pressure (Pa)', r,h,'v91-ex3-过圆心的水平监测线的水压.dat');
end

