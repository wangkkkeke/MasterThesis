%将juxing-seepage-2D-stuct.y 的非饱和渗流 峰前线的数值解输出到tecplot
outfilename='juxing-1D-unsat-峰前线-数值解.dat';
fidw=fopen(outfilename,'w');
% t=[0 7 15 30 50 76 120 150 190 210 250 270 300     370 430 500 570   630 660 740 780 860 900 960 1030 1130 1220 1320]*1e5*1e-8;
% x=[0 0.03 0.05 0.07 0.1 0.12 0.15 0.17 0.19 0.2 0.22 0.23 0.24   0.27 0.29 0.31 0.33  0.35 0.36 0.38 0.39 0.41 0.42 0.43 0.45 0.47 0.49 0.51];
%----sat=0.5
t=[0 40   100  200  300  400    600    800    1000   1200  1400  1600  1800  2000  2200   2400  2600  2800 3000  ]*1e4*1e-7;
x=[0 0.09 0.14 0.2 0.245 0.282  0.345  0.397  0.446  0.488 0.527 0.565 0.595 0.631 0.6625 0.692 0.719 0.747 0.774    ];
% t=t(1:end-2);
% x=x(1:end-2);
plot(t,x,'o');
hold on
% %----sat=0.99
% t=[0 100  500 1000  1500 2000 2500 3000 3500 4000 4500]*1e4*1e-7;
% x=[0 0.13 0.31 0.44 0.54 0.62 0.7  0.76 0.83 0.88 0.94];
% plot(t,x,'o');
hold on
fprintf(fidw,'TITLE = "t-x - Numerical solution"\n');
fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Numerical-no-gravity"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);

%------重力部分乘以三个节点的平均饱和度 fs=sat 结果不好
% outfilename='juxing-1D-unsat-含重力-峰前线-数值解.dat';
% fidw=fopen(outfilename,'w');
% t=[0 40    100   200    300   400    500    600   700   800   900   1000   1100   1200  1300  1400   1500  1600   2000  3000  4000  4500 ]*1e4*1e-7;
% x=[0 0.086 0.135 0.1875 0.227 0.2595 0.2874 0.315 0.336 0.356 0.375 0.3935 0.4075 0.425 0.4375 0.454 0.466 0.4775 0.525 0.615 0.686 0.716];
% plot(t,x,'o');
% hold on
% fprintf(fidw,'TITLE = "t-x -with grivat Numerical solution"\n');
% fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
% fprintf(fidw,'ZONE DATAPACKING=POINT, T="X with t"\n');
% pointTvalue=double([t; x]);
% fprintf(fidw,'%e %e\n',pointTvalue);

%------重力乘以纯水压作用下流出节点的平均饱和度 fs=sat  这个结果与解析解最为接近
outfilename='juxing-1D-unsat-含重力-峰前线-数值解.dat';
fidw=fopen(outfilename,'w');
%--sat=0.5
t=[0 40    100   200   300   400      600   800   1000  1200  1400 1600  1800 2000 2200  2400  2600  2800  3000]*1e4*1e-7;
x=[0 0.086 0.135 0.186 0.225 0.256  0.306 0.347 0.385 0.415 0.443  0.467 0.49 0.51 0.532 0.549 0.567 0.585 0.595];
% t=t(1:end-3); 
% x=x(1:end-3);
plot(t,x,'o');
hold on
% %----sat=0.99
% t=[0 100  500  1000  1500 2000 2500 3000 3500 4000 4500]*1e4*1e-7;
% x=[0 0.12 0.27 0.37  0.45 0.5  0.55 0.59 0.63 0.66 0.68];
% plot(t,x,'o');
% hold on
fprintf(fidw,'TITLE = "t-x -with grivat Numerical solution"\n');
fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Numerical-with-gravity"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);

% %------重力乘以纯水压作用下流出节点的平均饱和度 fs=sat*sat(3-2*sat); 结果不好 差距很大
% outfilename='juxing-1D-unsat-含重力-峰前线-数值解.dat';
% fidw=fopen(outfilename,'w');
% t=[0 100    500   1000 1500  2000 2500   3000  3500  4000  4500]*1e4*1e-7;
% x=[0 0.135 0.284 0.385 0.455 0.513 0.558 0.598 0.635 0.665 0.694];
% plot(t,x,'o');
% hold on
% fprintf(fidw,'TITLE = "t-x -with grivat Numerical solution"\n');
% fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
% fprintf(fidw,'ZONE DATAPACKING=POINT, T="X with t"\n');
% pointTvalue=double([t; x]);
% fprintf(fidw,'%e %e\n',pointTvalue);

%将juxing-seepage-2D-stuct.y 的非饱和渗流 峰前线的 解析解 输出到tecplot
%k=1e-15;
k=1e-9;
p0=1e4;
ro=1000;
g=9.8;
u=0.001;
n=0.1;

px=k*p0/(u*n);
alfa=ro*g*k/(u*n);

%tmax=4.5;
tmax=3;
t=0:0.01*tmax:tmax;

outfilename='juxing-1D-unsat-峰前线-解析解.dat';
fidw=fopen(outfilename,'w');
% tmax=max(t);
% t=0:0.01*tmax:tmax;
%x=(2*k*p*ro*g/(u*n)*t).^0.5;
x=(2*k*p0/(u*n)*t).^0.5;
plot(t,x);
hold on
fprintf(fidw,'TITLE = "t-x - analysis solution"\n');
fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Analysis-no-gravit"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);

%将juxing-seepage-2D-stuct.y 的非饱和渗流 考虑重力的 峰前线的 解析解 输出到tecplot
outfilename='juxing-1D-unsat-有重力-峰前线-解析解.dat';
fidw=fopen(outfilename,'w');
% tmax=max(t);
% t=0:0.01*tmax:tmax;
% x=(2*k*p*ro*g/(u*n)*t).^0.5;
% xmax=0.68;
xmax=0.6;
x=0:0.01*xmax:xmax;
%t=-(n*x/((k*ro*g/u)*ro*g)+(n*p*log(1-ro*g*x/p)/((k*ro*g/u)*(ro*g)^2)));
t=-x/alfa-px/alfa^2*log(1-alfa*x/px);
plot(t,x);
hold on
fprintf(fidw,'TITLE = "t-x - with gravit analysis solution"\n');
fprintf(fidw,'VARIABLES = "t", "X(m)"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Analysis-with-gravit"\n');
pointTvalue=double([t; x]);
fprintf(fidw,'%e %e\n',pointTvalue);
