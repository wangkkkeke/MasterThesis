%--读入tecplot结果云图数据文件 并输出满足条件的监测线上的数据曲线 2018-4-27
%TITLE = "ho-cy-3D-TM-Tin-big-solve-ThermalMech-65000.dat"
%VARIABLES = "X", "Y", "Z", "U<sub>x</sub>(m)", "U<sub>y</sub>(m)", "U<sub>z</sub>(m)", "U(m)", "V<sub>x</sub>(m/s)", "V<sub>y</sub>(m/s)", "V<sub>z</sub>(m/s)", "V(m/s)", "<greek>s</greek><sub>xx</sub>(Pa)", "<greek>s</greek><sub>yy</sub>(Pa)", "<greek>s</greek><sub>zz</sub>(Pa)", "<greek>s</greek><sub>xy</sub>(Pa)", "<greek>s</greek><sub>yz</sub>(Pa)", "<greek>s</greek><sub>xz</sub>(Pa)", "S<sub>max</sub>(Pa)", "S<sub>min</sub>(Pa)", "Shear<sub>Max</sub>", "Pressure(Pa)", "Saturation", "Flow(m<sup>3</sup>/s)", "Temperature(<sup>0</sup>C)"
%内径r=0.02 外径R=0.15 z=0.016

%破坏前
dataFileName='应力值-55000-fem.dat';
col=12; %共有24列数据
nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
x=nodedata(:,1);
y=nodedata(:,2);
z=nodedata(:,3);
Smax=nodedata(:,10);

dis=(x.^2+y.^2).^0.5;
R=0.15;
r=0.02;
z0=0.016;

%-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    rtemp=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/rtemp);
    else
        sita(i)=2*pi-acos(xr(i)/rtemp);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-65000-nei-bianjie.dat');

%-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    dis=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/dis);
    else
        sita(i)=2*pi-acos(xr(i)/dis);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-65000-wai-bianjie.dat');


%破坏后
dataFileName='ho-cy-3D-TM-Tin-big-solve-ThermalMech-80000.dat';
col=24; %共有24列数据
nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
x=nodedata(:,1);
y=nodedata(:,2);
z=nodedata(:,3);
Smax=nodedata(:,18);

dis=(x.^2+y.^2).^0.5;
R=0.15;
r=0.02;
z0=0.016;

%-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    rtemp=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/rtemp);
    else
        sita(i)=2*pi-acos(xr(i)/rtemp);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-80000-nei-bianjie.dat');

%-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    dis=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/dis);
    else
        sita(i)=2*pi-acos(xr(i)/dis);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-80000-wai-bianjie.dat');

%--------------------------------------------------------------------------------------------------------

%破坏前
dataFileName='ho-cy-3D-TM-Tout-big-solve-ThermalMech-55000.dat';
col=24; %共有24列数据
nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
x=nodedata(:,1);
y=nodedata(:,2);
z=nodedata(:,3);
Smax=nodedata(:,18);

dis=(x.^2+y.^2).^0.5;
R=0.15;
r=0.02;
z0=0.016;

%-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    rtemp=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/rtemp);
    else
        sita(i)=2*pi-acos(xr(i)/rtemp);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-55000-nei-bianjie.dat');

%-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    dis=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/dis);
    else
        sita(i)=2*pi-acos(xr(i)/dis);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-55000-wai-bianjie.dat');


%破坏后
dataFileName='ho-cy-3D-TM-Tout-big-solve-ThermalMech-80000.dat';
col=24; %共有24列数据
nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
x=nodedata(:,1);
y=nodedata(:,2);
z=nodedata(:,3);
Smax=nodedata(:,18);

dis=(x.^2+y.^2).^0.5;
R=0.15;
r=0.02;
z0=0.016;

%-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    rtemp=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/rtemp);
    else
        sita(i)=2*pi-acos(xr(i)/rtemp);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-80000-nei-bianjie.dat');

%-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
xr=x(id);
yr=y(id);
Smaxr=Smax(id);
num=size(xr,1);
sita=zeros(num,1);
for i=1:num
    dis=(xr(i)^2+yr(i)^2).^0.5;
    if yr(i)>=0
        sita(i)=acos(xr(i)/dis);
    else
        sita(i)=2*pi-acos(xr(i)/dis);
    end
