function [  ] = plotAEdistribution( dataFileName,nodeData,elemData,jointElemData)
%2013-4-22绘制声发射分布图
%   单元中的结点号从1开始
elemData=elemData';
nodeDataX=nodeData(:,1);%每个结点的x坐标
nodeDataY=nodeData(:,2);
x=nodeDataX(elemData);%由一维向量形成矩阵
y=nodeDataY(elemData);
figure
fill(x,y,'b');
hold on;
axis equal;
axis(AxisRange(nodeData));

fidr=fopen(dataFileName,'r');
while feof(fidr)==0
  line=fgetl(fidr);
  if strcmpi(line(1:5),'TITLE')
      line=fgetl(fidr); %跳过第二行
      data=fscanf(fidr,'%d %d %d %d\n',[4 inf]); 
      data=data';
      data(:,1)=data(:,1)+1;   %data 第1列表示节理单元的单元编号 ，从1开始
  end
end
brockjoint=jointElemData(data(:,1),1:4);
coorx=nodeData(:,1);
coory=nodeData(:,2);
xc=((coorx(brockjoint(:,1))+coorx(brockjoint(:,4)))/2+(coorx(brockjoint(:,2))+coorx(brockjoint(:,3)))/2)/2;
yc=((coory(brockjoint(:,1))+coory(brockjoint(:,4)))/2+(coory(brockjoint(:,2))+coory(brockjoint(:,3)))/2)/2;

xc1=xc(data(:,2)==3);
yc1=yc(data(:,2)==3);
s=15*ones(size(xc1,1),1);
scatter(xc1,yc1,3*s,'r'); %拉坏

xc1=xc(data(:,3)==3);
yc1=yc(data(:,3)==3);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,3*s,'r'); %拉剪

xc1=xc(data(:,4)==3);
yc1=yc(data(:,4)==3);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,3*s,'r'); %压剪
%--------------------------------------

xc1=xc(data(:,2)==2);
yc1=yc(data(:,2)==2);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,2*s,'r'); %拉坏

xc1=xc(data(:,3)==2);
yc1=yc(data(:,3)==2);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,2*s,'y'); %拉剪

xc1=xc(data(:,4)==2);
yc1=yc(data(:,4)==2);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,2*s,'g'); %压剪
%--------------------------------------
xc1=xc(data(:,2)==1);
yc1=yc(data(:,2)==1);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,s,'r');
xc1=xc(data(:,3)==1);
yc1=yc(data(:,3)==1);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,s,'y');
xc1=xc(data(:,4)==1);
yc1=yc(data(:,4)==1);
s=10*ones(size(xc1,1),1);
scatter(xc1,yc1,s,'g');
%--------------------------------------
end

