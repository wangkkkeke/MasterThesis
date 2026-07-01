%绘制远场地应力作用下，圆孔监测线的应力的数值解及解析解 2015-4-30
% 水平监测线A 竖向监测线 B
r0=2.0;
sigh=10e6;sigv=30e6;
r=r0:0.2*r0:10*r0; 
sitaA=0; %水平监测线 A
%[sigr,sigsita,sigtao] = BoreholeStressPolar( sigh,sigv,r0,sitaA,r );
[sigrA,sigsitaA,sigtaoA] = BoreholeStressPolar( sigh,sigv,r0,sitaA,r );
%createfigure_polar_stress([r' r'],[sigrA' sigsitaA']);
%plot(r,sigr,'b',r,sigsita,'r');
%title('水平监测线A');
%figure
sitaB=90;
[sigrB,sigsitaB,sigtaoB] = BoreholeStressPolar( sigh,sigv,r0,sitaB,r );
%plot(r,sigr,'b',sigsita,'r');
%createfigure_polar_stress([r' r'],[sigrB' sigsitaB']);

%--转换到直角坐标
[ sigxA,sigyA,sigxyA ] = StressPolarToCartesianCoord( sigrA,sigsitaA,sigtaoA,sitaA );
%createfigure_cartesianCoord_stress([r' r'], [sigxA' sigyA']);
%------读取数值模拟 水平监测线的数据
monitorData=ReadMonitorLineDataFromTecplot('xzhou.dat',21);
plot(r',sigxA',r',sigyA',monitorData(:,1),monitorData(:,9)*-1,monitorData(:,1),monitorData(:,10)*-1); %monitorData(:,9)对应sigx 10对应sigy
legend('\sigma_x 解析解','\sigma_y 解析解','\sigma_x 数值解','\sigma_y 数值解')
%plot(monitorData(:,1),monitorData(:,9)*-1);

[ sigxB,sigyB,sigxyB ] = StressPolarToCartesianCoord( sigrB,sigsitaB,sigtaoB,sitaB );
createfigure_cartesianCoord_stress([r' r'], [sigxB' sigyB']);


