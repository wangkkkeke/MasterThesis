function [ data_xy ] = plotHistory( dataFileName )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fidr=fopen(dataFileName,'r');
while feof(fidr)==0
  line=fgetl(fidr);
  if strcmpi(line(1:5),'TITLE')
      line=fgetl(fidr); %跳过第二行
      data_xy=fscanf(fidr,'%f %f %f %f %f %f %f %f %f\n',[9 inf]);
      data_xy=data_xy';
      %figure;
      %plot(data_xy(:,1),data_xy(:,7));    
  end
end
end
%--------绘制F-s曲线图的命令如下
%  jz_his= plotHistory(fullfile('Bp-newmodel-junzhi-his.dat'));
% act_his= plotHistory(fullfile('Bp-newmodel-act-his.dat'));
% plot(jz_his(:,1),jz_his(:,5)*1e-6,'r');
% hold on
% plot(act_his(:,1),act_his(:,5)*1e-6);
% legend('均质','非均质')

