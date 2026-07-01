%k=1e-15;
k=1e-9;
p0=1e4;
ro=1000;
g=9.8;
u=0.001;
n=0.1;

px=k*p0/(u*n);
alfa=ro*g*k/(u*n);

tmax=4.5;
t=0:0.01*tmax:tmax;

%x=(2*k*p*ro*g/(u*n)*t).^0.5;
x=(2*px*t).^0.5;

figure %2016-12-20Ìí¼Ó 
plot(t,x);
hold on
xmax=max(x);
x=0:0.01*xmax:xmax;
%t=-(n*x/((k*ro*g/u)*ro*g)+(n*p*log(1-ro*g*x/p)/((k*ro*g/u)*(ro*g)^2)));
t=-x/alfa-px/alfa^2*log(1-alfa*x/px);
t=t(t<tmax);
x=x(1:size(t,2));
plot(t,x);
hold on