end
[sita_new, I]=sort(sita);
% xr_new=xr(I);
% yr_new=yr(I);
Smaxr_new=Smaxr(I);
sita_new=sita_new/pi*180;
figure
plot(sita_new,Smaxr_new);
write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-80000-wai-bianjie.dat');



% %--------------------------------------------------------------------------
% %破坏前
% dataFileName='ho-cy-3D-TM-Tin-big-solve-ThermalMech-65000.dat';
% col=24; %共有24列数据
% nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
% x=nodedata(:,1);
% y=nodedata(:,2);
% z=nodedata(:,3);
% Smax=nodedata(:,18);
% 
% dis=(x.^2+y.^2).^0.5;
% R=0.15;
% r=0.02;
% z0=0.016;
% 
% %-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     rtemp=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/rtemp);
%     else
%         sita(i)=2*pi-acos(xr(i)/rtemp);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-65000-nei-bianjie.dat');
% 
% %-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     dis=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/dis);
%     else
%         sita(i)=2*pi-acos(xr(i)/dis);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-65000-wai-bianjie.dat');
% 
% 
% %破坏后
% dataFileName='ho-cy-3D-TM-Tin-big-solve-ThermalMech-80000.dat';
% col=24; %共有24列数据
% nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
% x=nodedata(:,1);
% y=nodedata(:,2);
% z=nodedata(:,3);
% Smax=nodedata(:,18);
% 
% dis=(x.^2+y.^2).^0.5;
% R=0.15;
% r=0.02;
% z0=0.016;
% 
% %-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     rtemp=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/rtemp);
%     else
%         sita(i)=2*pi-acos(xr(i)/rtemp);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-80000-nei-bianjie.dat');
% 
% %-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     dis=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/dis);
%     else
%         sita(i)=2*pi-acos(xr(i)/dis);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tin-big-80000-wai-bianjie.dat');
% 
% %--------------------------------------------------------------------------------------------------------
% 
% %破坏前
% dataFileName='ho-cy-3D-TM-Tout-big-solve-ThermalMech-55000.dat';
% col=24; %共有24列数据
% nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
% x=nodedata(:,1);
% y=nodedata(:,2);
% z=nodedata(:,3);
% Smax=nodedata(:,18);
% 
% dis=(x.^2+y.^2).^0.5;
% R=0.15;
% r=0.02;
% z0=0.016;
% 
% %-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     rtemp=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/rtemp);
%     else
%         sita(i)=2*pi-acos(xr(i)/rtemp);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-55000-nei-bianjie.dat');
% 
% %-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     dis=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/dis);
%     else
%         sita(i)=2*pi-acos(xr(i)/dis);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-55000-wai-bianjie.dat');
% 
% 
% %破坏后
% dataFileName='ho-cy-3D-TM-Tout-big-solve-ThermalMech-80000.dat';
% col=24; %共有24列数据
% nodedata=Read_Tecplot_Contour_Node_Data( dataFileName,col );
% x=nodedata(:,1);
% y=nodedata(:,2);
% z=nodedata(:,3);
% Smax=nodedata(:,18);
% 
% dis=(x.^2+y.^2).^0.5;
% R=0.15;
% r=0.02;
% z0=0.016;
% 
% %-----提取内径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis < r+(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     rtemp=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/rtemp);
%     else
%         sita(i)=2*pi-acos(xr(i)/rtemp);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-80000-nei-bianjie.dat');
% 
% %-----提取外径表面z=0.016处的节点的值，并按照逆时针排列，起点x轴正向sita=0
% id= ((dis > R-(R-r)/100) & (z>z0-z0/10));
% xr=x(id);
% yr=y(id);
% Smaxr=Smax(id);
% num=size(xr,1);
% sita=zeros(num,1);
% for i=1:num
%     dis=(xr(i)^2+yr(i)^2).^0.5;
%     if yr(i)>=0
%         sita(i)=acos(xr(i)/dis);
%     else
%         sita(i)=2*pi-acos(xr(i)/dis);
%     end
% end
% [sita_new, I]=sort(sita);
% % xr_new=xr(I);
% % yr_new=yr(I);
% Smaxr_new=Smaxr(I);
% figure
% plot(sita_new,Smaxr_new);
% write_curve_To_teclplot('<greek>q</greek>','S<sub>max</sub>',sita_new',Smaxr','ho-cy-3D-TM-Tout-big-80000-wai-bianjie.dat');
