function [ output_args ] = plot_Point_disp_y(x,E,v,L,p,outfilename,outfilename2)
%2015-12-16添加  绘制 fanban-onecrack.y 裂纹张开度分布曲线解析 并读入数值解数据绘制解析解
%   x为向量
w=4*(1-v^2)*p*L*(1-(x/L).^2).^0.5/E;  %2015-12-15 增添.^0.5  这是数值解和解析解不吻合的根本原因
%clear n; %取消符号变量定义
figure
plot(x,w);
hold on
if nargin==6
    monitorData=ReadMonitorRadiusData(outfilename);
    x=monitorData(:,1);
    uy=monitorData(:,4);
    plot(x,2*uy,'o');
    title(outfilename);
end

if nargin==7
    monitorData=ReadMonitorRadiusData(outfilename);
    monitorData2=ReadMonitorRadiusData(outfilename2);
    x=(monitorData(:,1) + monitorData2(:,1))/2.0;
    uy=abs(monitorData(:,4))+abs(monitorData2(:,4));
    plot(x,uy,'o');
    title(strcat(outfilename,outfilename2));
end

% w=4*(1-v^2)*p*L*(1-(x/L).^2).^0.5/E;  %2015-12-15 增添.^0.5  这是数值解和解析解不吻合的根本原因
% %clear n; %取消符号变量定义
% figure
% plot(x,w);
% hold on
% monitorData=ReadMonitorRadiusData(outfilename);
% x=monitorData(:,1);
% uy=monitorData(:,4);
% plot(x,2*uy,'o');
% title(outfilename);

% fprintf(fidw,'TITLE = "aperture along crack "\n');
% fprintf(fidw,'VARIABLES = "X", "uy"\n');
% fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature at  s"\n');
% pointValue=double([x; w/2]);
% fprintf(fidw,'%e %e\n',pointValue);
end


