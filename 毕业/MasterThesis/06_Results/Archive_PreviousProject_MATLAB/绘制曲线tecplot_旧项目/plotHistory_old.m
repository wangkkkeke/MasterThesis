function [ output_args ] = plotHistory_old( dataFileName )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fidr=fopen(dataFileName,'r');
while feof(fidr)==0
  line=fgetl(fidr);
  if strcmpi(line(1:2),'uy')
      data_xy=fscanf(fidr,'%f %f\n',[2 inf]);
      data_xy=data_xy';
      plot(data_xy(:,1),data_xy(:,2))     
  end

end
end

