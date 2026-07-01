function [ data_xy,allData ] = plotAEHistory( dataFileName,Interval)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
fidr=fopen(dataFileName,'r');
while feof(fidr)==0
  line=fgetl(fidr);
  if strcmpi(line(1:5),'TITLE')
      line=fgetl(fidr); %跳过第二行
      data_xy=fscanf(fidr,'%f %f %f %f %f\n',[5 inf]);    
  end
end
data_xy=data_xy';
numgap=0;
num=1;
numData=size(data_xy,1);
allData=zeros(numData,5);
data=zeros(floor(numData/Interval)+3,5);
for i=1:numData
    numgap=numgap+1;
    data(num,2:5)=data(num,2:5)+data_xy(i,2:5);
    if numgap-1==Interval
        data(num,1)=data_xy(i-floor(Interval/2),1);
        num=num+1;
        numgap=0;
    end
    allData(i,1)=data_xy(i,1);
    if i>1
       allData(i,2:5)=allData(i-1,2:5)+data_xy(i,2:5);%累计声发射数
    end
end
figure;
plot(data(:,1),data(:,5));
figure
plot(allData(:,1),allData(:,5));
figure
plot(allData(:,1),allData(:,2),'b');
hold on
plot(allData(:,1),allData(:,3),'k');
hold on
plot(allData(:,1),allData(:,4),'r');
plot(allData(:,1),allData(:,5),'g');
legend('拉破坏','拉剪破坏','压剪破坏','总的破坏')
xlabel('位移/mm');
ylabel('累计声发射次数');
end

