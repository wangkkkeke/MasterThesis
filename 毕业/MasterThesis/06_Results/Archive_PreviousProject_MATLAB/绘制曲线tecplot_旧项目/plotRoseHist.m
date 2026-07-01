function [ output_args ] = plotRoseHist( dataFileName )
%plotRose 此处显示有关此函数的摘要
%   2015-1-9 根据节理的方向矢量绘制玫瑰花图
fidr=fopen(dataFileName,'r');
while feof(fidr)==0
    line=fgetl(fidr);
    if strcmpi(line(1:5),'TITLE')
        line=fgetl(fidr); %跳过第二行
        data_xy=fscanf(fidr,'%f %f\n',[2 inf]);
        data_xy=data_xy';
    end
end
%---------测试数据  以后写的程序，一定要事先用简单的数据去测试，然后再用来算具体的问题！切记 2015-1-13 这样可以节省很多时间
%data_xy=[1 1;-1 1;-1 -1;1 -1]
%data_xy=[1 2;-1 2;-1 -2;1 -2]
%data_xy=[0 1;-1 0;0 -1;1 0]
%-----------------------
anger=zeros(size(data_xy,1),1); 
anger_pi=zeros(size(data_xy,1),1); %0-180度范围
for in=1:size(data_xy,1)
    x=data_xy(in,1);
    y=data_xy(in,2);
    if (x>0&&y>=0)
        anger(in)=atan(abs(y/x))/pi*180;
    elseif x<0&&y>=0
        anger(in)=atan(abs(y/x))/pi*180;
        anger(in)=180-anger(in);
    elseif x<0&&y<=0 %y>=0 改为y<=0
        anger(in)=atan(abs(y/x))/pi*180;
        anger(in)=180+anger(in);
    elseif x>0&&y<=0
        anger(in)=atan(abs(y/x))/pi*180;
        anger(in)=360-anger(in); %360+改为360-
    elseif x==0&&y>0
        anger(in)=90;
    elseif x==0&&y<0;
        anger(in)=270;
    end
    
%     anger_pi(in)=anger(in);  %2015-1-12注释掉
%     if anger_pi(in)>180
%         anger_pi(in)=anger_pi-180;
%     end
end
%----2015-1-12添加
anger_pi=anger;
anger_pi(anger_pi>180)=anger_pi(anger_pi>180)-180;
%----
figure
rose(anger/180*pi,40);  %rose()函数采用的是弧度
figure;
rose(anger_pi/180*pi,40);
figure;
hist(anger_pi,36);
end

