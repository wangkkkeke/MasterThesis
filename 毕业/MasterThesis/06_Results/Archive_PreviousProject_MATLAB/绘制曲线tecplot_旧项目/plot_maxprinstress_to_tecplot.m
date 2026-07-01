function [ output_args ] = plot_maxprinstress_to_tecplot(outfilename)
%2015-9-20添加  绘制 TM-2circle.y 最大主应力最大值随时间的变化曲线 并将曲线数据导出为tecplot文件
%   此处显示详细说明
fidw=fopen(outfilename,'w');
data=[0 0;
    1000 -6357.78
    2000 625215
    3000 1.30834e6
    4000 745993
    5000 405380
    6000 1.14725e6
    7000 1.65798e6
    8000 1.5387e6
    9000 1.08497e6
    10000 1.79714e6
    20000 3.54495e6
    40000 6.51539e6
    60000 8.95336e6
    80000 1.07976e7
    90000 1.15462e7
    100000 1.13333e7
    102000 1.08448e7
    104000 8.99765e6
    105000 8.07634e6    
 ];
plot(data(:,1),data(:,2));
hold on
fprintf(fidw,'TITLE = "max(maxprinstress) along time step"\n');
fprintf(fidw,'VARIABLES = "step", "Max_maxprinstress"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Max_maxprinstress along time"\n');
fprintf(fidw,'%e %e\n',data');
end

