%绘制带孔圆板因为温度引起的应力分布 2015-9-11
E=3e9;
v=0.29;
alfa=5e-6;
Ta=100;
Tb=0;
a=0.5;
b=5.0;
r=a:0.01*(b-a):b;
[sigr,sigsita,sigtao]=HollowCylinderStress(E,v,alfa,Ta,Tb,a,b,r); %解析解
plot(r',sigr');
figure
plot(r',sigsita');
figure
plot(r',sigtao');
monitorData=ReadMonitorRadiusData('T-mi-new-输出热应力.dat');
x=monitorData(:,1);
y=monitorData(:,2);
r_num=(x.^2+y.^2).^0.5;
sigx=monitorData(:,9);
sigy=monitorData(:,10);
sigxy=monitorData(:,11);
[ sigr_num,sigsita_num,sigtao_num ] = StressCartesianToPolarCoord( sigx,sigy,sigxy,270 );
plot(r',sigr',r_num',sigr_num',r',sigsita',r_num',sigsita_num',r',sigtao',r_num',sigtao_num');
legend('\sigma_r 解析解','\sigma_r 数值解','\sigma_sita 解析解','\sigma_sita 数值解','\sigma_tao 解析解','\sigma_tao 数值解');