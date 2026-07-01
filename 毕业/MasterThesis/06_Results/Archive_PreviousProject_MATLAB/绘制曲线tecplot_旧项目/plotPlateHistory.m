function [ data_xy ] = plotPlateHistory( dataFileName )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
fidr=fopen(dataFileName,'r');
while feof(fidr)==0
  line=fgetl(fidr);
  if strcmpi(line(1:5),'TITLE')
      line=fgetl(fidr); %跳过第二行
      data_xy=fscanf(fidr,'%d %e %e\n',[3 inf]); % %f %f改为%e %e
      data_xy=data_xy';
      data_xy=data_xy(:,[2 3]); 
      figure;
      plot(data_xy(:,1),data_xy(:,2));    
  end
end

end

