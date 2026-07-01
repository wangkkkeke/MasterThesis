%------2017-3-14添加
% outfilename='KGD-Lisjak-half-gmsh-crack-length-数值解.dat';
% fidw=fopen(outfilename,'w');
% % t=[1 2 3 4 5 6 7 8 9 10 11];
% % x=[1.1 2.1 2.2 3.1 4.1 4.2 5.1 5.4 6.1 6.7 7.3];
% % t=[100 200 300 400 500 600 700 1000 1100 1500 2000 2200 2550 3000 3500 4000 4500 5000]*1e4*2.5e-7; %取饱和度50%的结果
% % x=[0.65 0.955 1.284 1.522 1.744 1.97 2.1915 2.79 2.97 3.7 4.4 4.7 5.2 5.9 6.5 7.1 7.7 8.3];
% t=[100 500 1000 1500 2000 2500 3000 3500 4000 4500 5000]*1e4*2.5e-7; %取饱和度50%的结果
% x=[0.65 1.75 2.79 3.7 4.4 5.2 5.9 6.5 7.1 7.7 8.3];
% hold on
% plot(t,x,'o');
% hold on
% fprintf(fidw,'TITLE = "t-crack_length - Numerical solution"\n');
% fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
% fprintf(fidw,'ZONE DATAPACKING=POINT, T="crack_length"\n');
% pointTvalue=double([t; x]);
% fprintf(fidw,'%e %e\n',pointTvalue);

%------2017-3-14添加
outfilename='KGD-chen-half-gmsh-crack-length-数值解.dat';
fidw=fopen(outfilename,'w');
t=[100 500 1000 1500 2000 2500 3000]*1e4*2.5e-7; %取饱和度50%的结果
x=[0.4 1 1.4 1.9 2.2 2.6 3.0];
x=[0.3 0.825 1.31 1.725 2.115 2.475 2.8315];
hold on
plot(t,x,'+');
hold on
fprintf(fidw,'TITLE = "t-crack_length - Numerical solution"\n');
fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="crack_length"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);

%---2017-3-16添加
outfilename='KGD-Lisjak-half-gmsh-Aperture-数值解.dat';
fidw=fopen(outfilename,'w');
t=[100 500 1000 1500 2000 2500 3000 3500 4000 4500 5000]*1e4*2.5e-7; %取饱和度50%的结果
%x=[4.78 8.37 10.7 12.35 13.69 14.84 15.88 16.83 17.73 18.60 19.45]*1e-5*2 + 2e-5;
wu=[4.7822  8.37586 10.7004 12.3595 13.695  14.8441 15.8854 16.8356 17.7378 18.6076 19.4623]*1e-5; %上壁的竖向位移
wd=[4.78053 8.37218 10.6951 12.3528 13.6872 14.8352 15.8755 16.8247 17.7259 18.5948 19.4486]*1e-5; %下壁的竖向位移
wu(3)=10.7478*1e-5;wd(3)=wu(3);
x=(wu+wd)+2e-5;
hold on
plot(t,x,'o');
hold on
fprintf(fidw,'TITLE = "t-Aperture(m) - Numerical solution"\n');
fprintf(fidw,'VARIABLES = "t", "Aperture(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Aperture(m)"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);
