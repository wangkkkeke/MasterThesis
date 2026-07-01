function [ output_args ] = plot_Point_disp_y_to_tecplot(x,E,v,L,p,outfilename)
%2015-12-15添加  绘制 fanban-onecrack.y 裂纹张开度分布曲线 并将曲线数据导出为tecplot文件
%   x为向量
fidw=fopen(outfilename,'w');
w=4*(1-v^2)*p*L*(1-(x/L).^2).^0.5/E;  %2015-12-15 增添.^0.5  这是数值解和解析解不吻合的根本原因
%clear n; %取消符号变量定义
plot(x,w);
hold on
fprintf(fidw,'TITLE = "aperture along crack "\n');
fprintf(fidw,'VARIABLES = "X", "uy"\n');
fprintf(fidw,'ZONE DATAPACKING=POINT, T="Temperature at  s"\n');
pointValue=double([x; w/2]);
fprintf(fidw,'%e %e\n',pointValue);
end
